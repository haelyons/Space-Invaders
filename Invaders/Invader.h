#ifndef INVADER_H
#define INVADER_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** Invader.h
* @brief Defines variables and methods for the Invader object
* @author Helios A. Lyons
* @date April, 2020
*/
 
class Invader
{
public:
    /** Constructor */
    Invader();
    /** Destructor */
    ~Invader();
    
    /** Initialises variables
    * @param value for sprite, hitpoints and boss (int)
    */
    void init(int sprite, int hitpoints, int boss);
    
    /** Draws contents to LCD
    * @param bitmap and position values (bit, int)
    */
    void draw(N5110 &lcd);
    
    /** Gets sprite value
    * @return sprite value (int)
    */
    int get_sprite();
    
    /** Decrement hitpoints
    * @return a decremented value for hitpoints
    */
    int hit();
    
    /** Returns death
    * @return boolean for death state
    */
    bool get_death();
    
    /** Gets position
    * @return current position (Vector2D)
    */
    Vector2D get_pos();
    
    /** Gets width
    * @return width of sprite (int)
    */
    int get_width();
    
    /** Gets height
    * @return height of sprite (int)
    */
    int get_height();
    
    /** Sets position
    * @param sets position based on x and y inputs (int)
    */
    void set_pos(int x, int y);
    
    int _speed;
 
private:

    int _height;
    int _width;
    int _x;
    int _y;
    int _hitpoints;
    bool _death;
    int _sprite;
    
    Vector2D _velocity;
    
 
};
#endif