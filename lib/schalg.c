#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./setup.h"
#include "./schalg.h"

// time quantum of 5 for rr
#define TIME_QUANTUM 5

// Scheduling algorithm fn implementation file

void print_results(char *alg_name, process *queue, uint8_t process_count, _Bool show_timeline) {
    float avg_response   = 0;
    float avg_turnaround = 0;

    if(show_timeline) {     // standard printout
        printf("%s Timeline:\n-------------------------------\n", alg_name);
        for(uint8_t i = 0; i < process_count; ++i) {
            printf("T = %d %s\n", queue[i].first_turn_t, queue[i].id);
            avg_response   += queue[i].response_t;
            avg_turnaround += queue[i].turnaround_t;
        }
    }
    else {                  // printout for compare
        printf("%s Averages:\n", alg_name);
        for(uint8_t i = 0; i < process_count; ++i) {
            avg_response   += queue[i].response_t;
            avg_turnaround += queue[i].turnaround_t;
        }
    }
    printf("-------------------------------\n");
    printf("Average Response Time   : %.2f \n", avg_response   / process_count);
    printf("Average Turnaround Time : %.2f \n", avg_turnaround / process_count);
    printf("-------------------------------\n\n");
}

void (print_rr_resultsprocess **queue, uint8_t queue_size, uint8_t process_count, uint8_t times[], _Bool show_timeline) {
    float avg_response   = 0;
    float avg_turnaround = 0;

    if(show_timeline) {     // standard printout
        printf("Round Robin Timeline:\n-------------------------------\n");
        for(uint8_t i = 0; i < queue_size; ++i) {
            printf("T = %d %s\n", times[i], queue[i]->id);
        }
    }
    else {                  // printout for compare
        printf("Round Robin Averages:\n");
    }

    // get averages - use process list so we only get each once
    extern process *processes;
    for(uint8_t i = 0; i < process_count; ++i) {
        avg_response   += processes[i].response_t;
        avg_turnaround += processes[i].turnaround_t;
    }

    printf("-------------------------------\n");
    printf("Average Response Time   : %.2f \n", avg_response   / process_count);
    printf("Average Turnaround Time : %.2f \n", avg_turnaround / process_count);
    printf("-------------------------------\n\n");
}


void reset_processes(process *processes, uint8_t process_count) {
    for(int i = 0; i < process_count; ++i) {
        processes[i].completion_t = 0;
        processes[i].first_turn_t = 0;
        processes[i].response_t   = 0;
        processes[i].turnaround_t = 0;
        processes[i].remaining_t  = processes[i].burst_t;
        processes[i].arrived      = 0;
    }
}

process *get_longest_process(process *processes, uint8_t process_count) {
    process *p = &processes[0];
    for(uint8_t i = 1; i < process_count; ++i) {
        if(processes[i].burst_t > p->burst_t) {
            p = &processes[i];
        }
    }
    return p;
}

process **resize_queue(process **queue, int8_t items) {
    // double the size of the queue
    process **new_queue = realloc(queue,(items * 2) * sizeof(process));
    // if realloc fails, create a new queue of a bigger size & copy into it
    if(new_queue == NULL) {
        new_queue = malloc((items * 2) * sizeof(process));
        if(new_queue == NULL) {
            printf("Could not allocate memory successfully, please try again.");
            close_program();
        }
        // copy queue items to new queue
        for(int i = 0; i < items; ++i) {
            new_queue[i] = queue[i];
        }
        // now that we have a new queue, free up the old one
        free(queue);
	    queue = NULL;
    }
    return new_queue;
}

void fifo_alg(process *processes, uint8_t process_count, _Bool show_timeline) {
    reset_processes(processes, process_count);
    // no need for queue, assume processes arrive in order of arrival
    // if not, need a sort method?
    uint32_t current_time = 0;
    for(uint8_t i = 0; i < process_count; ++i) {
        processes[i].first_turn_t = current_time;   // set arrival time
        current_time += processes[i].burst_t;       // increment time scale by burst time of process - FIFO only 
        processes[i].completion_t = current_time;   // set completion time of process
        processes[i].remaining_t  = 0;
        // Set response & turnaround times
        processes[i].response_t   = processes[i].first_turn_t - processes[i].arrival_t;     // time taken between time of arrival and time of first execution.
        processes[i].turnaround_t = processes[i].completion_t - processes[i].arrival_t;     // time taken to complete the process.
    }
    //build EXECUTION timeline (in data format or just text?)
    print_results("FIFO", processes, process_count, show_timeline);
}

void sjf_alg(process *processes, uint8_t process_count, _Bool show_timeline) {
    reset_processes(processes, process_count);
    // go through tasks and order them, add references to queue, then print out
    process queue[process_count];

    // start first task
    uint32_t current_time = 0;
    
    process *longest_p = get_longest_process(processes, process_count);
    process *p;
    for(uint8_t i = 0; i < process_count; ++i) {
        p = longest_p;
        for(uint8_t j = 0; j < process_count; ++j) {
            // find shortest burst time & add to queue
            if(processes[j].arrival_t <= current_time) {        // get all who have arrived
                if(processes[j].burst_t < longest_p->burst_t && processes[j].completion_t == 0) {   // of those, find the one that will finish first
                    p = &processes[j];
                }
            }
        }
        p->arrived = 1;
        p->first_turn_t = current_time;
        current_time += p->burst_t;
        p->completion_t = current_time;
        // Set response & turnaround times
        p->response_t   = p->first_turn_t - p->arrival_t;
        p->turnaround_t = p->completion_t - p->arrival_t;
        // add pointer to process to queue
        queue[i] = *p;
    }
    print_results("SJF", queue, process_count, show_timeline);
    // set ptrs to null before ending
    longest_p = NULL;
    p = NULL;
}

// void stcf_alg(process *processes, uint8_t process_count, _Bool show_timeline) {
//     reset_processes(processes, process_count);
//     process queue[process_count];

//     uint32_t current_time = 0;

//     //this one hurted my head ;-;

//     print_results("STCF", queue, process_count, show_timeline);


//     // reduce burst time

//     // play first task
//     // when new task appears, stop, and compare time remaining
//     // play task that will finish first
//     // repeat
// }

void rr_alg(process *processes, uint8_t process_count, _Bool show_timeline) {
    // GOD THIS ONE WAS A MESS, SORRY IN ADVANCE
    reset_processes(processes, process_count);
    // create queue with malloc because we might need to resize later
    process **queue = malloc((process_count * 2) * sizeof(process));
    if(queue == NULL) {
        printf("Could not allocate memory successfully, please try again.");
        return;
    }

    // set up
    uint8_t  queue_size     = 1;
    uint8_t  finished_ps    = 0;                        // no. of finished processes
    uint32_t max_queue_size = process_count * 2;        
    uint32_t current_time   = 0;
    uint8_t  time_count     = 0;
    uint8_t  arrived_ps     = 1;
    uint8_t  times[255];
    times[0] = 0;
    queue[0] = &processes[0];
    queue[0]->arrived = 1;

    while(1) {
        // elapse time quantum with current process
        times[time_count] = current_time;
        uint8_t current_p = time_count;
        // set first turn if first turn isn't assigned
        if(queue[current_p]->first_turn_t == 0 && strcmp(queue[current_p]->id, "P1") != 0) {
            queue[current_p]->first_turn_t = current_time;
        }

        // Update Process time remaining by decrementing time quantum
        if(queue[current_p]->remaining_t > TIME_QUANTUM) {
            current_time += TIME_QUANTUM;
            queue[current_p]->remaining_t -= TIME_QUANTUM;
        }
        else {
            // finish process, set remaining_t to 0 and calc response & turnaround time
            current_time += queue[current_p]->remaining_t;
            queue[current_p]->completion_t = current_time;
            queue[current_p]->remaining_t  = 0;
            queue[current_p]->response_t   = queue[current_p]->first_turn_t - queue[current_p]->arrival_t;
            queue[current_p]->turnaround_t = queue[current_p]->completion_t - queue[current_p]->arrival_t;
            finished_ps++;
        }

        // check if any processes have arrived that have not arrived prior, if so add them to queue
        if(arrived_ps < process_count) {
            for(int8_t i = 0; i < process_count; ++i) {
                if(processes[i].arrival_t <= current_time && processes[i].arrived == 0) {   // if process arrives during the time quantum timeframe & hasn't arrived yet
                    queue[queue_size] = &processes[i];
                    queue[queue_size]->arrived = 1;
                    queue_size++;
                    arrived_ps++;
                    // check if i need to resize queue
                    if(queue_size >= max_queue_size) {
                        queue = resize_queue(queue, queue_size);
                        max_queue_size *= 2;
                    }
                }
            }
        }

        // if current process has time remaining, add to end of the queue
        if(queue[current_p]->remaining_t != 0) {
            queue[queue_size] = queue[current_p];
            queue_size++;
            // check if i need to resize queue
            if(queue_size >= max_queue_size) {
                queue = resize_queue(queue, queue_size);
                max_queue_size *= 2;
            }
        }
        
        // break loop if all processes are finished
        if(finished_ps >= process_count) {
            break;
        }
        time_count++;
    }
    print_rr_results(queue, queue_size, process_count, times, show_timeline);
    // deallocate queue when ending
    free(queue);
	queue = NULL;
}

void compare(process *processes, uint8_t process_count) {
    fifo_alg(processes, process_count, 0);
    sjf_alg(processes, process_count, 0);
    //stcf_alg(processes, process_count, 0);
    rr_alg(processes, process_count, 0);
}