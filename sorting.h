#include<iostream>
using namespace std;
void InsertionSort(int* nums, int N);
void ShellSort(int* nums, int N);

void InsertionSort(int* nums, int N){
	if (N == 1)
		return;
	int index = 1;
	int j;
	for (; index < N; index++){
		int baseNum = nums[index];
		for (j = index; j > 0; j--){
			if (nums[j - 1]>baseNum){
				nums[j] = nums[j - 1];
			}
			else{
				break;
			}
		}
		nums[j] = baseNum;
	}
}

void ShellSort(int* nums, int N){
	if (N == 1){
		return;
	}
	int Increment, i, j;
	for (Increment = N / 2; Increment > 0; Increment /= 2){
		for (i = Increment; i < N; i++){
			int baseNum = nums[i];
			for (j = i; j >= Increment; j -= Increment){
				if (baseNum < nums[j - Increment]){
					nums[j] = nums[j - Increment];
				}
				else{
					break;
				}
			}
			nums[j] = baseNum;
		}

	}

}
void printVector(int *nums, int N){
	cout << "[";
	for (int index = 0; index < N; index++){
		cout << nums[index] << ",";
	}
	cout << "]\n";
}
