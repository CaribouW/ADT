#include"fpu.h"
floatNum add(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val + float2.f_val;
#endif // !FPU
	//1. check exp
	//if (float1.sign ^ float2.sign)
		//return sub(float1, float2);
	if (float1.exp == 0 && float1.significant == 0)
		return float2;
	if (float2.exp == 0 && float2.significant == 0)
		return float1;
	uint32_t exp_1 = float1.exp;
	uint32_t exp_2 = float2.exp;
	if(exp_1<exp_2){//Let the float1 has the larger exp.
		floatNum tmp = float1;
		float1 = float2;
		float2 = tmp;
	}
	uint32_t offset_exp = float1.exp - float2.exp;
	float2.exp = float1.exp;
	float2.significant >>= offset_exp;


	return 0;
}
floatNum sub(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val - float2.f_val;
#endif // !FPU
	return 0;
}
floatNum mul(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val * float2.f_val;
#endif // !FPU
	return 0;
}
floatNum div(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val / float2.f_val;
#endif // !FPU
	return 0;
}
