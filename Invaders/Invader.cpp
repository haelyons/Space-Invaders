#include "Invader.h"
#include "Bitmap.h"
#include <vector>

Invader::Invader()
{
}
 
Invader::~Invader()
{
}
 
void Invader::init(int sprite, int hitpoints, int boss)
{    
    _height = 8; // set invader accessible variables
    _width = 8; // height is the same for normal invaders
    _death = false; // changed in drawn statement for bosses
    _sprite = sprite;
    _hitpoints = hitpoints;
}
 
void Invader::draw(N5110 &lcd)
{
    // classic Space Invader sprites made into a bitmap    
    static int inv1_resize_data[] = {
    0,1,0,0,0,0,1,0, // shrunk from original design (used on start screen)
    0,0,1,0,0,1,0,0, // to fit better on LCD
    0,0,1,1,1,1,0,0,
    0,1,0,1,1,0,1,0,
    1,1,1,1,1,1,1,1,
    1,0,1,1,1,1,0,1,
    1,0,1,0,0,1,0,1,
    0,0,0,1,1,0,0,0
    };
    
    static int inv2_resize_data[] = {
    0,1,0,0,0,0,1,0, 
    0,0,1,0,0,1,0,0, 
    1,0,1,1,1,1,0,1,
    1,1,0,1,1,0,1,1,
    0,1,1,1,1,1,1,0,
    0,0,1,0,0,1,0,0,
    0,1,0,0,0,0,1,0,
    1,0,0,0,0,0,0,1
    };
    
    static int inv3_resize_data[] = {
    0,0,0,1,1,0,0,0, 
    0,0,1,1,1,1,0,0, 
    0,1,0,1,1,0,1,0,
    1,1,0,1,1,0,1,1,
    0,1,1,1,1,1,1,0,
    0,0,1,0,0,1,0,0,
    0,1,0,1,1,0,1,0,
    1,0,1,0,0,1,0,1
    };
    
    static int boss1_data[] = {
    0,0,0,1,0,0,0,0,0,0,0, // Boss 1: Astro
    0,0,0,0,1,0,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,1,1,1,0,0,0,0,
    0,0,1,1,1,1,1,1,1,0,0,
    0,1,1,1,1,1,1,1,1,1,0,
    0,1,0,0,1,1,1,0,0,1,0,
    0,1,0,0,1,1,1,0,0,1,0,
    1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,
    0,1,1,0,0,0,0,0,1,1,0,
    0,0,1,0,0,0,0,0,1,0,0,
    0,0,0,1,0,0,0,1,0,0,0,
    0,0,0,0,1,0,1,0,0,0,0
    };
    
    static int boss2_data[] = {
    0,0,1,1,1,0,0,1,1,1,0,0, // Boss 2: Wormling
    0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,0,0,1,1,1,1,0,0,1,0,
    0,1,0,1,1,1,1,1,1,0,1,0,
    0,0,1,0,0,1,1,0,0,1,0,0,
    0,0,1,0,0,1,1,0,0,1,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,1,1,1,1,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,1,
    0,1,1,1,0,0,0,0,1,1,1,0
    };
    
    static int boss3_data[] = {
    0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0, // Boss 3: Eater of Worlds
    0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,
    0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,
    1,1,1,1,0,0,0,1,0,1,0,0,0,1,1,1,1,
    0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,
    0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,
    0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,
    0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0
    };
    
    if (_sprite == 1 && _death == false) { // set conditions for draw function
        Bitmap invader1(inv1_resize_data,8,8); // only alive invaders are rendered
        invader1.render(lcd,_x,_y);
        }
    else if (_sprite == 2 && _death == false) {
        Bitmap invader2(inv2_resize_data,8,8);
        invader2.render(lcd,_x,_y);
        }
    else if (_sprite == 3 && _death == false) {
        Bitmap invader3(inv3_resize_data,8,8);
        invader3.render(lcd,_x,_y);
        }
    else if (_sprite == 4 && _death == false) {
        Bitmap boss1(boss1_data,14,11);
        boss1.render(lcd,_x,_y);
        _width = 11;
        _height = 14;
        }
    else if (_sprite == 5 && _death == false) {
        Bitmap boss2(boss2_data,10,12);
        boss2.render(lcd,_x,_y);
        _width = 10;
        _height = 12;
        }
    else if (_sprite == 6 && _death == false) {
        Bitmap boss3(boss3_data,11,17);
        boss3.render(lcd,_x,_y);
        _width = 17;
        _height = 11;
        }
    else if (_death == true) {printf("Alien is dead");}
    else {printf("Incorrect Sprite Value");}
}
    
int Invader::hit() // decrement invader hitpoints, and set death if at 0
{
    _hitpoints--;
    if (_hitpoints <= 0) {
        _death = true;
        }
    return _hitpoints;
}

bool Invader::get_death() // retrieve death state
{
    if (_hitpoints <= 0) {
        _death = true;
        }
    return _death;
}

Vector2D Invader::get_pos() 
{
    Vector2D pos = {_x,_y};
    return pos;
}

int Invader::get_sprite()
{
    return _sprite;
}

void Invader::set_pos(int x, int y) 
{
    _x = x;
    _y = y;
}

int Invader::get_width() 
{
    return _width;
}

int Invader::get_height()
{
    return _height;
}