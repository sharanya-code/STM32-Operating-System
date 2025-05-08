#include "k_mem.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include <math.h>
#include "k_task.h"

/************************************************
 *               GLOBALS
 ************************************************/

extern uint32_t _estack;
extern uint32_t _Min_Stack_Size;
extern uint32_t _img_end;
U32 total_alloc = 0; // THIS IS FOR DEBUG ONLY
U32 init_called = 0;
metadata *free_list[11];
U8 bitarray[2047] = {0};
U32 heap_start;
U8 MAX_SIZE_POWER = 15;

/************************************************
 *               HELPER FUNCTIONS
 ************************************************/

static inline U16 get_parent(U16 index)
{
	return (index - 1) >> 1;
}

static inline U16 get_left_child(U16 index)
{
	return index << 1;
}

static inline U16 get_right_child(U16 index)
{
	return (1 << index) + 1;
}

// The math.h library doesn't seem to work so I'm just going to implement my own log2 function
unsigned int integer_log2(unsigned int num)
{
	if (num == 0)
		return 0; // Handle the edge case for 0
	return 31 - __builtin_clz(num);
}

static inline U8 index_to_level(const U16 index)
{
	return (U8)(integer_log2(index + 1));
}

static U16 index_to_level_pos(const U16 index)
{
	U8 level = index_to_level(index);
	return (U16)(index - (1 << level) + 1);
}

static inline U16 index_level_to_level_pos(const U16 index, const U8 level)
{
	return (U16)(index - (1 << level) + 1);
}

void index_to_level_and_pos(const U16 index, U8 *level, U16 *level_pos)
{
	*level = index_to_level(index);
	*level_pos = (U16)(index - (1 << *level) + 1);
}

static U16 get_buddy(const U16 index)
{
	U8 level;
	U16 level_pos;
	index_to_level_and_pos(index, &level, &level_pos);

	return ((1 << level) - 1) + (level_pos ^ 1);
}

static inline U16 get_buddy_level_level_pos(const U8 level, const U16 level_pos)
{
	return ((1 << level) - 1) + (level_pos ^ 1);
}

static U16 addr_to_index(const U32 *const ptr, U8 *level_out)
{
	// Find the index for the bottom level node (child of desired node)
	U16 bottom_level_offset = ((U32)ptr - heap_start) / (U32)(1 << 5);
	U16 bottom_level_index = (1 << 10) - 1 + bottom_level_offset;

	// Move up the heap until allocated node is found
	U8 level = 10;
	U16 bitarray_index = bottom_level_index;

	while (bitarray[bitarray_index] == 0)
	{
		level--;
		bitarray_index = get_parent(bitarray_index);
	}

	*level_out = level;

	return bitarray_index;
}

static U32 index_to_addr(const U16 index)
{
	U8 level;
	U16 level_pos;

	index_to_level_and_pos(index, &level, &level_pos);

	return heap_start + (U32)(1 << (MAX_SIZE_POWER - level)) * level_pos;
}

static inline U32 level_level_pos_to_addr(const U8 level, const U16 level_pos)
{
	return heap_start + (U32)(1 << (MAX_SIZE_POWER - level)) * level_pos;
}

void super_fast_index_to_addr(const U16 index, U32 **addr, U32 **buddy_addr)
{
	U32 level = integer_log2(index + 1);
	U32 level_pos = (index - (1 << level) + 1);

	U32 level_offset = 1 << (MAX_SIZE_POWER - level);
	*addr = heap_start + level_offset * level_pos;
	*buddy_addr = heap_start + level_offset * (level_pos + 1);
}

void split_node(metadata *parent, int lvl)
{
	int next_lvl = lvl + 1;
	int parent_index = (1 << lvl) + parent->level_pos - 1;
	int parent_pos = parent->level_pos;
	int bitindex = (parent_index << 1) + 1;

	bitarray[parent_index] = 1;
	bitarray[bitindex] = 1;

	free_list[lvl] = free_list[lvl]->next;

	// free_list[lvl] = free_list[lvl]->next; // we remove the shit in the loop then, also calculate pos and bitarray position here for comfort
	metadata *cur;
	metadata *next;
	// uint32_t start = TIMER_THING;
	super_fast_index_to_addr(bitindex, &cur, &next);
	// Calculate the children nodes off parent
	cur->level_pos = parent_pos << 1;
	next->level_pos = cur->level_pos + 1;
	next->next = NULL;
	cur->prev = NULL;
	// set the nodes to created
	next->prev = cur;
	cur->next = next;

	free_list[next_lvl] = cur;
}

void debug_printer()
{
	for (int i = 0; i < 2047; i++)
	{
		if (bitarray[i] == 1)
		{
			// printf("Bit array i: %d, addr: %p \r\n", i, index_to_addr(i));
		}
	}
}
void debug_printer_size()
{
	// printf("size: %d \r\n", total_alloc);
}

void debug_print1()
{
	for (int i = 0; i < 11; i++)
	{
		if (free_list[i] != NULL)
		{
			// printf("%d %p, ", i, free_list[i] + 20);
		}
		else
		{
			// printf("%d NULL, ", i);
		}
	}

	// printf("\r\n");
}
/************************************************
 *               FUNCTIONS
 ************************************************/

int k_mem_init()
{
	heap_start = &_img_end;

	if (init_called == 1 || kernel_config.is_running == FALSE)
	{
		return RTX_ERR;
	}
	init_called = 1;
	metadata *head = index_to_addr(0);

	head->next = NULL;
	head->prev = NULL;
	head->level_pos = 0;

	free_list[0] = head;

	for (int i = 1; i < 11; i++)
	{
		free_list[i] = NULL;
	}
	return RTX_OK;
}

void *k_mem_alloc(size_t size)
{
	if (init_called == 0 || size == 0) // Check to make sure init called and size are greater than 0
	{
		return NULL;
	}

	int k = MAX_SIZE_POWER;
	int size_of_block = 1 << k;
	size += sizeof(metadata);

	while (size < size_of_block) // Find the upperbound of a block that fits our size includied with metadata
	{
		k = k - 1;
		size_of_block = 1 << k;
	}

	k = MAX_SIZE_POWER - k;
	k--;
	if (k < 0)
	{
		return NULL;
		k = 0;
	}
	if (free_list[k] != NULL) // If node exists then put memory into here then go to next node
	{
		int pos = (1 << k) + (free_list[k]->level_pos) - 1;
		bitarray[pos] = 1;
		//	free_list[k] = free_list[k]->next;
	}
	else
	{
		// Now we have k
		int node_not_null = k;
		while (node_not_null >= 0 && free_list[node_not_null] == NULL) // Find the peak node where space exists
		{
			node_not_null = node_not_null - 1;
		}
		if (node_not_null < 0)
		{
			// No available block large enough

			return NULL;
		}

		for (node_not_null; node_not_null < k; node_not_null++)
		{
			split_node(free_list[node_not_null], node_not_null);
		}
	}

	// uint32_t *base_address = index_to_addr((1 << 15 - k) * free_list[k]->level_pos);
	// U8 *base_address = (U8 *)index_to_addr((1 << k) + (free_list[k]->level_pos) - 1); // has to be U8 for pointer arithmetic
	U8 *base_address = (U8 *)free_list[k];

	free_list[k] = free_list[k]->next; // Update the free list to point to the next free block

	metadata *meta = (metadata *)base_address;
	meta->task_tid = osGetTID();
	meta->secret_key = 0b10011001;
	meta->is_allocated = 1;
	// total_alloc= total_alloc +size_of_block;
	return base_address + sizeof(metadata);
}

void transfer_function(void *ptr, task_t tid) {
	U8 *mem_addr = (U8 *)ptr;
	metadata *meta = (metadata *)(mem_addr - sizeof(metadata));

	meta->task_tid = tid;
}

int k_mem_dealloc(void *ptr)
{
	if (init_called == 0) // Check to make sure init called and size are greater than 0
	{
		return RTX_ERR;
	}

	U8 *mem_addr_p = (U8 *)ptr;

	if (ptr == NULL)
	{
		// printf("NULL pointer\r\n");
		return RTX_ERR;
	}

	/**
	 *  Check validity of pointer (random/invalid so check for metadata key value)
	 */
	metadata *block_metadata_p = (metadata *)(mem_addr_p - sizeof(metadata));
	// printf("block_metadata: secret_key: %d, is_allocated: %d, task_tid: %d, level_pos: %d, next: %p, prev: %p\r\n", block_metadata_p->secret_key, block_metadata_p->is_allocated, block_metadata_p->task_tid, block_metadata_p->level_pos, block_metadata_p->next, block_metadata_p->prev);

	if (block_metadata_p->secret_key != 0b10011001)
	{
		// printf("Invalid pointer\r\n");
		return RTX_ERR;
	}

	/*
	 *  Check that memory that ptr points to is allocated
	 */
	if (block_metadata_p->is_allocated == 0)
	{
		// printf("Memory not allocated\r\n");
		return RTX_ERR;
	}

	/*
	 *  Check that current running task owns block
	 */
	if (block_metadata_p->task_tid != osGetTID())
	{
		// printf("Task does not own block\r\n");
		return RTX_ERR;
	}

	/****************************************************
	 *                  DEALLOCATE
	 ****************************************************/

	/*
	 *  Finding block (start at addr block and move up to parent) (Slide 30)
	 */
	U8 level = 10;
	U16 bitarray_index = addr_to_index(mem_addr_p, &level);

	// while (bitarray[bitarray_index] == 0)
	// {
	// 	level--;
	// 	bitarray_index = get_parent(bitarray_index);
	// }

	/**************************
	 *  Coalescing algorithm
	 **************************/

	U8 current_level = level;
	U16 current_level_pos = index_level_to_level_pos(bitarray_index, current_level);
	// total_alloc= total_alloc - (1<< current_level);

	U16 buddy_index = get_buddy_level_level_pos(current_level, current_level_pos);
	U8 finish_coalescing = 0;

	do
	{
		// set current node to 0
		bitarray[bitarray_index] = 0;
		metadata *current_node = (metadata *)level_level_pos_to_addr(current_level, current_level_pos);

		// update current node metadata
		current_node->is_allocated = 0;
		current_node->level_pos = current_level_pos; // What is this for
		current_node->next = NULL;
		current_node->prev = NULL;

		if (bitarray[buddy_index] != 0 || bitarray_index == 0)
		{
			// if buddy is 1 (or we are root) we add ourselves to free list (AND END ALGORITHM)
			metadata *prev_head = free_list[current_level];

			current_node->next = prev_head;
			current_node->prev = NULL;

			if (prev_head != NULL)
				prev_head->prev = current_node;

			// printf("prev head:%p, curr: %p\r\n",prev_head,current_node);

			free_list[current_level] = current_node;
			return RTX_OK;
			finish_coalescing = 1;
		}
		else if (bitarray[buddy_index] == 0)
		{
			// if buddy is 0 remove it from free list (and we are not root)
			// figure out if left or right child if left child we set abvove lvl to us.

			metadata *free_buddy = (metadata *)level_level_pos_to_addr(current_level, current_level_pos ^ 1);
			if (free_list[current_level] == free_buddy)
			{
				free_list[current_level] = free_buddy->next;
			}
			if (free_buddy->next != NULL)
			{
				free_buddy->next->prev = free_buddy->prev;
			}
			if (free_buddy->prev != NULL)
			{
				free_buddy->prev->next = free_buddy->next;
			}
		}

		current_level--;
		current_level_pos = current_level_pos >> 1;

		// update current node to parent
		bitarray_index = get_parent(bitarray_index);
		buddy_index = get_buddy_level_level_pos(current_level, current_level_pos);

	} while (!finish_coalescing);

	return RTX_OK;
}

int k_mem_count_extfrag(size_t size)
{
	if (init_called == 0 || size == 0 || size <= 32) // Check to make sure init called and size are greater than 0
	{
		return 0;
	}

	int k = 0;
	int log = size;
	while (log >>= 1)
		k++;
	if (1 << k == size)
	{
		k--;
	}

	if (k > 15)
	{
		k = 15;
	}
	k = 15 - k;
	//		printf("kets see k %d\r\n",k );

	int count = 0;

	for (int i = k; i <= 10; ++i)
	{
		//			printf("kets see i %d\r\n",i );

		if (free_list[i] != NULL)
		{
			//				printf("ALIVE ^ i %d\r\n",i );

			count++;
		}
	}
	return count;
}
