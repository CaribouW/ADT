#include<cstdint>
#include<iostream>
#include <windows.h>
#define BLOCK_SIZE_BYTE 32	        //32 Byte per block
#define MEM_SIZE_BYTE 32*1024*1024  //32MB mem
#define CACHE_WAY 4                 //4 ways
#define CACHE_SIZE_BYTE 4*1024      //cache has the total data size 4KB

typedef struct{
	uint8_t data[BLOCK_SIZE_BYTE];  //data part
	uint32_t tag : 15;              //tag part
}cache;

typedef union{
	uint32_t vaddr;
	struct{
		uint32_t offset : 12;
		uint32_t line_index : 5;
		uint32_t tag : 20 - 5;
	};
}vaddr_for_cache; //split the vaddr into three part

typedef union{
	uint32_t vaddr;
}vaddr_for_Vmem; //split the vaddr for the virtual memory
uint8_t hw_mem[MEM_SIZE_BYTE];
cache cpu_cache[CACHE_SIZE_BYTE / BLOCK_SIZE_BYTE];


//task1: Split the vaddr into the 'vaddr_for_cache' way by yourself
//task2: Give the list of the addr request and print out the condition of the cache lines
//task3: FIFO LRU LFU alog and compute the hit rate
//task4: Assume the time comsume on the cache is Tc, then the time on main-mem is 10*Tc, compute the time consume of task2