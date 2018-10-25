/*
 * Simple program to flash the LEDs 
 *
 * Implemented using a time-triggered scheduler.
 *
 * DK - 08-June-2018
 */


#include <stdbool.h>
#include <stdint.h>
#include <scheduler.h>
#include <mbed.h>

/* Declare function prototypes */

/* Declare varaibles for the LEDs etc */

int main () {
  /* Initialise the LEDs */

  /* Initialise the scheduler. Ensure TT_SCHED_TICK_HZ gives 1 ms between ticks */

  /* Add tasks to the scheduler table */

  /* Start the scheduler */
  
  while (true) {
    /* Main application loop -- dispatch tasks */
  }
}


void led1ToggleTask(void) {
  /* Toggle the red LED on the K64F board */
}

void led2ToggleTask(void) {
  /* Toggle the green LED on the application board */
}

