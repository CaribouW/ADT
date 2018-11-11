#include<iostream>
#include<cstdint>
#define FPU
union floatNum{
	struct{
		uint32_t significant : 23;
		uint32_t exp : 8;
		uint32_t sign : 1;
	};
	floatNum(float val){
		this->f_val = val;
	}
	floatNum(int val){
		this->val = val;
	}
	float f_val;
	uint32_t val;
};
floatNum add(floatNum float1, floatNum float2);
floatNum sub(floatNum float1, floatNum float2);
floatNum mul(floatNum float1, floatNum float2);
floatNum div(floatNum float1, floatNum float2);