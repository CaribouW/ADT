#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

enum KindOfEntry{
	Legitimate,Empty,Deleted
};
struct HashEntry{
	int element;
	enum KindOfEntry info;
};
typedef struct HashEntry Cell;
struct HashTbl{
	int TableSize;
	Cell *PtrToCell;
};


HashTable InitializeTable(int size);
void DestroyTable(HashTable H);
Position Find(int key, HashTable H);
void Insert(int key, HashTable H);
HashTable ReHash(HashTable H);
int NextPrime(int base);
Position Hash(int key, int size);


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
HashTable InitializeTable(int size){
	HashTable H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL){
		printf("No space for HashTable!\n");
		return NULL;
	}
	H->TableSize = size;
	H->PtrToCell = (Cell*)malloc(sizeof(struct HashEntry)*size);
	if (H->PtrToCell == NULL){
		printf("No space for cells!\n");
		return NULL;
	}
	for (int i = 0; i < size; i++)
		H->PtrToCell[i].info = Empty;
	return H;
}
Position Find(int key, HashTable H){
	Position CurrentPos;
	int CollisionNum = 0;

	CurrentPos = Hash(key, H->TableSize);
}