#ifndef BATTLE_H
#define BATTLE_H
 
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#include "Canon.h"
#include "Invader.h"
#include "Army.h"
#include "Bullet.h"

#include <vector>

/** Battle.h
* @brief Main engine for the game, instatiates canon and army objects
* @author Helios A. Lyons
* @date May, 2020
*/

using namespace std;
extern std::vector<std::vector<Invader*> > invaders;
 
class Battle
{
 
public:
    /** Constructor */
    Battle();
    /** Destructor */
    ~Battle();
    
    /** Creates a rectangle
    * @param rectangle (struct)
    */
    // Struct for bounding boxes – rectangles (canon, invaders, bullets)
    // Idea taken from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
    struct Rectangle
    { 
        Rectangle(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
        int x;
        int y;
        int width;
        int height;
    };
    /** Initialises variables
    * @param value for invader vector (int), speed (int), interval (int), boss (bool), and boss number (int)
    */
    void init(int rows, int columns, int speed, int interval, bool boss, int bossNum);
    
    /** Reads input
    * @param gamepad input (struct)
    */
    void read_input(Gamepad &pad);
    
    /** Updates positions for canon and bullets
    * @param current positions (vector)
    */
    void update(Gamepad &pad);
    
    /** Draws contents to LCD
    * @param bitmap and position values (bit, int)
    */
    void draw(N5110 &lcd);
    
    /** Resets variables and vectors
    * @param vectors and variables to reset (int, bool, vector)
    */
    void reset(); // frees memory
    
    /** Returns battle end condition
    * @return boolean end condition
    */
    bool end();
    
    /** Returns lives
    * @return player lives remaining
    */
    int life();
    
    /** Resets player lives
    * @param player life from canon.h
    */
    void reset_life();

    /** Defines bullet vector 'bullets'
    * @param vector of bullet object pointers
    */
    vector<Bullet*> Bullets;
    
    /** Defines bullet vector 'bombs'
    * @param vector of bullet object pointers
    */
    vector<Bullet*> Bombs;
    
    Ticker t;
    
    /** Starts invader firing
    * @param invader_fire() method to certain time interval
    */
    void clock(Gamepad &pad);
    
    bool _boss;
    bool _end;
    bool _dead;
    int _speed;
    
private:

    void invader_fire();
    void canon_fire(Gamepad &pad);
    void projectile_edge();
    
    bool colTest(Rectangle r1, Rectangle r2);
    void bullet_collision(Gamepad &pad);
    void bomb_collision(Gamepad &pad); 
    void canon_collision(Gamepad &pad);
    
    int _x;
    int _interval;
    int _rows;
    int _columns;
    
    Canon _canon;
    Army _army;
    
    Direction _d;
    float _mag;
 
};
 
#endif