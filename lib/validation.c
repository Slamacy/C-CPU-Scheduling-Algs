#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./validation.h"
#include "./setup.h"
// Validation fns & error handling fns implementation file

// VALIDATE ARGUMENT COUNT BEFORE MAKING PAIRS
void validate_args(uint8_t argc) {
    printf("arg count: %d\n", argc);
    if(argc == 0 || (argc % 2) == 1) {
        // print error message & exit
        printf("ERROR: Invalid number of arguments, please try again.\n");
        close_program();
    }
    printf("Valid number of arguments got!\n");
    //system("clear");
} 

// VALIDATE PROGRAM INPUTS
uint32_t validate_arrival(int32_t arrival_t) {
    if(arrival_t < 0) {
        printf("ERROR: Invalid arrival time input, please try again.\n");
        close_program();
    }
    return (uint32_t)arrival_t;
}

uint32_t validate_burst(int32_t burst_t) {
    if(burst_t <= 0) {
        printf("ERROR: Invalid burst time input, please try again.\n");
        close_program();
    }
    return (uint32_t)burst_t;
}
//