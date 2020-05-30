#include "Battle.h"
#include "Bullet.h"
#include "Invader.h"
#include "Army.h"

#include "N5110.h"
#include "Gamepad.h"

#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

Ticker t;
 
Battle::Battle()
{
    
}
 
Battle::~Battle()
{

}
 
void Battle::init(int rows, int columns, int speed, int interval, bool boss, int bossNum)
{
    reset(); // reset initial variables
    _speed = speed; // set value for accessible variables
    _interval = interval;
    _boss = boss;
    _rows = rows;
    _columns = columns;
     
    _canon.init(HEIGHT - 3); // initialise player
    _army.create_army(_rows,_columns,speed,_boss,bossNum); // initialise army
}

void Battle::read_input(Gamepad &pad)
{
    _d = pad.get_direction();
    _mag = pad.get_mag();
}

void Battle::draw(N5110 &lcd) // draw battle elements, and refresh display
{
    _canon.draw(lcd); // draw canon
    _army.draw(lcd); // draw invaders    
    
    for(int i = 0; i < Bombs.size(); i++) { Bombs[i]->draw(lcd); } // draw bombs
    for(int n = 0; n < Bullets.size(); n++) { Bullets[n]->draw(lcd); } // draw bullets
    lcd.refresh();
}

void Battle::clock(Gamepad &pad) // call invader fire at an interval of 2
{
    t.attach(Callback<void()>(this, &Battle::invader_fire), _interval);
}

void Battle::update(Gamepad &pad) // update canon position and firing, 
{                                 // and all projectile positions and collisions
    
    //_army.move_army();
    canon_fire(pad);
    _canon.update(_d,_mag);
    
    for(int i = 0; i < Bombs.size(); i++) { Bombs[i]->update(); } 
    for(int n = 0; n < Bullets.size(); n++) { Bullets[n]->update(); }

    projectile_edge();
    bullet_collision(pad);
    bomb_collision(pad);
}

void Battle::invader_fire() // pseudo-randomly select the position of an alive invader
{                           // and drop a bomb
    std::vector<int> fire_pos_y;
    std::vector<int> fire_pos_x;
    
    for (int i = 0; i < _rows; i++) { // iterate through invaders
            for (int n = 0; n < _columns; n++) {
                int state = invaders[i][n]->get_death(); 
                if (!state) { // add alive invader position to X and Y vectors
                    Vector2D fire_pos = invaders[i][n]->get_pos();
                    fire_pos_y.push_back(fire_pos.y);
                    fire_pos_x.push_back(fire_pos.x);
                    }
                }
            }
    // select random X and Y positions from the vectors        
    int rand1 = rand() % fire_pos_y.size();
    int rand2 = rand() % fire_pos_x.size();
    
    Vector2D fire_pos;
    fire_pos.y = fire_pos_y[rand1];
    fire_pos.x = fire_pos_x[rand2];
    
    // instantiate a new Bullet pointer, and add it to the Bomb vector
    Bombs.push_back(new Bullet()); // initialise the Bullet with owner, position, speed
    Bombs.back()->init(false, fire_pos.x + 4, fire_pos.y + 2, 3);
}

void Battle::canon_fire(Gamepad &pad) // fire when A is pressed, and add a new
{                                     // projectile to the player bullet vector
    bool A = pad.A_pressed();
    if (A) {
            Vector2D canon_pos = _canon.get_pos();
            int x1 = canon_pos.x + 2;
            int y1 = canon_pos.y + 1;
            
            Bullets.push_back(new Bullet());
            Bullets.back()->init(true, x1, y1, 3);
            
            printf("Player fired");
        }
}

void Battle::bullet_collision(Gamepad &pad) // bullet collision algorithm
{
    Vector2D BulPos;
    
    for(int z = 0; z < Bullets.size(); z++) { // iterate through bullets
        BulPos = Bullets[z]->get_pos(); // fetch each bullets position
        Rectangle bulletRect(BulPos.x, BulPos.y, 1, 2); // apply to rectangle
            
        for (int i = 0; i < _rows; i++) { // iterate through invaders
            for (int n = 0; n < _columns; n++) {
          
                bool state = invaders[i][n]->get_death();
        
                if (!state) { // only test for collision if invader is alive
                    Vector2D invPos = invaders[i][n]->get_pos(); // fetch parameters
                    int invWidth = invaders[i][n]->get_width();
                    int invHeight = invaders[i][n]->get_height();    
                    Rectangle invaderRect(invPos.x, invPos.y, invWidth, invHeight); // apply to rectangle 
                            
                    if(colTest(invaderRect, bulletRect)){ // compare invader vs. bullet rectangles
                        
                        invaders[i][n]->hit(); // if collided, decrease health
                        //int sprite = invaders[i][n]->get_sprite(); // add to kill count
                        //_canon.kill(sprite);
                        pad.tone(750.0,0.1); // play a tone
                        Bullets.erase(Bullets.begin() + z - 1); // and delete bullet
                        }
                }
            }
        }
    }
}

void Battle::bomb_collision(Gamepad &pad) // check if bombs have collided with the canon
{                                         // if so, remove life, play tone, 
    Vector2D BombPos;                     // and delete from vector
    Vector2D canonPos;
    
    for (int i = 0; i < Bombs.size(); i++) { // check 
        BombPos = Bombs[i]->get_pos();
        
        canonPos = _canon.get_pos();
        int canonWidth = _canon.get_width();
        int canonHeight = _canon.get_height();
        
        Rectangle canonRect(canonPos.x, canonPos.y, canonWidth, canonHeight);
        Rectangle bombRect(BombPos.x, BombPos.y, 2, 2);
        
        if (colTest(canonRect,bombRect)) {
            _canon.remove_life();
            pad.tone(650.0,0.1);
            Bombs.erase(Bombs.begin() + i - 1);
            }
        } 
}

void Battle::projectile_edge() // if projectiles are beyond screen limits
{                               // remove from the vector to free memory
    Vector2D BombEdge;
    Vector2D BullEdge;
    
    for(int i = 0; i < Bombs.size(); i++) {
        BombEdge = Bombs[i]->get_pos();
        if (BombEdge.y >= HEIGHT){
            Bombs.erase(Bombs.begin() + i - 1);
        }
    }

    for(int n = 0; n < Bullets.size(); n++) {
        BullEdge = Bullets[n]->get_pos();
        if (BullEdge.y <= 0){
            Bullets.erase(Bullets.begin() + n - 1);
        }
    }
}

bool Battle::end() // if all the invaders are dead, returns true
{
    if (_army.end()) { // saves main from interacting with army.h
        return _end = true;
        }
    else { return _end = false; }
}

void Battle::reset() // free memory from the vector pointers for projectiles
{   
    Bullets.clear();
    Bombs.clear();
    
    _end = false; // reset _end and _dead conditions
    _dead = false;
}

int Battle::life() // check next comment
{
    int lives = _canon.get_life();
    return lives;
}

void Battle::reset_life() // pulls from canon.h method so that main only
{                         // has to interact with battle.h
    _canon.reset_life();
}

bool Battle::colTest(Rectangle r1, Rectangle r2) // check if 2 rectangles 
{                                                // are overlapping
    return ((r1.x + r1.width > r2.x) // code taken from Mozilla:
        &&  (r1.x < r2.x + r2.width) // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
        &&  (r1.y + r2.height > r2.y) // for 2D game collisions
        &&  (r1.y < r2.y + r2.height));
}