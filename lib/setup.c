#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./validation.h"
#include "./setup.h"
#include "./schalg.h"
#include "./input-utils.h"

// maximum length of user input constant
#define MAX_ALG_CHARS 8

process *create_process_pairs(uint8_t process_count, char *argv[]) {
    // create process ptr array in heap memory
    process *processes = malloc(process_count * sizeof(process));
    // check if malloc was successful -> learned from https://www.codingame.com/playgrounds/14589/how-to-play-with-pointers-in-c/dynamic-memory-allocation 
    if(processes == NULL) {
        system("clear");
        printf("Couldn't allocate memory successfully, please try again.");
        close_program();
    }

    // create process items using argv & add to processes
    int count = 0;
    for(int i = 0; i < process_count * 2; i += 2) {
        // create char from int for process id
        char c = (count + 1) + '0';
        // take two items from argv & assign them into arrival_t & burst_t, then validate
        uint32_t arrival_t = validate_arrival(atoi(argv[i+1]));
        uint32_t burst_t   = validate_burst(atoi(argv[i+2]));

        process p = {{'P', c, '\0'}, arrival_t, burst_t, 0, 0, 0, 0, burst_t, 0};
        // turnaround_t & response_t will be assigned later, when the process is complete.
        processes[count] = p;
        count++;
    }
    return processes;
}

void menu() {
    while (1) {
        // print algorithm options
        printf("--------------------------------------------\n");
        printf("Oisin Murphy CA1 - CPU Scheduling Algorithms\n");
        printf("--------------------------------------------\n");
        printf(" OPTIONS                                    \n");
        printf(" -    fifo -> First in, First out.          \n");
        printf(" -     sjf -> Shortest Job First.           \n");
        //printf(" -    stcf -> Shortest Time-to-Completion First .\n");
        printf(" -      rr -> Round Robin.                  \n\n");
        printf(" - compare -> Compare response & turnaround times of each algorithm.\n");
        printf("--------------------------------------------\n");
        printf(" - Enter 'quit' to exit the program.        \n");
        printf("--------------------------------------------\n");
        printf("Please input your desired option by name > ");

        // -- register user input --
        char choice[MAX_ALG_CHARS];

        // validate user input
        // first, apply limits / validate / clear buffer 
        fgets_str_stdin(choice, MAX_ALG_CHARS);
        system("clear");
        // check input commands
        extern process *processes;
        extern uint8_t process_count;
        // case insensitive because I honestly hate meaninglessly case sensitive inputs >:I
        if(strcasecmp(choice, "quit") == 0) {
            break;
        }
        else if(strcasecmp(choice, "fifo") == 0) {
            fifo_alg(processes, process_count, 1);
        }
        else if(strcasecmp(choice, "sjf") == 0) {
            sjf_alg(processes, process_count, 1);
        }
        // else if(strcasecmp(choice, "stcf") == 0) {
        //     stcf_alg(processes, process_count, 1);
        // }
        else if(strcasecmp(choice, "rr") == 0) {
            rr_alg(processes, process_count, 1);
        }
        else if(strcasecmp(choice, "compare") == 0) {
            compare(processes, process_count);
        }
        else {
            // Tell the user off for not putting in a valid input
            printf("PLEASE INPUT ONE OF THE OPTIONS LAID OUT BEFORE YOU!\n");
        }
    }
    system("clear");
    printf("Exiting program...\n");
    close_program();
}

void close_program() {
    // deallocate heap memory
    extern process *processes;
    free(processes);
	processes = NULL;

    exit(0);
}