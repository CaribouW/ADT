#include"ALU.h"
inline int32_t get_lower(int32_t X, int8_t n){ return X&(0xFFFFFFFF >> (32 - n)); }
inline int8_t get_sign(int32_t X, int8_t n){ return 0x1 & (X >> (n - 1)); }
inline int8_t neg(int32_t X, int8_t n){ return X ^ (0xFFFFFFFF >> (32 - n)); }
/*
unsigned multiple.
The factors has (data_size) bits. And return the 2*(data_size) bits result.
*/
uint32_t mul(uint32_t X, uint32_t Y, uint8_t data_size){
	assert(data_size == 4 || data_size == 8 || data_size == 16); //Assume that the data_size=4,8,16
	uint32_t reg = 0;											//The register that contains the result.
	uint8_t carry = 0;											//The carry bit

	reg += Y;													//set the lower to be X.
	for (uint8_t counter = 0; counter < data_size; counter++){	//We just shift right counter times.
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
			break;
		}
		Y0 = Y1;
		uint8_t sign = get_sign(reg, data_size * 2);
		reg = (get_lower(reg, data_size * 2)) >> 1;//shift right
		if (sign == 1)             //Algrithom shift. we put the bit move in to be 1
			reg |= 1 << (data_size * 2 - 1);
		Y = get_lower(reg, data_size);
	}
	int8_t sign = get_sign(reg, data_size * 2);
	if (sign){
		if (data_size == 16)
			return reg;
		else//put to the whole reg to be neg
			return reg | (0xFFFFFFFF << (data_size * 2));
	}
	else
		return get_lower(reg, data_size * 2);
}

/*
ret the reult of X/Y
The length of the result is 'data_size'
*/
int32_t div(int32_t X, int32_t Y, uint8_t data_size){
	assert(data_size == 4 || data_size == 8 || data_size == 16);
	assert(Y);
	int32_t Rest = 0, reg = 0;
	int8_t divisor_sign, divident_sign, rest_sign;
	bool Q0 = 0;
	divisor_sign = get_sign(Y, data_size);
	rest_sign = divident_sign = get_sign(X, data_size);
	if (divident_sign == 1){
		X = get_lower(-X, data_size);
	}
	if (divisor_sign == 1){
		Y = get_lower(-Y, data_size);
	}
	int32_t divisor = get_lower(Y, data_size);
	int32_t quotient = get_lower(X, data_size * 2);
	reg += quotient;   //Set the lower bits to be the X.
#ifdef add_back
	for (int8_t counter = 0; counter < data_size; counter++){
		reg = reg << 1;
		Rest = get_lower(reg >> data_size, data_size);
		//Rest = Rest > divisor ? (Rest - divisor) : Rest;
		if (Rest >= divisor){
			Q0 = 1;
			reg = reg - (divisor << data_size);
		}
		else{
			Q0 = 0;
		}
		reg = Q0 ? reg + 1 : reg; //Set the Q0
		reg = get_lower(reg, data_size * 2);
	}
	Rest = get_lower(reg >> data_size, data_size);
	quotient = get_lower(reg, data_size);

	if (rest_sign)
		Rest = -Rest;
	if (divisor_sign^divident_sign)
		quotient = -quotient;
	return quotient;
#else
	//£¨²»»Ö¸´ÓàÊý³ý·¨£©
	//Not add back
	//reg = reg - (divisor << data_size);
	reg = reg - (divisor << data_size); //subtract first
	for (int8_t counter = 0; counter <= data_size; counter++){
		//Rest = get_lower(reg >> data_size, data_size);
		int sign = get_sign(reg, data_size * 2);
		reg = reg << 1;
		reg = sign == 0 ? reg + 1 : reg; //Set the Q0
		reg = get_lower(reg, data_size * 2);
		//put Q0
		if (sign == 0){
			Q0 = 1;
			reg = reg - (divisor << data_size);
		}
		else{
			Q0 = 0;
			//if (counter != data_size - 1)
			reg = reg + (divisor << data_size);
		}

		reg = get_lower(reg, data_size * 2);
	}
	if (Q0 == 1){
		reg = reg + (divisor << data_size);
		reg = get_lower(reg, data_size * 2);
	}
	Rest = get_lower(reg >> data_size, data_size);
	quotient = get_lower(reg, data_size);
	Rest = Rest | (0xFFFFFFFF << data_size);
	if (!rest_sign)
		Rest = -Rest;
	if (divisor_sign^divident_sign)
		quotient = -quotient;
	return quotient;
#endif

}

int compute_BCD(BCD bcd){
	int result = 0;
	uint32_t data = get_lower(bcd.data, bcd.data_size * 4);
	for (int i = 0; i < bcd.data_size; i++){
		result += (data >> (bcd.data_size - i - 1) * 4)&(0xFFFFFFFF >> (32 - 4));
		result *= 10;
	}
	result /= 10;
	if (bcd.sign)
		result = -result;
	return result;
}
int BCD_add(BCD b1, BCD b2){
	return 1;
}
int BCD_sub(BCD b1, BCD b2){
	b2.sign *= -1;
	return BCD_add(b1, b2);
}