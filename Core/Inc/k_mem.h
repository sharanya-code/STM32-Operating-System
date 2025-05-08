/*
 * k_mem.h
 *
 *  Created on: Jan 5, 2024
 *      Author: nexususer
 *
 *      NOTE: any C functions you write must go into a corresponding c file that you create in the Core->Src folder
 */

#ifndef INC_K_MEM_H_
#define INC_K_MEM_H_

/************************************************
 *               INCLUDES
 ************************************************/

#include "common.h"
#include "k_task.h"

/************************************************
 *               DEFINITIONS
 ************************************************/

// Used to verify validity of pointer provided for deallocation
#define METADATA_SECRET_KEY      0b10011001

/************************************************
 *               TYPEDEFS
 ************************************************/

typedef unsigned int size_t;

typedef struct block_metadata {
	U8 secret_key;
	U8 is_allocated;
	U32 task_tid;
	U16 level_pos;
	struct block_metadata* next;
	struct block_metadata* prev;
	U32 dummy; // 8 byte alignment
} metadata;


/************************************************
 *              FUNCTION DEFS
 ************************************************/

/*
 * @brief: Initialize
 */
int k_mem_init();

/*
 * @brief: Allocate
 */
void* k_mem_alloc(size_t size);

/*
 * @brief: Deallocate
 */
int k_mem_dealloc(void* ptr);
int k_mem_count_extfrag(size_t size);
void debug_printer_size();
void transfer_function(void *ptr, task_t tid);

#endif /* INC_K_MEM_H_ */
