#include<iostream>
using namespace std;

#ifdef print
inline void printChars(char* str){
	int index = 0;
	while (str[index++])cout << str[index - 1] << endl;
}
#endif
#ifdef SUB_SUM
int max3(int a, int b, int c);
int maxBorderSum(int* nums, int left, int right);
int maxSubSum(int* nums, int N);
int maxSubSum(int* nums, int left, int right);

int max3(int a, int b, int c){
	if (a > b){
		return a > c ? a : c;
	}
	else{
		return b > c ? b : c;
	}
}
int maxBorderSum(int* nums, int left, int right){
	int leftBorderSum = 0, leftMax = 0;
	int rightBorderSum = 0, rightMax = 0;
	int center = (left + right) / 2;
	for (int index = center; index >= left; index--){
		leftBorderSum += nums[index];
		if (leftBorderSum > leftMax)
			leftMax = leftBorderSum;
	}
	for (int index = center + 1; index <= right; index++){
		rightBorderSum += nums[index];
		if (rightBorderSum > rightMax)
			rightMax = rightBorderSum;
	}
	return leftMax + rightMax;
}
int maxSubSum(int* nums, int N){
	return maxSubSum(nums, 0, N - 1);
}
int maxSubSum(int* nums, int left, int right){
	if (left == right){
		return nums[left];
	}
	int center = (left + right) / 2;
	int LeftMaxSubSum = maxSubSum(nums, left, center);
	int RightMaxSubSum = maxSubSum(nums, center + 1, right);
	int MaxBorderSum = maxBorderSum(nums, left, right);
	return max3(LeftMaxSubSum, RightMaxSubSum, MaxBorderSum);
}

#endif
#ifdef BinarySearch
int BinarySearches(int* nums, int N,int target);
int BinarySearches(int* nums, int left, int right,int target);

int BinarySearches(int* nums, int N,int target){
	return BinarySearches(nums, 0, N - 1,target);
}
int BinarySearches(int* nums, int left, int right,int target){
	int center = (left + right) / 2;
	if (left < right){
		if (nums[center]>target)
			return BinarySearches(nums, left, center - 1, target);
		else if (nums[center] < target)
			return BinarySearches(nums, center + 1, right, target);
		else
			return center;
	}
	else if (left == right){
		return center;
	}
	else
		return -1;
}


#endif
int main(){

	cin.get();
}