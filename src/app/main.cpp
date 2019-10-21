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
void led1ToggleTask(void);
void led2ToggleTask(void);

/* Declare varaibles for the LEDs etc */
DigitalOut led1(LED1);
DigitalOut rled_mbed(D5);
DigitalOut gled_mbed(D9);

int main () {
  /* Initialise the LEDs */
  led1 = 1;
  rled_mbed = 1;
  gled_mbed = 1;

  /* Initialise the scheduler. Ensure TT_SCHED_TICK_HZ gives 1 ms between ticks */
  schInit();

  /* Add tasks to the scheduler table */
  schAddTask(led1ToggleTask, 0, 500);
  schAddTask(led2ToggleTask, 500, 500);

  /* Start the scheduler */
  schStart();
  
  while (true) {
    /* Main application loop -- dispatch tasks */
    schDispatch();
  }
}


void led1ToggleTask(void) {
  /* Toggle the red LED on the K64F board */
  led1 = !led1;
}

void led2ToggleTask(void) {
  /* Toggle the green LED on the application board */
  gled_mbed = !gled_mbed;
}

