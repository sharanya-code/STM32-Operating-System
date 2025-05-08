/*
 * k_task.h
 *
 *  Created on: Jan 5, 2024
 *      Author: nexususer
 *
 *      NOTE: any C functions you write must go into a corresponding c file that you create in the Core->Src folder
 */

#ifndef INC_K_TASK_H_
#define INC_K_TASK_H_
#include "common.h"


/************************************************
 *               DEFINITIONS
 ************************************************/


#define TID_DORMANT  -1
#define SHPR2 *(uint32_t*)0xE000ED1C //for setting SVC priority, bits 31-24
#define SHPR3 *(uint32_t*)0xE000ED20 //PendSV is bits 23-16

/************************************************
 *               TYPEDEFS
 ************************************************/

typedef unsigned int U32;
typedef unsigned short U16;
typedef char U8;

//Task ID type.
typedef unsigned int task_t;

//Task state
enum task_state {
	TASK_DORMANT = 0,
	TASK_READY = 1,
	TASK_RUNNING = 2,
	TASK_SLEEPING = 3
};

typedef struct task_control_block{
	void (*ptask)(void* args); //entry address
	task_t tid; //task ID
	U8 state; //task's state
	U16 stack_size; //stack size. Must be a multiple of 8
	//your own fields at the end
	U32 stack_high;
	U32* SP;
	U32* p_stack_mem; //pointer to address of dynamically allocated stack
	U32 remaining_sleep_time;
	U32 deadline; //a fixed amount of time (we need to store this value to update remaining time on yield)
	U32 remaining_time; //decrements every tick, is initially equal to the deadline
}TCB;


//Master struct containing all data for kernel functions.
typedef struct kernel_config_t {
	TCB TCBS[MAX_TASKS];
	U8 num_running_tasks;
	U8 is_running; //as bool 0 = False else true
	task_t running_task;
}KERNEL_CONFIG;

/************************************************
 *             GLOBAL VARS
 ************************************************/

extern KERNEL_CONFIG kernel_config;


/************************************************
 *              FUNCTION DEFS
 ************************************************/

/*
 * @brief:
 */
void osKernelInit(void);


/*
 * @brief: Hard
 */
int osCreateTask(TCB* task);


/*
 * @brief:
 */
int osKernelStart(void);

/*
 * @brief: Very Hard
 */
void osYield(void);

/*
 * @brief:
 */
int osTaskInfo(task_t TID, TCB* task_copy);

/*
 * @brief:
 */
task_t osGetTID (void);

/*
 * @brief:
 */
int osTaskExit(void);

void osSleep(int timeInMs);


void print_kernel_info(void);

void ContextSwitch(void);


void osPeriodYield();

int osSetDeadline(int deadline, task_t TID);

int osCreateDeadlineTask(int deadline, TCB* task);

#endif /* INC_K_TASK_H_ */
