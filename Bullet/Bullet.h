#ifndef BULLET_H
#define BULLET_H
 
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Canon.h"
 
/** Bullet.h
* @brief Defines variables and methods for the bullet object
* @author Helios A. Lyons
* @date April, 2020
*/
class Bullet
{

public:
    /** Constructor */
    Bullet();
    /** Destructor */
    ~Bullet();
    
    /** Initialises variables
    * @param boolean for ownership, position (XY - int), and speed (int)
    */
    void init(bool canon, int x, int y, int speed);
    
    /** Draws contents to LCD
    * @param bitmap and position values (bit, int)
    */
    void draw(N5110 &lcd);
    
    /** Updates position
    * @param vector and position values (Vector2D, int)
    */
    void update();
    
    /** Gets velocity
    * @return current velocity (Vector2D)
    */
    Vector2D get_velocity();
    
    /** Gets position
    * @return current position (Vector2D)
    */
    Vector2D get_pos();
    
    /** Gets bullet ownership
    * @return boolean for bullet ownership
    */
    bool get_canon();
    
    //////// edit for final publish
    
private:
 
    Vector2D _velocity;
    int _width;
    int _height;
    int _x;
    int _y;
    bool _canon;
    int _speed;
};
#endif