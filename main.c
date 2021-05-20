#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "./lib/setup.h"
#include "./lib/validation.h"
#include "./lib/schalg.h"
#include "./lib/input-utils.h"

// GLOBALS
process *processes;       // array of process ptrs
uint8_t  process_count;   // number of processes

int main(int argc, char *argv[]) {
    // --- SETUP ---
    system("clear");
    // validate arguments - decrement argc by one to exclude run command argument
    validate_args(argc - 1);
    // assign process count & structure array
    process_count = (argc - 1) / 2;
    processes = create_process_pairs(process_count, argv);
    // enter menuing system
    menu();

    return 0;
}