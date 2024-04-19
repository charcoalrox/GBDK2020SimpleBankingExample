#pragma bank 2

#include <gb/gb.h>
#include <stdio.h>

uint8_t bankedvar = 5;

void printthree(void){
    printf("3\n");
}