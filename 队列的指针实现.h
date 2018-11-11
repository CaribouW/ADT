#include<stdio.h>
#include<stdlib.h>

int main(){
	char p[3][4] = {
		"ABC",
		"DEF",
		"GHI"
	};
	char *q[3], **pp;

	pp = q + 2;

	q[0] = p[1];
	q[1] = p[2];
	q[3] = p[0];

	putchar(pp[-1][-2] + 3);
}