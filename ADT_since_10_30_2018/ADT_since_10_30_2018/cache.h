#include<cstdint>
#include<iostream>
#include <windows.h>
#define BLOCK_SIZE_BYTE 32	        //32 Byte per block
#define MEM_SIZE_BYTE 32*1024*1024  //32MB mem
#define CACHE_WAY 4                 //4 ways
#define CACHE_SIZE_BYTE 4*1024      //cache has the total data size 4KB

typedef struct{
	uint32_t data;
	uint32_t tag;
}cache;

typedef union{
	uint32_t vaddr;
	struct{
		uint32_t offset;
		uint32_t line_index;
		uint32_t tag;
	};
}vaddr_for_cache; //split the vaddr into three part

typedef union{
	uint32_t s;
}vaddr_for_Vmem; //split the vaddr for the virtual memory
uint8_t hw_mem[MEM_SIZE_BYTE];
cache cpu_cache[CACHE_SIZE_BYTE / BLOCK_SIZE_BYTE];