#include<stdio.h>
#include<stdlib.h>
void InsertionSort(int* nums, int N);
void InsertionSortNormal(int* nums, int N);
void swap(int* nums, int left, int right);
void swapTwo(int*num2, int* num1);
void printArr(int* nums, int N);
void ShellSort(int* nums, int N);
void HeapSort(int* nums, int N);
void MergeSort(int*nums, int N);
void merge(int*A, int*B, int left, int right);
void ConductMerge(int*A, int*B, int leftPos, int rightPos, int rightEnd);
void quickSort(int* nums, int N);
void QSort(int* nums, int left, int right);
int MedianThree(int* nums, int left, int right);
void quickSelect();


void swap(int* nums, int left, int right){
	int tmp = nums[left];
	nums[left] = nums[right];
	nums[right] = tmp;
}
void swapTwo(int*num2, int* num1){
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}
void printArr(int* nums, int N){
	printf("[");
	for (int index = 0; index < N; index++)
		printf("%d,", nums[index]);
	printf("]\n");
}
void InsertionSort(int* nums, int N){
	int j, P;
	int tmp;
	for (P = 1; P < N; P++){
		tmp = nums[P];
		for (j = P; j > 0 && nums[j - 1] > tmp; j--){
			nums[j] = nums[j - 1];
		}
		nums[j] = tmp;
	}//Decrease the time used during the swap process.
}
void InsertionSortNormal(int* nums, int N){
	for (int P = 1; P < N; P++){
		for (int j = P; j > 0; j--){
			if (nums[j] < nums[j - 1])
				swap(nums, j, j - 1);
			else
				break;
		}
	}
}
void ShellSort(int* nums, int N){
	int i, j, Increment;
	int tmp;

	for (Increment = N / 2; Increment > 0; Increment /= 2){//Define the increment of the sorting process
		for (i = Increment; i < N; i++){
			tmp = nums[i];
			for (j = i; j >= Increment; j -= Increment){
				if (tmp < nums[j - Increment]){
					nums[j] = nums[j - Increment];
				}
				else
					break;
			}
			nums[j] = tmp;
		}
	}
}
void HeapSort(int* nums, int N){

}
void MergeSort(int*nums, int N){
	int *tmpArr = (int*)malloc(sizeof(int)*N);
	if (tmpArr){
		merge(nums, tmpArr, 0, N - 1);
		free(tmpArr);
	}
	else{
		printf("Data error!\n");
	}
}
void merge(int*A, int*B, int left, int right){
	int center = (left + right) / 2;
	if (left < right){
		merge(A, B, left, center);
		merge(A, B, center + 1, right);
		ConductMerge(A, B, left, center + 1, right);
	}
}

void ConductMerge(int*A, int*B, int leftPos, int rightPos, int rightEnd){
	int leftEnd = rightPos - 1;
	int size = rightEnd - leftPos + 1;
	int index = leftPos;

	while (leftPos <= leftEnd&&rightPos <= rightEnd){
		if (A[leftPos] <= A[rightPos])
			B[index++] = A[leftPos++];
		else
			B[index++] = A[rightPos++];
	}
	while (leftPos <= leftEnd)B[index++] = A[leftPos++];
	while (rightPos <= rightEnd)B[index++] = A[rightPos++];
	for (int i = 0; i < size; i++)
		A[i] = B[i];
}

void quickSort(int* nums, int N){
	QSort(nums, 0, N - 1);
}

void QSort(int* nums, int left, int right){
	int i, j;
	int pivot;
	if (right - left >= 10){
		pivot = MedianThree(nums, left, right);
		i = left;
		j = right - 1;
		for (;;){
			while (nums[++i] < pivot){}
			while (nums[--j] > pivot){}
			if (i < j){
				swapTwo(&nums[i], &nums[j]);
			}
			else break;
		}
		swapTwo(&nums[i], &nums[right - 1]);
		QSort(nums, left, i - 1);
		QSort(nums, i + 1, right);
	}
	else{
		InsertionSort(nums + left, right - left + 1); 
	}

}

int MedianThree(int* nums, int left, int right){
	int center = (left + right) / 2;
	if (nums[left]>nums[center])
		swapTwo(&nums[left], &nums[center]);
	if (nums[left] > nums[right])
		swapTwo(&nums[left], &nums[right]);
	if (nums[center] > nums[right])
		swapTwo(&nums[center], &nums[right]);
	swapTwo(&nums[center], &nums[right - 1]);
	return nums[right - 1];

}
int main(){

}