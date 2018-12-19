#include<iostream>
#include<cstdint>
#include<cassert>
/*
The switch of the div
*/
#define add_back
uint32_t mul(uint32_t X, uint32_t Y, uint8_t data_size);
int32_t imul(int32_t X, int32_t Y, uint8_t data_size);
int32_t div(int32_t X, int32_t Y, uint8_t data_size);

typedef struct{
	uint32_t data_size; //one per decimal
	uint32_t data;      //We have at most 32/4 = 8 data_size
	uint32_t sign : 1;
}BCD;

int compute_BCD(BCD bcd);
int BCD_add(BCD b1, BCD b2);
int BCD_sub(BCD b1, BCD b2);