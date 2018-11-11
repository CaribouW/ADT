#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct ListNode;
typedef struct ListNode *Position;
typedef Position List;
struct HashTbl;
typedef struct HashTbl *HashTable;

struct ListNode{
	int element;
	Position next;
};

struct HashTbl{
	int size;
	List *PtrToList;
};

HashTable InitializeTable(int size);
void DestroyTable(HashTable H);
Position Find(int key, HashTable H);
void Insert(int key, HashTable H);
int Retrieve(Position P);
int Hash(int key, int size);
void Delete(int key, HashTable H);
int NextPrime(int base);


HashTable InitializeTable(int size){
	HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL){
		printf("No space for HashTable!\n");
		return NULL;
	}
	H->size = size;
	H->PtrToList = (List*)malloc(sizeof(List)*H->size);
	if (H->PtrToList == NULL){
		printf("No space for the Lists!\n");
		return NULL;
	}
	for (int i = 0; i < H->size; i++){
		H->PtrToList[i] = (List)malloc(sizeof(struct ListNode));
		H->PtrToList[i]->element = 0;
		H->PtrToList[i]->next = NULL;
	}
	return H;
}
void DestroyTable(HashTable H){
	for (int i = 0; i < H->size; i++){
		free(H->PtrToList[i]);
	}
	free(H->PtrToList);
	free(H);
}

Position Find(int key, HashTable H){
	List L = H->PtrToList[Hash(key, H->size)];
	Position P = L->next;
	while (P != NULL&&P->element != key)
		P = P->next;
	return P;
}
void Insert(int key, HashTable H){
	Position P = Find(key, H);
	if (P == NULL){
		Position newNode = (Position)malloc(sizeof(struct ListNode));
		if (newNode == NULL){
			printf("No space for new node.\n");
			return;
		}
		List L = H->PtrToList[Hash(key, H->size)];
		newNode->next = L->next;
		L->next = newNode;
		newNode->element = key;
	}
}
void Delete(int key, HashTable H){
	List L = H->PtrToList[Hash(key, H->size)];
	Position P = L;
	while (P->next != NULL&&P->next->element != key)
		P = P->next;
	if (P->next != NULL){
		Position tmpNode = P->next;
		P->next = tmpNode->next;
		free(tmpNode);
		return;
	}


	int NextPrime(int base){
		if (base <= 1)
			return 2;
		int result;
		int flag = 0;
		for (result = base + 1;; result++){
			flag = 1;
			for (int i = 2; i < sqrt((double)result); i++){
				if (result%i == 0){
					flag = 0;
					break;
				}
			}
			if (flag == 1)
				break;
		}
		return result;
	}