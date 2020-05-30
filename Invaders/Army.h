#ifndef ARMY_H
#define ARMY_H

#include <vector>

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#include "Invader.h"

/** Army.h
* @brief Defines variables and methods for the invader army, instatiates invaders
* @author Helios A. Lyons
* @date April, 2020
*/
 
class Army
{
    
public:
    /** Constructor */
    Army();
    /** Destructor */
    ~Army();
    
    /** Initialises variables
    * @param value for invader vector (int), speed (int), boss (bool), and boss number (int)
    */
    void create_army(int rows, int columns, int speed, bool boss, int bossNum);
    
    //void move_army();
    
    /** Draws contents to LCD
    * @param bitmap and position values (bit, int)
    */
    void draw(N5110 &lcd);
    
    int _rows; // passed from main to Army to define the size of the invader vector
    int _columns;
    
    /** Returns end condition
    * @return returns end condition (boolean) and passes to battle.h
    */
    bool end();
    bool _end;
 
private:
    
    int _x;
    int _y;
    bool _boss;
    int _inc;
    
};
#endif