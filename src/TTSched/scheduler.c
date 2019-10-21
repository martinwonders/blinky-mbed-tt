#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <cmsis.h>
#include <scheduler.h>

/* Variables managed by the scheduler */
static volatile uint32_t tickCount = 0;
static TCB_t schTasks[TT_SCHED_MAX_TASKS];

void SysTick_Handler(void) {
  /* Increment tickCount */
  tickCount++;
}

void schInit(void) {   // initialise the scheduler
  
  /* loop to set all TCBs in the task array to zeroes */
  uint8_t i;
  for (i = 0; i < TT_SCHED_MAX_TASKS; ++i) {
    schTasks[i].task = 0;
    schTasks[i].delay = 0;
    schTasks[i].period = 0;
  }
}

/* Here's the schAddTask function for free - nothing more to do here! */
void schAddTask(               // add a task to the task set
  task_t task,              // the task to add
  uint32_t delay,                // the delay in ms
  uint32_t period) {             // the period
  
  uint8_t i = 0;
  
  while (i < TT_SCHED_MAX_TASKS && schTasks[i].task != (task_t)0) {
    i += 1;
  }
  assert(i < TT_SCHED_MAX_TASKS);
  schTasks[i].task = task;
  schTasks[i].delay = delay;
  schTasks[i].period = period;
}

void schStart(void) {           // start ticking
  /* Configure the SysTick timer with the correct value 
   * to achieve TT_SCHED_TICK_HZ ticks per second
   */
  SysTick_Config(SystemCoreClock / TT_SCHED_TICK_HZ); 
}

void schDispatch(void) {        
  bool need_update = false;
  /* Check to see if we need to update the task array and run tasks 
   * Don't forget to protect the tickCount variable by disabling interrupts
   * while you check it. Enable interrupts again as soon as possible
   */ 
  __disable_irq();
  if (tickCount > 0) {
    need_update = true;
  }
  __enable_irq();
  
  if (need_update) {
    // Loop through task array
    for (uint8_t i = 0; i < TT_SCHED_MAX_TASKS; ++i) {
      // if the TCB entry is populated
      if ( schTasks[i].task != 0 ) {
        //if the delay field is 0
        if ( schTasks[i].delay == 0 ) {
          (*(schTasks[i].task))();			//run the task and
          schTasks[i].delay = schTasks[i].period;       //set the delay field from the period
        //otherwise decrement its delay field 
        } else {
          schTasks[i].delay--;
        }
      }
    }//end loop through task array
    /* Decrement the tickCount variable to show that we have handled
     * 1 tick. Check to see if we need to loop again through the task
     * array. Make sure that your use of the tickCount variable is protected.
    */ 
    __disable_irq();
    tickCount--;
    __enable_irq(); 
  }
  
  /* Indicate that the microcontroller should enter low-power mode */
  schSleep();
}

void schSleep(void) {         // go to sleep, if possible, to save power
  /* single line of code needed here */
  __WFI();
}

