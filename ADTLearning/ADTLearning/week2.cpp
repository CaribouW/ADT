#include<iostream>
#include<cstdlib>
#ifdef LinkedList
	using namespace std;
	struct Node;
	typedef struct Node* PtrToNode;
	typedef PtrToNode head;
	typedef PtrToNode position;
	typedef PtrToNode List;

	struct Node{
		int element;
		PtrToNode next;
	};
	head Initialize(int* nums,int N);
	head Initialize(void);
	List Insert(List L, int index, int X);//insert after the index and insert to the head if index<0
	int Delete(List L, int index);
	position getByIndex(List L, int index);
	position find(List L, int element);
	position findPre(List L, int element);
	List AddSortedLists(List L1, List L2);
	int compare(position p1, position p2);

	head Initialize(int* nums, int N){
		List L = (List)malloc(sizeof(struct Node));
		if (L == NULL){
			cout << "Space overflow!\n" << endl;
			return NULL;
		}
		L->next = NULL;
		L->element = INT_MIN;
		position tmp = L;
		for (int index = 0; index < N; index++){
			position newNode = (List)malloc(sizeof(struct Node));
			if (L == NULL){
				cout << "Space overflow!\n" << endl;
				return NULL;
			}
			newNode->element = nums[index];
			newNode->next = NULL;
			tmp->next = newNode;
			newNode = tmp;
		}
		return L;
	}
	head Initialize(void){
		List L = (List)malloc(sizeof(struct Node));
		if (L == NULL){
			cout << "Space overflow!\n" << endl;
			return NULL;
		}
		L->next = NULL;
		L->element = INT_MIN;
		return L;
	}
	List Insert(List L, int index, int X){
		if (L->next == NULL){
			cout << "Empty list!\n" << endl;
			return NULL;
		}
		else if (index < 0){
			List newNode = (List)malloc(sizeof(struct Node));
			if (newNode == NULL){
				cout << "Space overflow!\n" << endl;
				return NULL;
			}
			newNode->next =L->next ;
			newNode->element = X;
			L->next = newNode;
			return L;
		}
		else{
			position tmpPos = L;
			for (int i = 0; tmpPos != NULL&& i <= index; i++){
				tmpPos = tmpPos->next;
			}
			if (tmpPos == NULL){
				cout << "The unlegal index!\n" << endl;
				return L;
			}
			else{
				List newNode = (List)malloc(sizeof(struct Node));
				if (newNode == NULL){
					cout << "Space overflow!\n" << endl;
					return NULL;
				}
				newNode->next = tmpPos->next;
				tmpPos->next = newNode;
				newNode->element = X;
				return L;
			}
		}
	}
	int Delete(List L, int index){
		if (L->next == NULL){
			cout << "Empty List!";
			return L->element;
		}
		for (int i = 0; i < index; i++){
			L = L->next;
		}
		position tmp = L->next;
		L->next = tmp->next;
		int result = tmp->element;
		free(tmp);
		return result;
	}
	List AddSortedLists(List L1, List L2){
		List ptr_1 = L1;
		List ptr_2 = L2;
		if (L1->next == NULL)return L2;
		if (L2->next == NULL)return L1;
		ptr_1 = L1->next; ptr_2 = L2->next;
		List L_result = (List)malloc(sizeof(Node));
		L_result->element = INT_MIN; L_result->next = NULL;
		while (ptr_1&&ptr_2){
			position newNode = (position)malloc(sizeof(Node));
			switch (compare(ptr_1,ptr_2))
			{
			case 0://ptr1 ptr2 insertion
				ptr_2 = ptr_2->next;
			case 1://ptr1 insertion
				newNode->element = ptr_1->element;
				newNode->next = L_result->next;
				L_result->next = newNode;
				ptr_1 = ptr_1->next;
				break;
			case -1://ptr2 insertion
				newNode->element = ptr_2->element;
				newNode->next = L_result->next;
				L_result->next = newNode;
				ptr_2 = ptr_2->next;
				break;

			default:
				break;
			}
			L_result = newNode;
		}
		if (ptr_1 == NULL&&ptr_2 == NULL)
			return L_result;
		else if (ptr_2 != NULL){

		}
	}
	int compare(position p1, position p2){
		if (p1->element > p2->element)
			return 1;
		else if (p1->element < p2->element)
			return -1;
		else
			return 0;
	}

#endif

#ifdef Poly
	using namespace std;
	class PolyNode{
	public:
		int exp;
		double val;
		PolyNode* next;
		void printPoly();
		PolyNode* insert(int val, int exp);
		PolyNode* add(const PolyNode* l1);
		PolyNode* multiple(const PolyNode* l2);
		int compareExp(const PolyNode* l1, const PolyNode* l2);
		int compareExp(const PolyNode*l1)const;
		PolyNode(){ exp = 0; val = 0; next = NULL; };
		PolyNode(int val, int exp){ 
			this->exp = exp;
			this->next = NULL; 
			this->val = val;
		};
		~PolyNode(){
			delete this;
		}

	}; 
	int PolyNode::compareExp(const PolyNode* l1, const PolyNode* l2){
		int exp_1 = l1->exp;
		int exp_2 = l2->exp;
		if (exp_1 > exp_2)
			return 1;
		else if (exp_1 < exp_2)
			return -1;
		else
			return 0;
	}
	void PolyNode::printPoly(){
		if (this == NULL){
			return;
		}
		PolyNode* ptr = this;
		while (ptr != NULL){
			if (ptr->next != NULL)
				cout << ptr->val << "x^" << ptr->exp << " +";
			else
				cout << ptr->val << "x^" << ptr->exp << endl;
			ptr = ptr->next;
		}
	}
	PolyNode* PolyNode::insert(int val, int exp){
		PolyNode* head = this;
		if (head == NULL)
			return new PolyNode(val, exp);
		else{
			PolyNode* tmpIndex = head;
			while (tmpIndex != NULL){
				int exp_current = tmpIndex->exp;
				if (exp_current == exp){
					tmpIndex->val += val;
					break;
				}
				else if (exp_current > exp){
					PolyNode* newNode = new PolyNode(val, exp);
					newNode->next = tmpIndex;
					if (tmpIndex == this)
						head = newNode;
					break;
				}
				else{
					if (tmpIndex->next == NULL){
						PolyNode* newNode = new PolyNode(val, exp);
						tmpIndex->next = newNode;
						break;
					}
					int exp_next = tmpIndex->next->exp;
					if (exp_next < exp){
						tmpIndex = tmpIndex->next;
						continue;
					}
					else if (exp_next>exp){
						PolyNode* newNode = new PolyNode(val, exp);
						newNode->next = tmpIndex->next;
						tmpIndex->next = newNode;
						break;
					}
				}
			}
		}
		return head;
	}
	PolyNode* PolyNode::add(const PolyNode* l1){
		PolyNode* head = this;
		while (l1 != NULL){
			head = head->insert(l1->val, l1->exp);
			l1 = l1->next;
		}
		return head;

	}
	PolyNode* PolyNode::multiple(const PolyNode* l1){
		PolyNode* result=NULL;
		PolyNode* tmpIndex = this;
		while (l1 != NULL){
			int val = l1->val;
			int exp = l1->exp;
			if (val == 0)continue;
			while (tmpIndex != NULL){
				result = result->insert(val*tmpIndex->val, exp*tmpIndex->exp);
				tmpIndex = tmpIndex->next;
			}
			l1 = l1->next;
		}
		return result;
	}


#endif

#ifdef stacks
	class Stack{
	public:
		char ch;
	};

#endif
#ifdef Lists
	template<typename T>
	struct ListNode{
		T data;
		ListNode<T>* link;
		ListNode(ListNode<T>* ptr = NULL){ link = ptr; };
		ListNode(const T& item, ListNode<T>* ptr = NULL){
			data = item;
			link = ptr;
		}
	};

#endif

#ifdef SingleList
	class List{
	public:

	}
};
#endif
