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

void led1ToggleTask(void);
void led2ToggleTask(void);


static DigitalOut red(LED_RED);
static DigitalOut green(LED_GREEN);

int main () {
  red = 0;
  green = 0;
  schInit();
  schAddTask(led1ToggleTask, 0, 500);
  schAddTask(led2ToggleTask, 500, 500);


  schStart();
  
  while (true) {
    schDispatch();
  }
}


void led1ToggleTask(void) {
  red = 1 - red;
}

void led2ToggleTask(void) {
  green = 1 - green;
}

