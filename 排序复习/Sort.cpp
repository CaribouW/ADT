#include"Sort.h"
#include<iostream>

void Sort::bubble_sort(int* nums, int N){
	using namespace std;
	/**
	* float the max num up to the top
	*/
	cout << "before------" << endl;
	print_arr(nums, N);
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N - i - 1; j++)
			if (nums[j]>nums[j + 1])
				swap(nums, j, j + 1);
	}
	cout << "after-------" << endl;
	print_arr(nums, N);
}
void Sort::select_sort(int* nums, int N){
	using namespace std;
	/**
	* every time we put the minum num to the left most positon
	*/
	cout << "before------" << endl;
	print_arr(nums, N);
	for (int i = 0; i < N; i++){
		for (int j = i + 1; j < N; j++){
			if (nums[i] > nums[j])
				swap(nums, i, j);
		}
	}
	cout << "after-------" << endl;
	print_arr(nums, N);
}
void Sort::insert_sort(int* nums, int N){
	using namespace std;
	/*
	* insert the i + 1 element to the appropriate position.
	*/
	cout << "before------" << endl;
	print_arr(nums, N);
	for (int i = 0; i < N - 1; i++){
		int element = nums[i + 1];
		int j = i;
		for (; j >= 0; j--){
			if (nums[j] > element){
				nums[j + 1] = nums[j];
			}
			else
				break;
		}
		nums[j + 1] = element;
		print_arr(nums, N);
	}
	cout << "after-------" << endl;
	print_arr(nums, N);
}
void Sort::binary_insert_sort(int* nums, int left, int right){
	using namespace std;
	cout << "before------" << endl;
	int size = right - left + 1;
	print_arr(nums, size);
	for (int i = left + 1; i <= right; i++){
		int right_index = i - 1;
		int left_index = left;
		int element = nums[i];
		while (left_index <= right_index){
			int middle = (left_index + right_index) / 2;
			if (nums[middle] > element)
				right_index = middle - 1;
			else
				left_index = middle + 1;
		}
		int k;
		for (k = i - 1; k >= left_index; k--)
			nums[k + 1] = nums[k];
		nums[k + 1] = element;
		print_arr(nums, size);
	}
	cout << "after-------" << endl;
	print_arr(nums, size);
}
void Sort::shell_sort(int* nums, int N){
	using namespace std;
	cout << "before------" << endl;
	print_arr(nums, N);
	for (int increment = N; increment >= 1; increment = increment / 3){
		for (int i = increment; i < N; i++){
			int element = nums[i + increment];
			int j = i;
			for (; j >= 0; j -= increment){
				if (nums[j] > element)
					nums[j + increment] = nums[j];
				else
					break;
			}
			nums[j + increment] = element;
			print_arr(nums, N);
		}
	}
	cout << "after-------" << endl;
	print_arr(nums, N);
}
void Sort::merge_sort(int* nums, int left, int right){
	using namespace std;
	if (right - left < 1){
		//binary_insert_sort(nums, left, right);
		return;
	}
	int size = right - left + 1;
	cout << "before------" << endl;
	print_arr(nums, size);

	int middle = (left + right) / 2;
	merge_sort(nums, left, middle);
	merge_sort(nums, middle + 1, right);
	int* tmp_arr = new int[size];

	int left_index = left, left_bound = middle;
	int right_index = middle + 1, right_bound = right;
	int index = 0;
	while (left_index <= left_bound&&right_index <= right_bound){
		if (nums[left_index] == nums[right_index]){
			tmp_arr[index++] = nums[left_index++];
			tmp_arr[index++] = nums[right_index++];
		}
		else if (nums[left_index] < nums[right_index]){
			tmp_arr[index++] = nums[left_index++];
		}
		else if (nums[left_index] > nums[right_index]){
			tmp_arr[index++] = nums[right_index++];
		}
	}
	while (left_index <= left_bound)
		tmp_arr[index++] = nums[left_index++];
	while (right_index <= right_bound)
		tmp_arr[index++] = nums[right_index++];
	for (int i = 0; i < size; i++)
		nums[left + i] = tmp_arr[i];
	cout << "after-------" << endl;
	print_arr(nums, size);
}


void Heap::buildHeap(int* nums, int N){
	for (int i = (N - 2) / 2; i >= 0; i--)
		scroDown(nums, i, N - 1);
}
void Heap::scroUp(int* nums, int end){
	int index = end;
	int element = nums[end];
	for (; index > 0; index = Father(index)){
		int father_index = Father(index);
		if (nums[father_index] < nums[index]){
			nums[index] = nums[father_index];
		}
		else
			break;
	}
	nums[index] = element;
}
void Heap::scroDown(int* nums, int begin, int end){
	int index = begin;
	int element = nums[begin];
	for (int child_index = Childern(index);
		Childern(index) <= end; index = child_index){
		if (child_index != end&&
			nums[child_index] < nums[child_index + 1]){
			child_index++;
		}
		if (nums[index] < nums[child_index])
			nums[index] = nums[child_index];
		else
			break;
	}
	nums[index] = element;
}