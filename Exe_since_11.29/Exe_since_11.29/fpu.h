#include<iostream>
#include<cstdint>
#define FPU
#define P_ZERO_F 0X0              //positive zero
#define N_ZERO_F 0X80000000       //negative zero
#define P_INF_F 0X7f800000        //positive infinity
#define N_INF_F 0Xff800000		  //negative infinity
#define P_NAN_F 0X7fc00000		  //positive not a number
#define N_NAN_F 0Xffc00000		  //negative not a number
#define sign(x) ((x>>31)&0x1)
union floatNum{
	struct{
		uint32_t significant : 23;
		uint32_t exp : 8;
		uint32_t sign : 1;
	};
	float f_val;
	uint32_t val;

	floatNum(float val){
		this->f_val = val;
	}
	floatNum(int val){
		this->val = val;
	}

};
floatNum add(floatNum float1, floatNum float2);
floatNum sub(floatNum float1, floatNum float2);
floatNum mul(floatNum float1, floatNum float2);
floatNum div(floatNum float1, floatNum float2);