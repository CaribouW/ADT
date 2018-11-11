#include<iostream>
#include<cstdint>
#include<cassert>
inline int32_t get_lower(int32_t X, int8_t n){ return X&(0xFFFFFFFF >> (32 - n)); }
inline int8_t get_sign(int32_t X, int8_t n){ return 0x1 & (X >> (n - 1)); }
inline int8_t neg(int32_t X, int8_t n){ return X ^ (0xFFFFFFFF>>(32-n)); }
/*
unsigned multiple.
The factors has (data_size) bits. And return the 2*(data_size) bits result.
*/
uint32_t mul(uint32_t X, uint32_t Y, uint8_t data_size){
	assert(data_size == 4 || data_size == 8 || data_size == 16); //Assume that the data_size=4,8,16
	uint32_t reg = 0;											//The register that contains the result.
	uint8_t carry = 0;											//The carry bit
			
	reg += Y;													//set the lower to be X.
	for (uint8_t counter = 0; counter < data_size ; counter++){	//We just shift right counter times.
		if (Y & 0x01 == 1)										//If the lower bit of X equals 1.
			reg += (X << data_size);
		reg = reg >> 1;
		Y = get_lower(reg, data_size);				//Renew the value of X.
	}
	return get_lower(reg, data_size * 2);
}

/*
Adopt the Booth multiply to compute the result.
*/
int32_t imul(int32_t X, int32_t Y, uint8_t data_size){
	assert(data_size == 4 || data_size == 8 || data_size == 16);
	int8_t Y0 = 0;
	int32_t reg = 0;
	int32_t comple = -X;                      //get the comlement of Y;
	X = get_lower(X, data_size); //Assume all of the number are unsigned
	Y = get_lower(Y, data_size);
	comple = get_lower(comple, data_size);
	reg += Y;                    //Set the lower bit of reg.
	for (uint8_t counter = 0; counter < data_size; counter++){
		int8_t Y1 = Y & 0x01;
		switch (Y0 - Y1){
		case 0:
			break;
		case 1:
			reg += (X << data_size);
			break;
		case -1:
			reg += (comple << data_size);
		}
		Y0 = Y1;
		uint8_t sign = get_sign(reg, data_size * 2);
		reg = (get_lower(reg,data_size*2)) >> 1;
		if (sign == 1)             //Algrithom shift.
			reg |= 1 << (data_size*2 - 1);
		Y = get_lower(reg, data_size);
	}
	int8_t sign = get_sign(reg, data_size * 2);
	if (sign){
		return reg | (0xFFFFFFFF<<(data_size*2));
	}
	else
		return get_lower(reg, data_size * 2);
}

/*
ret the reult of X/Y
*/
int32_t div(int32_t X, int32_t Y, uint8_t data_size){
	assert(data_size == 4 || data_size == 8 || data_size == 16);
	int32_t Rest = 0, result = 0;
	int32_t divisor = get_lower(Y, data_size);
	int32_t quotient= get_lower(X, data_size*2);
	result += quotient;   //Set the lower bits to be the X.
	uint8_t signle_q = 0;
	for (uint8_t counter = 0; counter < data_size; counter++){

	}
	return 0;
}

