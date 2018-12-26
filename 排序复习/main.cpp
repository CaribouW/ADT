#include"Sort.h"
int main(){
	using namespace std;
	//int* nums = new int[]{1, 4, 10, 3, 6, -1, 32, 5, 14, -100};
	int nums[] = { 4, 3, 2, 1, 5, 21, -4212, 412, 10 };
	Sort* s = new Sort();
	Heap* H = new Heap(4);
	H->heap_sort(nums, 9);
	delete[] nums;
	delete s;
	return 0;
}