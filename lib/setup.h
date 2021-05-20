#pragma once

// struct for holding process data
// could use uint8_t for struct for this CA, but idk am conflicted. Conisder CA use or real life use?
typedef struct {
    char id[3]; 
    uint32_t arrival_t;     // time at which the process arrives to the cpu
    uint32_t burst_t;       // estimated uninterrupted time for the process to complete
    uint32_t completion_t;  // actual time of process completion
    uint32_t first_turn_t;  // time when the process first starts executing
    uint32_t response_t;    // time between process arrival and first executing
    uint32_t turnaround_t;  // time taken for process to finish
    uint32_t remaining_t;   // for round robin so we don't destroy burst_t
    _Bool    arrived;
} process;

//create process array * return pointer (use malloc)
process *create_process_pairs(uint8_t process_count, char *argv[]);

// menu loop to ensure user returns to menu after going down a path
void menu();

// closing program procedure - free memory
void close_program();