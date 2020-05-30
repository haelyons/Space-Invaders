/* 
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds
2019/20

Name: Helios Ael Lyons
Username: mc18hal
Student ID Number: 201239214
Date: 24th March 2020
*/

/** Main
* @brief Start screen, menu, and game loop
* @author Helios A. Lyons
* @date March, 2020
*/

///////// pre-processor directives ////////
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "Bitmap.h"
#include "Battle.h"

// structs
struct UserInput {
    Direction d;
    float mag;
};

// objects
N5110 lcd;
Gamepad pad;
Battle battle;
Canon player;

Timer playTime;

// prototypes
void init();
void update_game(UserInput input);
void render();
void welcome();
void wave(int n);
void game(Gamepad &pad);
void menu(Gamepad &pad);

// functions
int main()
{        
    //lcd.clear();
    init(); // initialise LCD and gamepad
    
    welcome(); // display welcome screen
    
    Menu_Point: // goto point after victory/defeat
    menu(pad);
    
    battle.reset_life(); // start player lives at 3
    int n = 0;
    
    while (n < 9) {
            n++;
            if (battle.life() < 1) { break; } // break condition for when player dies
            switch(n) {
                case 1: // initialise entities for the wave
                    battle.init(1,3,4,3,0,3); // row,column,speed,firing interval,boss,bossNum
                    battle.clock(pad); // start the invader firing pattern
                    wave(n); // print wave #
                    playTime.start(); // start timer before game starts
                    game(pad); // start the main game loop
                    playTime.stop(); // stop timer
                break;
                
                case 2:
                    battle.init(3,3,4,3,0,3); // init function is used this way to provide
                    battle.clock(pad); // easy options to vary invader formation and number
                    wave(n); // in wave
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 3:
                    battle.init(1,1,3,2,1,1);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 4:
                    battle.init(2,3,3,3,0,1);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 5:
                    battle.init(3,3,3,3,0,1);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 6:
                    battle.init(1,1,2,1,1,2);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 7:
                    battle.init(3,4,2,3,0,2);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 8:
                    battle.init(3,6,3,2,0,2);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                
                case 9:
                    battle.init(1,1,1,1,1,3);
                    battle.clock(pad);
                    wave(n);
                    playTime.start();
                    game(pad);
                    playTime.stop();
                break;
                } // end of switch statement
        }
        
        if (battle.life() < 1) { // if player failed display game over
            lcd.printString("Game Over",16,2);
            lcd.refresh();
            wait(8.0);
            goto Menu_Point; // return to main menu after wait
            }
        else { // if waves are completed display time and victory screen
            lcd.printString("You won!",16,2);
            char buffer4[14];
            float time = sprintf(buffer4,"Time:%.2f",playTime.read());
            lcd.printString(buffer4,16,3);
            lcd.refresh();
            wait(8.0);
            goto Menu_Point; // return to main menu
            }
}

void init() // initialises LCD and Gamepad
{
    lcd.init();
    pad.init();
}

void render() {  // clears screen and re-draws content (+ current lives left) 
    lcd.clear(); // called in the main game() loop
    battle.draw(lcd);
    lcd.refresh();
    
    char buffer[4];
    int lives = sprintf(buffer,"%2d",battle.life()); 
    lcd.printString(buffer,0,5);
    lcd.refresh();
}

void game(Gamepad &pad) { // main game loop, reads input and updates bullet / canon positions
    while (1) { 
        int fps = 6;
        battle.read_input(pad);
        battle.update(pad);
        render();
        wait(1.0f/fps);
        if (battle.end() || battle.life() < 1 ) { break; }
        }
    lcd.clear();
    }
   
void wave(int n) {  // prints wave number and time taken so far
        lcd.clear();
        char buffer[14];
        char buffer3[3];
        int number = sprintf(buffer,"Wave%2d",n);
        float time = sprintf(buffer3,"%.2f",playTime.read());
        lcd.printString(buffer,24,1);
        lcd.printString(buffer3,27,2);
        
        lcd.refresh();
        wait(3.0); 
    }

void welcome() { // bitmap logo and title for start screen
    static int logo[] = {
    0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
    0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
    0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
    1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,
    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,
    0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0
    };
    
    Bitmap canon_sprite(logo, 16, 22);
    canon_sprite.render(lcd,30,4);
    
    lcd.printString("Space Invaders",0,3);
    lcd.printString("Press Start",8,4);
    lcd.refresh();
    
    while (pad.start_pressed() == false) { // LEDs flash until start is pressed
        lcd.setContrast(pad.read_pot1());
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
    }
}

void menu(Gamepad &pad) {
    while(1) {
        pad.reset_buttons();
        lcd.clear();
        lcd.printString("(A) Play",0,1);
        lcd.printString("(X) How To",0,2);
        lcd.printString("(B) Credits",0,3);
        lcd.refresh();
    
        if (pad.X_pressed()) {
            lcd.clear();
            lcd.printString("Press A",0,2);
            lcd.printString("to shoot",0,3);
            lcd.refresh();
            wait(5.0);
            
            lcd.clear();
            lcd.printString("Use the",0,1);
            lcd.printString("joystick to",0,2);
            lcd.printString("move left",0,3);
            lcd.printString("or right",0,4);
            lcd.refresh();
            wait(5.0);
            
            lcd.clear();
            lcd.printString("Remaining ",0,1);
            lcd.printString("lives are on",0,2);
            lcd.printString("the bottom",0,3);
            lcd.printString("left",0,4);
            lcd.refresh();
            wait(5.0);
            
            lcd.clear();
            lcd.printString("Elapsed time",0,1);
            lcd.printString("is shown at",0,2);
            lcd.printString("each wave",0,3);
            lcd.printString("interval",0,4);
            lcd.refresh();
            wait(5.0);
            }
        else if (pad.A_pressed()) {
            return;
            }
        else if (pad.B_pressed()) {
            lcd.clear();
            lcd.printString("Game by",0,2);
            lcd.printString("H.A. Lyons",0,3);
            lcd.refresh();
            wait(5.0);
            }
    }
    
} 