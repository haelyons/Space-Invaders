#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

#include "Bullet.h"
#include "Canon.h"
 
Bullet::Bullet()
{

}
 
Bullet::~Bullet()
{

}
 
void Bullet::init(bool canon, int x, int y, int speed)
{
    _canon = canon; // define ownership – canon, or invaders
    _x = x;
    _y = y;
    _speed = speed; // speed – using to update velocity
    
    Direction d;
    
    if (_canon == true) { // set direction based on ownership
        d = N;
        _width = 1;
        _height = 2;
        _velocity.x = 0; // only moves on y axis for both canon and invader
        _velocity.y = -speed;
       }
    else {
        d = S;
        _width = 1;
        _height = 1;
        _velocity.x = 0;
        _velocity.y = speed;
        }
}
 
void Bullet::draw(N5110 &lcd)
{
    if (_canon == true) { // square bullets for canon
        lcd.drawRect(_x,_y,_width,_height,FILL_BLACK);
        }
    else { // 'round' bombs for invaders –– didn't turn out round
        lcd.drawCircle(_x,_y,_width,FILL_BLACK); // but I like the aesthetic
        }
}
 
void Bullet::update() // update positions using velocity
{
    _x += _velocity.x;
    _y += _velocity.y;
}
 
Vector2D Bullet::get_velocity() // retrieve velocities
{
    Vector2D v = {_velocity.x,_velocity.y};
    return v;
}

Vector2D Bullet::get_pos() // get x and y positions (for collision testing)
{
    Vector2D p = {_x,_y};
    return p;
}

bool Bullet::get_canon() // return ownership
{
    return _canon;
}