#include "Canon.h"
#include "Bitmap.h"
#include <vector>

Canon::Canon()
{
 
}
 
Canon::~Canon()
{
 
}
 
void Canon::init(int y) // initialise canon at a certain Y position
{
    _y = y;  // y value is fixed
    _x = WIDTH/2 - _width/2; // x depends on width of screen and width of canon
    _height = 3; // initialise all accessible variables
    _width = 5;
    _speed = 1;
}
 
void Canon::draw(N5110 &lcd) // bitmap for canon sprite
{
    static int sprite_data[] = {
    0,0,1,0,0,
    1,0,1,0,1,
    1,1,1,1,1
    };
    Bitmap canon_sprite(sprite_data, _height, _width);
    canon_sprite.render(lcd, _x,_y);
}

Vector2D Canon::get_pos()
{
    Vector2D p = {_x,_y};
    return p;
}

int Canon::get_life()
{
    return _life;
}

int Canon::remove_life()
{
    _life--;
    return _life;
}

int Canon::reset_life()
{
    _life = 3;
    return _life;
}

void Canon::update(Direction d,float mag) // take input from the magnometer and pad direction
{
    _speed = int(mag*10.0f);

    if (d == E) {
        _x+=_speed;
    } else if (d == W) {
        _x-=_speed;
    }

    // check the X origin to ensure that canon doesn't go off screen
    if (_x < 1) {
        _x = 1;
    }
    if (_x > WIDTH - _width - 1) {
        _x = WIDTH - _width - 1;
    }
}

int Canon::get_width()
{
    return _width;
}

int Canon::get_height()
{
    return _height;
}