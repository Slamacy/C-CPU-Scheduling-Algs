#pragma once

void print_results(char*, process*, uint8_t, _Bool);
// special print method for Round Robin algorithm
void print_rr_results(process**, uint8_t, uint8_t, uint8_t[], _Bool);

process *get_longest_process(process*, uint8_t);
process **resize_queue(process**, int8_t);

// reset parts of each process to 0 to stop cross-contamination of algorithms
void reset_processes(process*, uint8_t);

//all scheduling algorithms declared here
// First in, First out
void fifo_alg(process*, uint8_t, _Bool);
// Shortest Job First
void sjf_alg(process*, uint8_t, _Bool);
// Shortest Time-to-Completion First 
void stcf_alg(process*, uint8_t, _Bool);
// Round Robin
void rr_alg(process*, uint8_t, _Bool);
// Compare averages of all algorithms - dont print out timelines
void compare(process *processes, uint8_t process_count);