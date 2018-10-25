#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <cmsis.h>
#include <scheduler.h>

/* Variables managed by the scheduler */
static volatile uint32_t tickCount = 0;
static schTCB_t schTasks[TT_SCHED_MAX_TASKS];

void SysTick_Handler(void) {
  /* Increment tickCount */
}

void schInit(void) {   // initialise the scheduler
  
  /* loop to set all TCBs in the task array to zeroes */
}

/* Here's the schAddTask function for free - nothing more to do here! */
void schAddTask(               // add a task to the task set
  pVoidFunc_t task,              // the task to add
  uint32_t delay,                // the delay in ms
  uint32_t period) {             // the period
  
  uint8_t i = 0;
  
  while (i < TT_SCHED_MAX_TASKS && schTasks[i].task != (pVoidFunc_t)0) {
    i += 1;
  }
  assert(i < TT_SCHED_MAX_TASKS);
  schTasks[i].task = task;
  schTasks[i].delay = delay + 1;
  schTasks[i].period = period;
}

void schStart(void) {           // start ticking
  /* Configure the SysTick timer with the correct value 
   * to achieve TT_SCHED_TICK_HZ ticks per second
   */ 
}

void schDispatch(void) {        

  /* Check to see if we need to update the task array and run tasks 
   * Don't forget to protect the tickCount variable by disabling interrupts
   * while you check it. Enable interrupts again as soon as possible
   */ 

    /* Loop if update is needed */
      /* Loop through task array
       * if the TCB entry is populated
       * decrement its delay field 
       * if the delay field is now 0, run the task and
       * reset the value of the delay field from the period
       * end loop through task array
       */
    /* end loop if update is needed */

    /* Decrement the tickCount variable to show that we have handled
     * 1 tick. Check to see if we need to loop again through the task
     * array. Make sure that your use of the tickCount variable is protected.
     */ 
  }
  /* Indicate that the microcontroller should enter low-power mode */
}

void schSleep(void) {         // go to sleep, if possible, to save power
  /* single line of code needed here */
}

