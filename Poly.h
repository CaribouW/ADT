/*
*3.6,
*3.7,
*3.8,
*3.9
*/

#include<stdio.h>
#include<stdlib.h>
#define MaxDegree 100000
typedef struct Node *PtrToNode;
typedef PtrToNode head;
typedef PtrToNode Polynomial;
struct Node{
	int coefficient;
	int exponent;
	PtrToNode next;
};
Polynomial Initial(const int coefficient, const int exponent);
void ZeroPolynomial(Polynomial Poly);
Polynomial AddPolynomial(const Polynomial poly1,
	const Polynomial poly2);
Polynomial MultPolynomial(const Polynomial poly1,
	const Polynomial poly2);
Polynomial ExponentPolynomial(const Polynomial poly1,
	const expCount);
void printPolynomial(const Polynomial poly);
Polynomial findBefore(const int exponent, const head poly);
void clearZero(const head poly);
/*
Change the Node's coe into the new one,
we would use GetCoefficient first.
*/
Polynomial Write(const int newCoe, const int exponent, const Polynomial poly);

/*
We organize the Poly into the exponent sorting and
put the new Node into the proper position.
*/
Polynomial Insert(int coefficient, int exponent, const head poly);
Polynomial Delete(const int expInfo, const head poly);
Polynomial find(const int expInfo, const head poly);
/*
@return  return 0 if not found
*/
int GetCoefficient(const int expInfo, const head poly);


Polynomial Initial(const int coefficient, const int exponent){
	Polynomial head = (Polynomial)malloc(sizeof(struct Node));
	if (head == NULL){
		printf("Data OverFlow when Initializing!\n");
		return NULL;
	}
	head->coefficient = coefficient;
	head->exponent = exponent;
	head->next = NULL;
}
void printPolynomial(Polynomial poly){
	if (poly == NULL){
		printf("Empty polynomial.\n");
		return NULL;
	}
	printf("F=");
	while (poly->next != NULL){
		int coe = poly->coefficient;
		int exp = poly->exponent;
		printf("%d x^(%d)+", coe, exp);
		poly = poly->next;
	}
	printf("%d x^(%d)\n", poly->coefficient, poly->exponent);
}
void ZeroPolynomial(Polynomial Poly){
	Poly->next = NULL;
	Poly->coefficient = 0;
	Poly->exponent = 0;
}
Polynomial AddPolynomial(const Polynomial poly1,
	const Polynomial poly2){
	Polynomial result = NULL;
	Polynomial tmp_1 = poly1;
	Polynomial tmp_2 = poly2;
	while (tmp_1->next != NULL){
		result = Write(tmp_1->coefficient, tmp_1->exponent, result);
		tmp_1 = tmp_1->next;
	}
	result = Write(tmp_1->coefficient, tmp_1->exponent, result);
	while (tmp_2->next != NULL){
		result = Write(tmp_2->coefficient, tmp_2->exponent, result);
		tmp_2 = tmp_2->next;
	}
	result = Write(tmp_2->coefficient, tmp_2->exponent, result);
	return result;
}

Polynomial MultPolynomial(const Polynomial poly1,
	const Polynomial poly2){
	Polynomial tmp1 = poly1;
	Polynomial tmp2 = poly2;
	int newExp = 0;
	int newCoe = 0;
	Polynomial head = NULL;
	while (tmp1->next != NULL){
		
		while (tmp2->next!=NULL){
			newExp = tmp1->exponent + tmp2->exponent;
			newCoe = tmp1->coefficient*tmp2->coefficient;
			head = Write(newCoe, newExp, head);
			tmp2 = tmp2->next;
		}
		newExp = tmp1->exponent + tmp2->exponent;
		newCoe = tmp1->coefficient*tmp2->coefficient;
		head = Write(newCoe, newExp, head);

		tmp2 = poly2;
		tmp1 = tmp1->next;
		
	}
	while (tmp2->next != NULL){
		newExp = tmp1->exponent + tmp2->exponent;
		newCoe = tmp1->coefficient*tmp2->coefficient;
		head = Write(newCoe, newExp, head);
		tmp2 = tmp2->next;
	}
	newExp = tmp1->exponent + tmp2->exponent;
	newCoe = tmp1->coefficient*tmp2->coefficient;
	head = Write(newCoe, newExp, head);
	return head;
}
Polynomial ExponentPolynomial(const Polynomial poly1,
	const expCount){
	if (expCount == 0)
		return Initial(1, 0);
	if (expCount == 1)
		return poly1;
	if (expCount == 2)
		return MultPolynomial(poly1, poly1);
	return ExponentPolynomial(poly1, expCount - 1);
}

/*
Change the Node's coe into the new one,
we would use GetCoefficient first.
*/
Polynomial Write(const int newCoe, const int exponent, const Polynomial poly){
	if (poly == NULL){
		Polynomial result = Initial(newCoe, exponent);
		return result;
	}

	Polynomial target = find(exponent, poly);
	if (target == NULL){
		target = (Polynomial)malloc(sizeof(struct Node));
		target->coefficient = newCoe;
		target->exponent = exponent;
		return Insert(newCoe, exponent, poly);
	}
	else{
		target->coefficient = newCoe;
		return poly;
	}
}
/*
We organize the Poly into the exponent sorting and
put the new Node into the proper position.
*/
Polynomial Insert(int coefficient, int exponent, const head poly){
	if (poly == NULL){
		printf("Empty poly when insertion!\n");
		return NULL;
	}
	Polynomial tmp = poly;
	Polynomial before = NULL;
	if (tmp->exponent > exponent){
		Polynomial newHead = (Polynomial)malloc(sizeof(struct Node));
		if (poly == NULL){
			printf("Empty poly when insertion!\n");
			return poly;
		}
		else{
			newHead->coefficient = coefficient;
			newHead->exponent = exponent;
			newHead->next = poly;
			return newHead;
		}
	}
	else if (tmp->exponent == exponent){
		tmp->coefficient += coefficient;
		return poly;
	}


	while (tmp->next != NULL){
		if (tmp->exponent < exponent){
			before = tmp;
			tmp = tmp->next;
			continue;
		}
		else if (exponent == tmp->exponent){
			tmp->coefficient += coefficient;
			return poly;
		}
		else{
			Polynomial current = (Polynomial)malloc(sizeof(struct Node));
			if (current == NULL){
				printf("Data OverFlow when insertion.\n");
				return poly;
			}
			else{
				current->coefficient = coefficient;
				current->exponent = exponent;
				current->next = tmp;
				before->next = current;
				return poly;
			}
		}
	}
	if (tmp->exponent == exponent){
		tmp->coefficient += coefficient;
		return poly;
	}
	else if (tmp->exponent > exponent){
		Polynomial current = (Polynomial)malloc(sizeof(struct Node));
		if (current == NULL){
			printf("Data OverFlow when insertion.\n");
			return poly;
		}
		else{
			current->coefficient = coefficient;
			current->exponent = exponent;
			current->next = tmp;
			before->next = current;
			return poly;
		}
	}
	else{
		Polynomial current = (Polynomial)malloc(sizeof(struct Node));
		if (current == NULL){
			printf("Data OverFlow when insertion.\n");
			return poly;
		}
		else{
			current->coefficient = coefficient;
			current->exponent = exponent;
			current->next = NULL;
			tmp->next = current;
			return poly;
		}
	}
}
Polynomial Delete(const int expInfo, const head poly){
	if (poly == NULL){
		printf("Empty Poly When deleting!\n");
		return NULL;
	}
	if (poly->exponent == expInfo){
		Polynomial tmp = poly->next;
		free(poly);
		return tmp;
	}

	Polynomial before = findBefore(expInfo, poly);
	Polynomial current = before->next;
	before->next = before->next->next;
	free(current);
	return poly;
}
/*
@return  return 0 if not found
*/
int GetCoefficient(const int expInfo, const head poly){
	Polynomial tmp = find(expInfo, poly);
	if (tmp == NULL)
		return 0;
	return tmp->coefficient;
}
Polynomial find(const int expInfo, const head poly){
	if (poly == NULL){
		printf("Empty poly!\n");
		return NULL;
	}
	Polynomial tmp = poly;
	while (tmp->next != NULL)	{
		if (tmp->exponent < expInfo){
			return NULL;
		}
		if (expInfo == tmp->exponent)
			return tmp;
		tmp = tmp->next;
	}
	if (tmp->exponent == expInfo)
		return tmp;
	return NULL;
}

Polynomial findBefore(const int exponent, const head poly){
	if (poly == NULL){
		printf("Empty poly when find before!\n");
		return NULL;
	}
	Polynomial tmp = poly;
	while (tmp->next != NULL){
		if (tmp->next->exponent == exponent){
			return tmp;
		}
		tmp = tmp->next;
	}
}
void clearZero(const head poly){
	Polynomial tmp = poly;
	while (tmp->next != NULL){
		if (tmp->coefficient == 0)
			tmp = Delete(tmp->exponent, tmp);
		tmp = tmp->next;
	}
	if (tmp->coefficient == 0)
		tmp = Delete(tmp->exponent, tmp);
}