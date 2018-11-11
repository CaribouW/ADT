#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node* List;

struct Node{
	int num;
	int position;
	List next;
};

void printList(List L);
List getList(int);
void Insert(int num, int p, List L);                //在索引p的位置之后插入元素num
void Add(int num, List L);
List deleteNode(int p, List L);                  //删除索引为P的第一个元素
List findBeforeByIndex(int p, List L);           //得到p索引的前驱元
List findByIndex(int index, List L);
int getIndex(int num, List L);                   //找到第一个num元素的索引，若找不到则返回-1
int getNum(int index, List L);                   //返回索引为index的元素
List getPtr(int index, List L);                  //得到索引对应的指针
int getSize(List);                               //得到List的节点个数 
void addList(List L1, List L2);                  //将链表L2加到L1链表末尾
void IndexAdjust(List L);                        //将链表下标进行调整
List Swap(int index1, int index2, List L);       //交换index1和index2索引的元素位置
int contain(int num, List L);                    //若包含某个元素则返回1，否则返回0
List Intersection(List L1, List L2);             //求得L1,L2的交集
List Union(List L1, List L2);                    //求得L1,L2的并集
List sort(List L);                               //升序排序

int getSize(List L){
	int count = 0;
	while (L->next != NULL){
		L = L->next;
		count++;
	}
	return count+1;
}

List getList(int num){
	List head = (List)malloc(sizeof(struct Node));

	if (head == NULL)
		printf("Data error!\n");
	head->position = 0;
	head->next = NULL;
	head->num = num;

	return head;
}

void Insert(int num, int p, List L){
	List ptr = L;
	
	List newNode = (List)malloc(sizeof(struct Node));

	if (ptr->next == NULL&&ptr->position==p){
		ptr->next = newNode;
    	newNode->next = NULL;
		newNode->position = 1;
		newNode->num = num;
		return;
	}//如果列表为空

	while (ptr->next != NULL&&ptr->position < p)
		ptr = ptr->next;                         //找到索引为p的位置，或者是最后一个位置
	if (ptr->position < p){
		printf("Index out of bound!\n");
		return;
	}//如果到了最后一个位置还没找到p，则这个p太大了
	
	newNode->next = ptr->next;
	ptr->next = newNode;
	newNode->num = num;
	newNode->position = ptr->position + 1;

	IndexAdjust(newNode);
}

void Add(int num, List L){
	List tmp = L;

	while (tmp->next != NULL)
		tmp= tmp->next;
	List newNode = (List)malloc(sizeof(struct Node));
	tmp->next = newNode;
	newNode->next = NULL;
	newNode->num = num;
	IndexAdjust(tmp);
}

List deleteNode(int p, List L){
	List tmp = L;

	if (tmp->next == NULL){
		printf("The List has been cleared.\n");
		free(L);
		return NULL;
	}

	while (tmp->next != NULL&&tmp->position < p)
		tmp = tmp->next;

	if (tmp->next == NULL&&tmp->position < p){
		printf("Index out of bound!\n");
		return L;
	}
	if (p == 0){
		List k = L->next;
		free(L);
		IndexAdjust(k);
		return k;
	}
	else if(p>0){
		tmp = findBeforeByIndex(p, L);
		List Node = tmp->next;
		tmp->next = Node->next;
		free(Node);

		IndexAdjust(tmp);
		return tmp;
	}
}

List findBeforeByIndex(int p, List L){
	List tmp = L;

	while (tmp->next != NULL&&tmp->next->position < p)
		tmp = tmp->next;

	return tmp;
}

int getIndex(int num, List L){
	List tmp = L;

	while (tmp->next != NULL&&tmp->num != num)
		tmp = tmp->next;
	if (tmp->next == NULL&&tmp->num != num)
		return -1;
	if (tmp->num == num)
		return tmp->position;
}

int getNum(int index, List L){
	List tmp = L;
	if (getSize(tmp) -1< index ){
		printf("Index out of bound!\n");
		return -1;
	}

	while (tmp->next != NULL&&tmp->position < index)
		tmp = tmp->next;
	if (tmp->position==index)
		return tmp->num;
}

List getPtr(int index, List L){
	while (L->next != NULL){
		if (L->position == index)
			return L;
		L = L->next;
	}
	if (L->position == index)
		return L;
	return NULL;
}

void addList(List L1, List L2){
	List tmp = L1;

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = L2;

	IndexAdjust(tmp);
}

void IndexAdjust(List L){
	while (L->next != NULL){
		int p = L->position;
		L = L->next;
		L->position = p + 1;
	}
}

void printList(List L){
	List tmp = L;

	putchar('[');
	while (tmp->next != NULL){
		printf("%d,", tmp->num);
		tmp = tmp->next;
	}
	printf("%d]\n", tmp->num);
}

List findByIndex(int index, List L){
	if (index == 0)
		return L;
	List tmp = findBeforeByIndex(index,L);
	return tmp->next;
}
/*
List Swap(int index1, int index2, List L){
	int indexBound = getSize(L) - 1;
	if (index1 == index2 || index1 < 0 || index2 < 0)
		return L;
	if (index1 > index2){
		int tmp = index1;
		index1 = index2;
		index2 = tmp;
	}

	if (getSize(L) == 2){
		List tmp1 = findByIndex(index1, L);
		List tmp2 = tmp1->next;

		tmp2->next = tmp1;
		tmp1->next = NULL;
		tmp2->position = tmp1->position;
		IndexAdjust(tmp2);
		return tmp2;
	}
	if (index2 - index1 == 1){
		if (index1 == 0){
			List tmp1 = findByIndex(index1, L);
			List tmp2 = tmp1->next;
			List After2 = tmp2->next;

			tmp2->next = tmp1;
			tmp1->next = After2;
			tmp2->position = tmp1->position;
			IndexAdjust(tmp2);
			return tmp2;
		}
		else if (index2 == getSize(L) - 1){
			List Before1 = findBeforeByIndex(index1, L);
			List tmp1 = Before1->next;
			List tmp2 = tmp1->next;

			Before1->next = tmp2;
			tmp2->next = tmp1;
			tmp1->next = NULL;
			tmp2->position = tmp1->position;
			IndexAdjust(tmp2);
			return L;
		}
		else {
			List Before1 = findBeforeByIndex(index1, L);
			List tmp1 = Before1->next;
			List tmp2 = tmp1->next;

			Before1->next = tmp2;
			tmp2->next = tmp1;
			tmp2->position = tmp1->position;
			IndexAdjust(tmp2);
			return L;
		}
	}
	if (index1 == 0 && index2 == indexBound){
		List Before2 = findBeforeByIndex(index2, L);
		List tmp1 = findByIndex(index1, L);
		List tmp2 = findByIndex(index2, L);
		List After1 = tmp1->next;
		tmp2->next = After1;
		Before2->next = tmp1;
		tmp1->next = NULL;
		tmp2->position = tmp1->position;
		IndexAdjust(tmp2);
		return tmp2;
	}

	if (index1 == 0 && index2 < indexBound){
		List tmp1 = findByIndex(index1, L);
		List tmp2 = findByIndex(index2, L);
		List After1 = tmp1->next;
		List After2 = tmp2->next;
		List Before2 = findBeforeByIndex(index2, L);

		tmp1->next = After2;
		Before2->next = tmp1;
		tmp2->next = After1;
		tmp2->position = tmp1->position;
		IndexAdjust(tmp2);
		return tmp2;
	}
	if (index1 > 0 && index2 == indexBound){
		List Before1 = findBeforeByIndex(index1, L);
		List Before2 = findBeforeByIndex(index2, L);
		List tmp1 = Before1->next;
		List tmp2 = Before2->next;
		List After1 = tmp1->next;

		tmp2->next = After1;
		Before1->next = tmp2;
		Before2->next = tmp1;
		tmp1->next = NULL;
		tmp2->position = tmp1->position;
		IndexAdjust(tmp2);
		return L;
	}
	if (index1 > 0 && index2 < indexBound){
		List Before1 = findBeforeByIndex(index1, L);
		List tmp1 = Before1->next;
		List After1 = tmp1->next;

		List Before2 = findBeforeByIndex(index2, L);
		List tmp2 = Before2->next;
		List After2 = tmp2->next;

		Before1->next = tmp2;
		tmp2->next = After1;
		Before2->next = tmp1;
		tmp1->next = After2;
		tmp2->position = tmp1->position;
		IndexAdjust(tmp2);
		return L;
	}

} //交换index1和index2索引的元素位置,首先默认让index1小于index2
*/
List Swap(int index1, int index2, List L){
	List tmp1 = findByIndex(index1, L);
	List tmp2 = findByIndex(index2, L);

	int tmp = tmp1->num;
	tmp1->num = tmp2->num;
	tmp2->num = tmp;

	return L;
}
int contain(int num, List L){
	while (L->next != NULL){
		if (L->num == num)
			return 1;
		L = L->next;
	}
	return (L->num == num) ? 1 : 0;
}

List Intersection(List L1, List L2){
	List result = getList(L1->num);
	while (L2->next != NULL){
		if (contain(L2->num, L1)){
			Add(L2->num, result);
		}
		L2 = L2->next;
	}//遍历L2链表，  如果有相同的，那么就存入；不同的就跳过。
	if (contain(L2->num, L1))
		Add(L2->num, result);
	result->next->position = 0;
	return deleteNode(0, result);
}

List Union(List L1, List L2){
	List result = getList(0);
	List tmp1 = L1;

	while (tmp1->next != NULL){
		Add(tmp1->num, result);
		tmp1 = tmp1->next;
	}
	while (L2->next != NULL){
		if (!contain(L2->num, L1))
			Add(L2->num, result);
		L2 = L2->next;
	}
	if (!contain(L2->num, L1))
		Add(L2->num, result);
	result->next->position = 0;
	return deleteNode(0, result);
}

List sort(List L){
	int size = getSize(L);

	for (int i = 0; i < size ; i++){
		for (int j = i + 1; j < size; j++){
			if (getNum(i, L) >=getNum(j, L))
				L = Swap(i, j, L);
		}
	}
	return L;
}//升序排序