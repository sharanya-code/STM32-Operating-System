///* USER CODE BEGIN Header */
///**
// ******************************************************************************
// * @file           : main.c
// * @brief          : Main program body
// ******************************************************************************
// * @attention
// *
// * Copyright (c) 2023 STMicroelectronics.
// * All rights reserved.
// *
// * This software is licensed under terms that can be found in the LICENSE file
// * in the root directory of this software component.
// * If no LICENSE file comes with this software, it is provided AS-IS.
// *
// ******************************************************************************
// */
///* USER CODE END Header */
///* Includes ------------------------------------------------------------------*/
//#include "main.h"
//
//#include <stdio.h> //You are permitted to use this library, but currently only printf is implemented. Anything else is up to you!
//#include "stm32f4xx.h"
//#include "k_mem.h"
//#include "k_task.h"
//#include <stdlib.h> //for testing
//#include "string.h" //for testing
//
//// #define  ARM_CM_DEMCR      (*(uint32_t *)0xE000EDFC)
//// #define  ARM_CM_DWT_CTRL   (*(uint32_t *)0xE0001000)
//// #define  ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)
//
//// #define ITERATIONS 100
//// uint8_t s_data_string[1000] = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. N";
//// uint8_t* p_buffers[ITERATIONS];
//// uint8_t i_checksums[ITERATIONS];
//// uint32_t i_buffer_sizes[ITERATIONS];
//// uint32_t i_total_alloc_bytes = 0;
//
//// // uint8_t CalcChecksum(uint8_t* p_buffer, uint32_t i_buffer_size){
//// // 	uint8_t checksum = 0;
//// // 	for (int i = 0; i < i_buffer_size; i++){
//// // 		checksum = checksum ^ p_buffer[i];
//// // 	}
//// // 	return checksum;
//// // }
//
//// /**
////  * @brief  The application entry point.
////  * @retval int
////  */
//void SVC_Handler_Main(unsigned int *svc_args)
//{
//
//  unsigned int svc_number;
//
//  // Stack frame contains: R0, R1, R2, R3, R12, LR, PC, xPSR
//  // SVC number is the immediate value passed in the SVC instruction
//  // It can be found at the address of the PC (Program Counter) - 2
//  svc_number = ((char *)svc_args[6])[-2];
//
//  // Handle the system call based on the svc_number
//  // For demonstration, we'll just print the SVC number
//  printf("System Call Number: %u \r\n", svc_number);
//
//  switch (svc_number)
//  {
//  case 0:
//    __set_CONTROL(__get_CONTROL() & ~CONTROL_nPRIV_Msk);
//    break;
//  case 1:
//    os_kernel_start();
//    break;
//  }
//  return;
//}
//
//// void print_continuously(void)
//// {
////   while (1)
////   {
////     printf("Thread!\r\n");
////   }
//// }
//
//// void MemTask32(void *)
//// {
////   int *big_ptr = k_mem_alloc((1 << 15) - 20);
////   printf("big_ptr: %p\r\n", big_ptr);
//// }
//
//// void MemTask16(void *)
//// {
////   int *left = k_mem_alloc((1 << 14) - 20);
////   int *right = k_mem_alloc((1 << 14) - 20);
//
////   printf("left_ptr: %p\r\n", left);
////   printf("right_ptr: %p\r\n", right);
////   osTaskExit();
//// }
//
//// void MemTask8_16(void *)
//// {
////   int *left = k_mem_alloc((1 << 13) - 20);
////   int *right = k_mem_alloc((1 << 14) - 20);
//
////   printf("left_ptr: %p\r\n", left);
////   printf("right_ptr: %p\r\n", right);
////   osTaskExit();
//// }
//
//// void MemTask8x4(void *)
//// {
////   int *first = k_mem_alloc((1 << 13) - 20);
////   int *second = k_mem_alloc((1 << 13) - 20);
////   int *third = k_mem_alloc((1 << 13) - 20);
////   int *fourth = k_mem_alloc((1 << 13) - 20);
////   printf("first: %p\r\n", first);
////   printf("second: %p\r\n", second);
////   printf("third: %p\r\n", third);
////   printf("fourth: %p\r\n", fourth);
////   osTaskExit();
//// }
//
//// void MemTask16_8(void *)
//// {
////   int *left = k_mem_alloc((1 << 14) - 20);
////   int *right = k_mem_alloc((1 << 13) - 20);
////   printf("left_ptr: %p\r\n", left);
////   printf("right_ptr: %p\r\n", right);
////   osTaskExit();
////   osTaskExit();
//// }
//
//// void MemTask32b(void *)
//// {
////   int *right = k_mem_alloc((1 << 5));
////   printf("right_ptr: %p\r\n", right);
////   osTaskExit();
////   osTaskExit();
//// }
//
//// void MemTask22B(void *)
//// {
////   int *left = k_mem_alloc((1 << 5) - 20);
////   int *right = k_mem_alloc((1 << 5) - 20);
////   printf("left_ptr: %p\r\n", left);
////   printf("right_ptr: %p\r\n", right);
////   osTaskExit();
////   osTaskExit();
//// }
//
//// void MemTask16x2_dealloc_realloc(void *)
//// {
////   int *ptr1 = k_mem_alloc((1 << 14) - 20);
////   int *ptr2 = k_mem_alloc((1 << 14) - 20);
////   int *ptr3 = k_mem_alloc((1 << 14) - 20); // should fail
//
////   printf("ptr1: %p\r\n", ptr1);
////   printf("ptr2: %p\r\n", ptr2);
////   printf("ptr3: %p\r\n", ptr3);
//
////   int res = k_mem_dealloc(ptr1);
////   printf("Dealloc first: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 14) - 20); // should pass
////   printf("ptr3: %p\r\n", ptr3);
//
////   osTaskExit();
//// }
//
//// void MemTask16x2_realloc_larger(void *)
//// {
////   int *ptr1 = k_mem_alloc((1 << 14) - 20);
////   int *ptr2 = k_mem_alloc((1 << 14) - 20);
////   int *ptr3 = k_mem_alloc((1 << 14) - 20); // should fail
//
////   printf("ptr1: %p\r\n", ptr1);
////   printf("ptr2: %p\r\n", ptr2);
////   printf("ptr3: %p\r\n", ptr3);
//
////   int res = k_mem_dealloc(ptr1);
////   printf("Dealloc first: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 15) - 20); // should fail
////   printf("ptr3: %p\r\n", ptr3);
//
////   res = k_mem_dealloc(ptr2);
////   printf("Dealloc second: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 15) - 20); // should pass
////   printf("ptr3: %p\r\n", ptr3);
//
////   osTaskExit();
//// }
//
//// void MemTask16x2_realloc_smaller(void *)
//// {
////   int *ptr1 = k_mem_alloc((1 << 14) - 20);
////   int *ptr2 = k_mem_alloc((1 << 14) - 20);
////   int *ptr3 = k_mem_alloc((1 << 14) - 20); // should fail
//
////   printf("ptr1: %p\r\n", ptr1);
////   printf("ptr2: %p\r\n", ptr2);
////   printf("ptr3: %p\r\n", ptr3);
//
////   int res = k_mem_dealloc(ptr1);
////   printf("Dealloc first: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 13) - 20);      // should pass
////   int *ptr4 = k_mem_alloc((1 << 13) - 20); // should pass
////   printf("ptr3: %p\r\n", ptr3);
////   printf("ptr4: %p\r\n", ptr4);
//
////   osTaskExit();
//// }
//
//// void MemTask16x2_realloc_larger2(void *)
//// {
////   int *ptr1 = k_mem_alloc((1 << 14) - 20);
////   int *ptr2 = k_mem_alloc((1 << 14) - 20);
////   int *ptr3 = k_mem_alloc((1 << 14) - 20); // should fail
//
////   printf("ptr1: %p\r\n", ptr1);
////   printf("ptr2: %p\r\n", ptr2);
////   printf("ptr3: %p\r\n", ptr3);
//
////   int res = k_mem_dealloc(ptr2);
////   printf("Dealloc first: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 15) - 20); // should fail
////   printf("ptr3: %p\r\n", ptr3);
//
////   res = k_mem_dealloc(ptr1);
////   printf("Dealloc second: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 15) - 20); // should pass
////   printf("ptr3: %p\r\n", ptr3);
//
////   osTaskExit();
//// }
//
//// void MemTask16x2_realloc_smaller2(void *)
//// {
////   int *ptr1 = k_mem_alloc((1 << 14) - 20);
////   int *ptr2 = k_mem_alloc((1 << 14) - 20);
////   int *ptr3 = k_mem_alloc((1 << 14) - 20); // should fail
//
////   printf("ptr1: %p\r\n", ptr1);
////   printf("ptr2: %p\r\n", ptr2);
////   printf("ptr3: %p\r\n", ptr3);
//
////   int res = k_mem_dealloc(ptr1);
////   printf("Dealloc first: %d\r\n", res);
////   ptr3 = k_mem_alloc((1 << 13) - 20);      // should pass
////   int *ptr4 = k_mem_alloc((1 << 13) - 20); // should pass
////   printf("ptr3: %p\r\n", ptr3);
////   printf("ptr4: %p\r\n", ptr4);
//
////   osTaskExit();
//// }
//
//// void MemTask32_invalid_ptr(void *)
//// {
////   int *ptr = k_mem_alloc((1 << 15) - 20);
////   int *invalid_ptr = ptr + 10;
////   int res = k_mem_dealloc(invalid_ptr);
////   printf("Dealloc invalid ptr: %d\r\n", res);
//// }
//// void MemTask_ext(void *)
//// {
//
////   printf("ext frag: %d, expected: 1 \r\n", k_mem_count_extfrag(1000000));
////   printf("ext frag: %d, expected: 0 \r\n", k_mem_count_extfrag(24));
////   printf("First alloc: %p \r\n", k_mem_alloc(10));
////   printf("ext frag: %d, expected: 9 \r\n", k_mem_count_extfrag(16384)); // STRICTLY LESS THAN
////   printf("ext frag: %d, expected: 8 \r\n", k_mem_count_extfrag(8096)); // STRICTLY LESS THAN
//
////   printf("ext frag: %d, expected: 10 \r\n", k_mem_count_extfrag(32000));
////   printf("ext frag: %d, expected: 9 \r\n", k_mem_count_extfrag(16000));
////   printf("ext frag: %d, expected: 8 \r\n", k_mem_count_extfrag(8000));
////   printf("Second alloc: %p\r\n", k_mem_alloc(1000));
//
//
////   printf("ext frag: %d, expected: 1 \r\n", k_mem_count_extfrag(33));
////   printf("ext frag: %d, expected: 7 \r\n", k_mem_count_extfrag(8000));
////   printf("Fourth alloc: %p\r\n", k_mem_alloc(8000));
////   printf("ext frag: %d, expected: 7 \r\n", k_mem_count_extfrag(16000));
////   printf("Fourth alloc: %p\r\n", k_mem_alloc(4000));
////   printf("ext frag: %d, expected: 6 \r\n", k_mem_count_extfrag(16000));
////   printf("fill: %p\r\n", k_mem_alloc(16000));
////   printf("fill: %p\r\n", k_mem_alloc(2000));
////   printf("fill: %p\r\n", k_mem_alloc(400));
////   printf("fill: %p\r\n", k_mem_alloc(200));
////   printf("fill: %p\r\n", k_mem_alloc(100));
////   printf("fill: %p\r\n", k_mem_alloc(30));
////   printf("fill: %p\r\n", k_mem_alloc(10));
////   printf("ext frag: %d, expected: 0 \r\n", k_mem_count_extfrag(1000000));
//
//
//
//
////   osTaskExit();
//// }
//// void MemTask_debug(void *){
//
//// //		uint8_t *ptr1 = k_mem_alloc(933);
//// //		uint8_t *ptr2 = k_mem_alloc(743);
//// //		uint8_t *ptr3 = k_mem_alloc(262); // should fail
//// 		uint8_t *ptr1 = k_mem_alloc(2000);
//// 		uint8_t *ptr2 = k_mem_alloc(2000);
//// 		uint8_t *ptr3 = k_mem_alloc(1000); // should fail
//// 	  printf("ptr1: %p\r\n", ptr1);
//// 	  printf("ptr2: %p\r\n", ptr2);
//// 	  printf("ptr3: %p\r\n", ptr3);
//
//// 	  int res = k_mem_dealloc(ptr1);
//// 	  printf("Dealloc first: %d\r\n", res);
//// 	  osTaskExit();
//
//// }
//// void MemTask_learn(void *)
//// {
//// 	  uint32_t size, r;
//// 	  uint32_t cnt_alloc_fails = 0;
//// 	  uint32_t cnt_dealloc_fails = 0;
//// 	  uint32_t cnt_checksum_fails = 0;
//
//// 	  printf("\r\n\r\n");
//// 	  printf("Starting testing ================================\r\n");
//// 	  for (int i = 0; i < ITERATIONS; i++ ){
//
//// 		  size = rand() % 1000; //select a random buffer size
//// 		  p_buffers[i] = k_mem_alloc(size); //allocate buffer
//// 		  printf("itr=%d, alloc %lu bytes, ptr=%p\r\n", i, size, p_buffers[i]);
//
//// 		  if (p_buffers[i] != NULL){ //success
//// 			  i_buffer_sizes[i] = size; //keep track of this allocation
//// 			  i_checksums[i] = CalcChecksum(s_data_string, size); //calculate checksum on original data, for the portion that will fit into this buffer
//// 			  memcpy(p_buffers[i], s_data_string, size); //fill the buffer fully with data (memcpy function used for testing only)
//// 			  i_total_alloc_bytes = i_total_alloc_bytes + size;
//// 		  } else { //did not allocate (should be due to fragmentation)
//// 			  printf("NULL POINTER\r\n");
//// 			  cnt_alloc_fails = cnt_alloc_fails + 1;
//// 			  i_buffer_sizes[i]=0;
//// 		  }
//
//// 		  if (i > 0 && i % 2 == 0){ //deallocate something on every other iteration
//// 			  do{
//// 				  r = rand() % i;
//// 			  } while(i_buffer_sizes[r] == 0);//repeat until finding a buffer that still exists (not deallocated already)
//
//// 			  printf("dealloc mem from itr %lu, ptr=%p, ~%lu bytes\r\n", r, p_buffers[r], i_buffer_sizes[r]);
//// 			  if (k_mem_dealloc(p_buffers[r]) != RTX_ERR) { //success
//// 				  i_total_alloc_bytes = i_total_alloc_bytes - i_buffer_sizes[r];
//// 				  i_buffer_sizes[r] = 0; //keep track of the dealloc
//// 				  p_buffers[r] = NULL;
//// 			  }else{
//// 				  printf("RTX_ERR\r\n");
//// 				  cnt_dealloc_fails += 1;
//// 			  }
//// 		  }
//// 	  }
//
//// 	  printf("Validating buffer contents... \r\n");
//
//// 	  uint8_t checksum;
//// 	  for (int i = 0; i < ITERATIONS; i++ ){
//// 		  if (i_buffer_sizes[i] > 0){
//// 			  checksum = CalcChecksum(p_buffers[i], i_buffer_sizes[i]);
//// 			  if (checksum != i_checksums[i]){
//// 				  cnt_checksum_fails += 1;
//// 				  printf("buffer from itr %d corrupted, checksum=%u, expected=%u \r\n", i, checksum, i_checksums[i]);
//// 			  }
//// 		  }
//// 	  }
//
//// 	  printf("Total corrupted buffers = %lu \r\n", cnt_checksum_fails);
//// 	  printf("Total failed allocs = %lu \r\n", cnt_alloc_fails);
//// 	  printf("Total failed deallocs = %lu \r\n", cnt_dealloc_fails);
//
//
//// 	  printf("back to main\r\n");
//// }
//// void MemTask_anything(void *){
//
//// //		uint8_t *ptr1 = k_mem_alloc(933);
//// //		uint8_t *ptr2 = k_mem_alloc(743);
//// //		uint8_t *ptr3 = k_mem_alloc(262); // should fail
//// 		uint8_t *ptr1 = k_mem_alloc(2000);
//// 		uint8_t *ptr2 = k_mem_alloc(2000);
//// 		uint8_t *ptr3 = k_mem_alloc(1000); // should fail
//// 		uint8_t *ptr4 = k_mem_alloc(1000); // should fail
//
//// 	  printf("ptr1: %p\r\n", ptr1);
//// 	  printf("ptr2: %p\r\n", ptr2);
//// 	  printf("ptr3: %p\r\n", ptr3);
//// 	  printf("ptr4: %p\r\n", ptr4);
//
//// 	  osTaskExit();
//
//// }
//
//// void MemTask_time(void *){
//
//// 	  if (ARM_CM_DWT_CTRL != 0) {        // See if DWT is available
//// 		  printf("Using DWT\r\n\r\n");
//// 	      ARM_CM_DEMCR      |= 1 << 24;  // Set bit 24
//// 	      ARM_CM_DWT_CYCCNT  = 0;
//// 	      ARM_CM_DWT_CTRL   |= 1 << 0;   // Set bit 0
//// 	  }else{
//// 		  printf("DWT not available \r\n\r\n");
//// 	  }
//
//// 	  int N = 100;
//// 	  volatile U32* p_temp;
//// 	  uint32_t timestamps[N+1];
//
//// 	//System under test---------------------
//// 	  //measure time to allocate N block
//// //	  for (int i = 0; i < N; i ++){
//// //		  timestamps[i] = ARM_CM_DWT_CYCCNT;
//// //		  p_temp = (U32*)k_mem_alloc(4);
//// //	  }
//// //	  timestamps[N] = ARM_CM_DWT_CYCCNT;
//// //	  //print total clock ticks as well as ticks per iteration
//// //	  printf("k_mem_alloc time: %lu\r\n", timestamps[N] - timestamps[0]);
//// //	  printf("Time per iteration:\r\n");
//// //	  for (int i = 0; i < N; i ++){
//// //		  printf("%u, ", timestamps[i+1] - timestamps[i]);
//// //	  }
//// //	  printf("\r\n\r\n");
//
//
//// 	//Compiler's version-------------------
//// 	  //measure time to allocate N block
//// 	  for (int i = 0; i < N; i ++){
//// 		  timestamps[i] = ARM_CM_DWT_CYCCNT;
//// 		  p_temp = (U32*)malloc(4);
//// 	  }
//// 	  timestamps[N] = ARM_CM_DWT_CYCCNT;
//// 	  //print total clock ticks as well as ticks per iteration
//// 	  printf("malloc time: %lu\r\n", timestamps[N] - timestamps[0]);
//// 	  printf("Time per iteration:\r\n");
//// 	  for (int i = 0; i < N; i ++){
//// 		  printf("%u, ", timestamps[i+1] - timestamps[i]);
//// 	  }
//// 	  printf("\r\n\r\n");
//
//
//// 	  printf("back to main\r\n");
//// }
//
// void MemTask_dealloctest(void *){
//
// //		uint8_t *ptr1 = k_mem_alloc(933);
// //		uint8_t *ptr2 = k_mem_alloc(743);
// //		uint8_t *ptr3 = k_mem_alloc(262); // should fail
// 		uint8_t *ptr1 = k_mem_alloc(8000);
// 		uint8_t *ptr2 = k_mem_alloc(8000); // should fail
// 		uint8_t *ptr3 = k_mem_alloc(8000);
//// 		uint8_t *ptr4 = k_mem_alloc(8000);
//
// 	 	printf("ptr1 8000b: %p\r\n", ptr1);
// 	 	printf("ptr2 8000b: %p\r\n", ptr2);
// 	 	printf("ptr3 8000b: %p\r\n", ptr3);
// 	 	//printf("ptr4: %p\r\n", ptr4);
//
// 		int res = k_mem_dealloc(ptr2);
// 		printf("Dealloc ptr2 8000b: %d\r\n", res);
// 		*ptr2 = k_mem_alloc(8000); // should fail
// 		uint8_t *ptr4 = k_mem_alloc(8000);
// 	  printf("ptr1 8000b: %p\r\n", ptr1);
// 	  printf("ptr2 8000b: %p\r\n", ptr2);
// 	  printf("ptr3 8000b: %p\r\n", ptr3);
// 	  printf("ptr4 8000b: %p\r\n", ptr4);
//
// 	  res = k_mem_dealloc(ptr1); // there is no free here poiting to
// 	  printf("Dealloc ptr1 8000b: %d\r\n", res);
// 	  res = k_mem_dealloc(ptr2); //the next free spot here should be its partner, however it should also coalesce
// 	  printf("Dealloc ptr2 8000b, coalese up: %d\r\n", res);
//
// 	  *ptr1 = k_mem_alloc(16000);
// 	  printf("ptr1 16000b: %p\r\n", ptr1);
//
// 	  res = k_mem_dealloc(ptr3);
// 	  printf("Dealloc ptr3 8000: %d\r\n", res);
// 	  res = k_mem_dealloc(ptr4);
// 	  printf("Dealloc ptr4 8000: %d\r\n", res);
// 	  res = k_mem_dealloc(ptr1);
// 	  printf("Dealloc ptr1 16000: %d\r\n", res);
// 	  *ptr1 = k_mem_alloc(32000);
//
// 	  printf("ptr1 32000: %p\r\n", ptr1);
// 	 res = k_mem_dealloc(ptr1);
// 	 printf("Dealloc 32000: %d\r\n", res);
// 	  osTaskExit();
//
// }
// void MemTask_debug(void *){
//
//  //		uint8_t *ptr1 = k_mem_alloc(933);
//  //		uint8_t *ptr2 = k_mem_alloc(743);
//  //		uint8_t *ptr3 = k_mem_alloc(262); // should fail
//		uint8_t *ptr0 = k_mem_alloc(4000);
//  		uint8_t *ptr1 = k_mem_alloc(4000);
//  		uint8_t *ptr2 = k_mem_alloc(4000); // should fail
//  		uint8_t *ptr3 = k_mem_alloc(4000);
//  		uint8_t *ptr4 = k_mem_alloc(4000);
//  		uint8_t *ptr5 = k_mem_alloc(4000);
//  		uint8_t *ptr6 = k_mem_alloc(4000);
//
//  	 	printf("ptr0: %p\r\n", ptr0);
//  	 	printf("ptr1: %p\r\n", ptr1);
//  	 	printf("ptr2: %p\r\n", ptr2);
//  	 	printf("ptr3: %p\r\n", ptr3);
//  	 	printf("ptr4: %p\r\n", ptr4);
//  	 	printf("ptr5: %p\r\n", ptr5);
//  	 	printf("ptr6: %p\r\n", ptr6);
//
//  		int res = k_mem_dealloc(ptr4);
//  		printf("Dealloc ptr4 4000: %d\r\n", res);
// // 	uint8_t *ptr4 = k_mem_alloc(8000);
//  		 res = k_mem_dealloc(ptr3);
//  		printf("Dealloc ptr3 4000: %d\r\n", res);
//
//  		 res = k_mem_dealloc(ptr5);
//  		printf("Dealloc ptr5 4000: %d\r\n", res);
//  		 *ptr3 = k_mem_alloc(4000);
//  		 *ptr4 = k_mem_alloc(4000);
//  		 *ptr5 = k_mem_alloc(4000); // should fail
//  		printf("ptr0: %p\r\n", ptr0);
//  	  	 	printf("ptr1: %p\r\n", ptr1);
//  	  	 	printf("ptr2: %p\r\n", ptr2);
//  	  	 	printf("ptr3: %p\r\n", ptr3);
//  	  	 	printf("ptr4: %p\r\n", ptr4);
//  	  	 	printf("ptr5: %p\r\n", ptr5);
//  	  	 	printf("ptr6: %p\r\n", ptr6);
//  	 	//printf("ptr4: %p\r\n", ptr4)
//  	  osTaskExit();
//
//  }
// int main_c(void)
// {
//
//   /* MCU Configuration: Don't change this or the whole chip won't work!*/
//
//   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//   HAL_Init();
//   /* Configure the system clock */
//   SystemClock_Config();
//
//   /* Initialize all configured peripherals */
//   MX_GPIO_Init();
//   MX_USART2_UART_Init();
//   /* MCU Configuration is now complete. Start writing your code below this line */
//
//   osKernelInit();
//   k_mem_init();
//
//   TCB st_mytask;
//   st_mytask.stack_size = 0x400;
//
//   st_mytask.ptask = &MemTask_debug;
//   osCreateTask(&st_mytask);
//
//   osKernelStart();
//
//   while (1)
//   {
//     /* USER CODE END WHILE */
//     //	  printf("Hello, world!\r\n");
//     /* USER CODE BEGIN 3 */
//   }
//   /* USER CODE END 3 */
// }
