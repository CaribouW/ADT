#include"fpu.h"
inline floatNum nomalization(uint32_t sign, uint32_t exp, uint32_t significant){
	uint32_t sticky = 0;
	bool overflow = false;
	uint32_t tmpTag = significant >> (23 + 3);
	if (tmpTag > 1){ //case 1xxxxx.xxxx
		while (((significant >> (23 + 3) > 1) &&
			(exp < 0xff)) ||
			(exp < 0 && significant>0x04)
			){
			sticky = sticky | (significant & 0x1);
			significant >>= 1;
			exp++;
			significant |= sticky;
		}
		if (exp == 0xff){
			overflow = true;
			std::cout << "over flow!\n";
			significant = 0;
		}
		sticky = 0;
		if (exp == 0){
			sticky |= (significant & 0x01);
			significant >>= 1;
			significant |= sticky;
		}
		if (exp < 0){
			/*
			The div operation generater a float that is too small.
			*/
			significant = 0;
			exp = 0;
			overflow = true;
		}
	}
	else if (tmpTag == 0){//case 0.0000xxxxx
		while ((significant >> (23 + 3) == 0) &&
			(exp > 0)){
			significant <<= 1;
			exp--;
		}
		sticky = 0;
		if (exp == 0){
			sticky |= (significant & 0x01);
			significant >>= 1;
			significant |= sticky;
		}
	}
	else if (exp == 0 && tmpTag == 1){
		/*Two denormal get normal*/
		exp++;
	}
	if (!overflow){
		uint32_t srg = significant & 0x07;
		if (srg > 0x04){
			significant += 0x08;
		}
		else if (srg == 0x04){
			if (significant & 0x08 == 1){
				significant += 0x08;
			}
		}
		if ((significant >> (23 + 3) > 1) || exp < 0){
			return nomalization(sign, exp, significant);
		}
		else{
			significant >>= 3;
			significant &= 0x7fffff;
		}
	}
	floatNum result(1);
	result.sign = sign;
	result.significant = (uint32_t)(significant & 0xff);
	result.exp = exp;
	return result;
}
floatNum add(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val + float2.f_val;
#endif // !FPU
	//1. check exp
	//if (float1.sign ^ float2.sign)
	//return sub(float1, float2);
	floatNum result = 0;
	if (float1.exp == 0 && float1.significant == 0)
		return float2;
	if (float2.exp == 0 && float2.significant == 0)
		return float1;
	if (float1.exp < float2.exp){//Let the float1 has the larger exp.
		floatNum tmp = float1;
		float1 = float2;
		float2 = tmp;
	}
	uint32_t exp_1 = float1.exp == 0 ? float1.exp - 126 : float1.exp - 127;
	uint32_t exp_2 = float2.exp == 0 ? float2.exp - 126 : float2.exp - 127;
	uint32_t sig_1 = float1.exp == 0 ? float1.significant : (0x800000 | float1.significant);
	uint32_t sig_2 = float2.exp == 0 ? float2.significant : (0x800000 | float2.significant);
	sig_1 = sig_1 << 3;
	sig_2 = sig_2 << 3; //Get three guard bits.
	uint32_t offset_exp = exp_1 - exp_2;
	uint32_t sticky = 0;
	while (offset_exp > 0){
		sticky = sticky | (0x1 & sig_2);
		exp_2++;
		sig_2 = sig_2 >> 1;
		sig_2 |= sticky;
		offset_exp--;
	}
	if (sig_2 < 0x7)
		return float1;
	if (float1.sign)
		sig_1 *= -1;
	if (float2.sign)
		sig_2 *= -1;
	uint32_t significant = sig_1 + sig_2;
	if (sign(significant)){
		result.sign = 1;
		significant *= -1;
	}
	else{
		result.sign = 0;
	}
	/*We have to nomalize*/


}
floatNum sub(floatNum float1, floatNum float2){
#ifndef FPU
	return float1.f_val - float2.f_val;
#endif // !FPU
	float2.sign = ~float2.sign;
	return add(float1, float2);
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
