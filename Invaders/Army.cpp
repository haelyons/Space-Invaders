#include "Army.h"
#include "Invader.h"
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>


using namespace std;

std::vector<std::vector<Invader*> > invaders;

Army::Army()
{

}

Army::~Army()
{

}

void Army::create_army(int rows, int columns, int speed, bool ifboss, int bossNum)
{
    _rows = rows; // assign variables
    _columns = columns;
    _boss = ifboss;
    
    invaders.clear(); // free memory from previous instances of the vector
    invaders.resize(_rows); // clear contents and resize to given # of rows, columns
    for (size_t i = 0; i < _rows; ++i) { invaders[i].resize(_columns); }
    
    int vector_width = _columns*8 + _columns; // calculate parameters of the vector
    int temp_x = WIDTH/2 - vector_width/2; // as a table, to allow proper Invader
    int start_y = HEIGHT/2 - 20;           // distribution
    _inc = 6;
    
    for (int i = 0; i < _rows; i++) { // nested 'for' looped through the vector    
        int start_x = temp_x; // reset x position at each row
        if (i > 0) {start_y += 9;} // increment y position from 2nd row onward
            
            for (int n = 0; n < _columns; n++) { // iterate through columns
                invaders[i][n] = new Invader(); // instantiate a new Invader pointer
                if (_boss) { // change sprite value if boss wave
                    int bossSprite = bossNum + 3;
                    invaders[i][n]->init(bossSprite,bossNum*2,1); // 
                    invaders[i][n]->set_pos(start_x,start_y);
                    }
                else {
                    invaders[i][n]->init(i+1,1,0); // initialise with sprite, HP, speed, and boss boolean
                    invaders[i][n]->set_pos(start_x,start_y);
                    int rowWidth = invaders[i][n]->get_width();
                    start_x += rowWidth + 2; // increment x position
                    }
            }
        }
}

bool Army::end() // find # of dead invaders and compare to expected result
{
    int sum = 0; 
    for (int i = 0; i < _rows; i++) { // iterate through Invader vector
            for (int n = 0; n < _columns; n++) { // and get death state for each
                bool inv_death = invaders[i][n]->get_death();
                if (inv_death) {sum++;} // add to sum
            }
        }
    
    if (sum == _rows*_columns) { // check sum vs. total number of invaders
        _end = true;
        return _end;
        }
    
    else {
        _end = false;
        return _end;
        }
}

void Army::draw(N5110 &lcd) // call draw for alive invaders
{    
    for (int i = 0; i < _rows; i++) { // iterate through Invader vector
        for (int n = 0; n < _columns; n++) { // call draw function if death is false
            bool state = invaders[i][n]->get_death();
            if (!state) {invaders[i][n]->draw(lcd);}
            }
        }
}

// NOTE: instead of all these 'for' loops, one that checked and deleted dead
// invaders would have been more efficient, if called prior to draw and 
// collision functions
        
// NOTE 2: std::for_each could have been used instead of functions called on 
// all invaders, but I could not identify the correct syntax for apply this
// to a vector of vectors of pointers.       
                             
//void Army::move_army()                
                                    
    // removed due to numerous errors, will be fixed if losing 5% is deemed
    // worth it                        
   