#include <gb/gb.h>
#include <stdio.h>
#include "spr_mainMan.c"
#include "gbt_player.h"
//Notice that banked values aren't included here. They're stated in the compiler (ALso note that you can't put .h files into the compiler)

//External function and variable to show how both are called into bank 0 from their original bank
extern uint8_t bankedvar;
extern void printthree(void);


//Global variables. Not relevant to banking the file I stole to modify was just set up illegally
int8_t playerLocation[2];
BYTE jumping;
int8_t gravity = -2;
uint8_t currentSpeedY;
uint8_t floorYPosition = 100;


//Music file saved in output.c; if you want more than 1 song then run the executable by yourself and then just rename them from output and include them that way
extern const unsigned char * const beautiful_garbage_Data[];


void performantdelay(uint8_t numloops){
//Tutorial said this is more space efficient than delay(). It happens to play nicer with music files too
    uint8_t i;
    for (i=0; i < numloops; i++){
        wait_vbl_done();
    }
}


int8_t wouldHitSurface(uint8_t projectedYPosition){
//Check collision with static floor position
    if (projectedYPosition >= floorYPosition){
        return floorYPosition;
    }
    else{
        return -1;
    }
}


void jump(uint8_t spriteid, uint8_t spriteLocation[2]){
//Character jump function
    int8_t possibleSurfaceY;

    if(jumping == 0){
        jumping = 1;
        currentSpeedY = 10;
    }

    //Every timet his function loops, y speed decelerates
    currentSpeedY = currentSpeedY + gravity;

    spriteLocation[1] = spriteLocation[1] - currentSpeedY; //y location go up

    possibleSurfaceY = wouldHitSurface(spriteLocation[1]);

    if(possibleSurfaceY > -1){
        jumping = 0;
        move_sprite(spriteid, spriteLocation[0], possibleSurfaceY);
    }
    else{
        move_sprite(spriteid, spriteLocation[0], spriteLocation[1]);
    }

    move_sprite(spriteid, spriteLocation[0], spriteLocation[1]);
}



int main(void){

    //Initialize sound banks
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    //Setting up tiles used in game
    set_sprite_data(0,3, mainMan);
    set_sprite_tile(0,0);

    playerLocation[0] = 10;
    playerLocation[1] = floorYPosition;
    jumping = 0;
    move_sprite(0,playerLocation[0], playerLocation[1]);

    DISPLAY_ON;
    SHOW_SPRITES;

    disable_interrupts();

    //Imports music and plays it constantly in the background
    gbt_play(beautiful_garbage_Data, 2, 7);
    gbt_loop(1);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();

    while (1){

        printf("%d", bankedvar); //This banked variable requires no banking. Just an extern call

        SWITCH_ROM(2); //This banked function requires a change to the appropriate bank (I've set it to bank 2 on th etop of the bank 2 page)
        printthree();
        SWITCH_ROM(0);
        wait_vbl_done();
        if((joypad() & J_A) || jumping == 1){
            jump(0, playerLocation);
        }
        if(joypad() & J_LEFT){
            playerLocation[0] = playerLocation[0] - 2;
            move_sprite(0,playerLocation[0],playerLocation[1]);
        }
        if(joypad() & J_RIGHT){
            playerLocation[0] = playerLocation[0] + 2;
            move_sprite(0,playerLocation[0],playerLocation[1]);
        }
        performantdelay(1); //For music, delay or performant delay must be set. Even if it's just 1. Otherwise you will get really ugly music glitches
        gbt_update();

    }
}