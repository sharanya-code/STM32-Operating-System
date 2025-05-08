#include "main.h"
#include <stdio.h>
#include "common.h"
#include "k_task.h"
#include "k_mem.h"


int i_test = 0;

int i_test2 = 0;


void TaskA(void *) {
	while(1)
	{
		printf("%d, %d\r\n", i_test, i_test2);
		osPeriodYield();
	}
}

void TaskB(void *) {
	while(1)
	{
		i_test = i_test + 1;
		osPeriodYield();
	}
}

void TaskC(void *) {
	while(1)
	{
		i_test2 = i_test2 + 1;
		osPeriodYield();
	}
}

void TaskD(void *) {

		printf("TaskD \r\n");

		printf(" Am i exiting 1 %d \r\n" , osTaskExit());


}
void TaskF(void *) {

		printf("TaskF \r\n");
		osTaskExit();


}
void TaskE(void *) {

		printf("TaskE \r\n");
		TCB st_mytask;
		st_mytask.stack_size = 16000;
		st_mytask.ptask = &TaskF;
		printf( "New task should be made 1 %d \r\n ", osCreateDeadlineTask(4, &st_mytask));

		osTaskExit();


}

int main_lab34(void)
{

  /* MCU Configuration: Don't change this or the whole chip won't work!*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* MCU Configuration is now complete. Start writing your code below this line */
  osKernelInit();
  k_mem_init();

  //in main
  TCB st_mytask;
  st_mytask.stack_size = 16000;
  st_mytask.ptask = &TaskD;
  printf( "TaskD 1 %d \r\n ", osCreateDeadlineTask(2, &st_mytask));
  st_mytask.ptask = &TaskE;

  printf( "Task E 1 %d \r\n ", osCreateDeadlineTask(4, &st_mytask));
  printf( "Task E failure -1 %d \r\n ", osCreateDeadlineTask(4, &st_mytask));

  osKernelStart();


//  osCreateDeadlineTask(4, &st_mytask);
//
//  st_mytask.ptask = &TaskB;
//  osCreateDeadlineTask(4, &st_mytask);
//
//  st_mytask.ptask = &TaskC;
//  osCreateDeadlineTask(12, &st_mytask);



  printf("back to main\r\n");
  while (1);
 }

//void Task1(void *) {
//   while(1){
//     printf("1\r\n");
//     for (int i_cnt = 0; i_cnt < 5000; i_cnt++);
//     osYield();
//   }
//}
//
//
//void Task2(void *) {
//   while(1){
//     printf("2\r\n");
//     for (int i_cnt = 0; i_cnt < 5000; i_cnt++);
//     osYield();
//   }
//}
//
//
//void Task3(void *) {
//   while(1){
//     printf("3\r\n");
//     for (int i_cnt = 0; i_cnt < 5000; i_cnt++);
//     osYield();
//   }
//}
//
//
//int main(void){
//	/* MCU Configuration: Don't change this or the whole chip won't work!*/
//
//	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//	HAL_Init();
//
//	/* Configure the system clock */
//	SystemClock_Config();
//
//	/* Initialize all configured peripherals */
//	MX_GPIO_Init();
//	MX_USART2_UART_Init();
//	/* MCU Configuration is now complete. Start writing your code below this line */
//	osKernelInit();
//	k_mem_init();
//
//	//in main
//
//	TCB st_mytask;
//	st_mytask.stack_size = STACK_SIZE;
//	st_mytask.ptask = &Task1;
//	osCreateTask(&st_mytask);
//
//
//	st_mytask.ptask = &Task2;
//	osCreateTask(&st_mytask);
//
//
//	st_mytask.ptask = &Task3;
//	osCreateTask(&st_mytask);
//
//	osKernelStart();
//
//	printf("back to main\r\n");
//	while (1);
//}
