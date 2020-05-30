#ifndef CANON_H
#define CANON_H
 
#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

/** Canon.h
* @brief Defines variables and methods for the Canon.
* @author Helios A. Lyons
* @date April, 2020
*/
 
class Canon
{
public:
    /** Constructor */
    Canon();
    /** Destructor */
    ~Canon();
    
    /** Initialises variables
    * @param boolean for ownership, position (XY - int), and speed (int)
    */
    void init(int y);
    
    /** Draws contents to LCD
    * @param bitmap and position values (bit, int)
    */
    void draw(N5110 &lcd);
    
    /** Updates position
    * @param vector, position values (Vector2D, int), direction (char) and magnitude (float)
    */
    void update(Direction d,float mag);
     
    /** Gets current position
    * @return current position (Vector2D)
    */    
    Vector2D get_pos();
    
    /** Gets current lives
    * @return value for life (int)
    */   
    int get_life();
    
    /** Decrements current lives
    * @return decremented value of lives (int)
    */   
    int remove_life();
    
    /** Resets current lives
    * @return reset value of lives (int = 3)
    */  
    int reset_life();
    
    /** Returns canon width
    * @return width (int)
    */  
    int get_width();
    
    /** Returns canon height
    * @return height (int)
    */
    int get_height();
 
private:

    int _height;
    int _width;
    int _x;
    int _y;
    int _speed;
    int _life;
 
};
#endif