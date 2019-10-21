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
#include "C12832.h"
#include <stdio.h>
#include <MMA7660.h>
#include <LM75B.h>

/* Declare function prototypes */
void led1ToggleTask(void);
void led2ToggleTask(void);
void readPots(void);
char getJoyStick();
void readAccs(void);
void readTemp(void);
void JoyStickResponse(void);

/* Declare varaibles for the LEDs etc */
DigitalOut led1(LED1);
DigitalOut rled_mbed(D5);
DigitalOut gled_mbed(D9);
DigitalIn  js_down(A3);
DigitalIn  js_left(A4);
DigitalIn  js_centre(D4);
DigitalIn  js_up(A2);
DigitalIn  js_right(A5);
MMA7660    acc(D14,D15);
LM75B      temperature(D14,D15);

 
C12832 lcd(D11, D13, D12, D7, D10);
AnalogIn pot1(A0);
AnalogIn pot2(A1);
PwmOut   buzzer(D6);

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
  schAddTask(readPots, 0,250);
  schAddTask(readAccs, 0,50);
  schAddTask(readTemp, 0,750);
  schAddTask(JoyStickResponse, 0,100);

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

void readPots(void){
  //lcd.cls();
  float p1, p2;
  p1 = pot1.read();
  p2 = pot2.read();
  lcd.locate(0,0);
  lcd.printf("Pot1 = %0.2f", p1);
  lcd.locate(64,0);
  lcd.printf("Pot2 = %0.2f", p2);
  
}

void JoyStickResponse(void){
  char status;
  status = getJoyStick();
  lcd.locate(0,8);
  lcd.printf("Joy stick: %c", status);
  if (status == 'L') {
    buzzer.period(0.00227);
    buzzer.write(0.50);
   } else {
     buzzer.write(0);
   }
}

void readAccs(void){
  //lcd.cls();
  float accel_val[3];
  accel_val[0] = acc.x();
  accel_val[1] = acc.y();
  accel_val[2] = acc.z();
  lcd.locate(0,16);
  lcd.printf("x = %0.2f y = %0.2f z = %0.2f", 
                      accel_val[0], accel_val[1], accel_val[2]);
}

void readTemp(void){
  //lcd.cls();
  float temp;
  temp = temperature.read();
  lcd.locate(55,8);
  lcd.printf("temp = %02.2f", temp);
}

char getJoyStick()
{
    char status = '-';
    if (js_down == 1) {
      status = 'D';
    } else if (js_up == 1) {
      status = 'U';
    } else if (js_left == 1) {
      status = 'L';
    } else if (js_right == 1) {
      status = 'R';
    } else if (js_centre == 1) {
      status = 'C';
    }
    return status;
}

