#ifdef MaxSubsequence
#include<iostream>
using namespace std;
static int* maxSubSum(int* nums, int left, int right);
static int* getMax(int*nums, int left, int right){
	int* result = new int[]{-1024, left,left};
	int tmpSum = 0;
	for (int i = left; i <= right; i++){
		tmpSum += nums[i];
		if (result[0] < tmpSum){
			result[0] = tmpSum;
			result[2] = i;
		}
	}
	return result;
}
int* maxSubSequence(int* nums, int N){
	return maxSubSum(nums, 0, N - 1);
}
int* maxSubSum(int* nums, int left, int right){
	int* leftMaxSum, *rightMaxSum;
	int* leftBorderSum, *rightBorderSum;
	int* maxSum = new int[3];
	if (left == right)
		maxSum = nums[left];
	else
		if (left < right){
			int center = (left + right) / 2;
			leftMaxSum = maxSubSum(nums, left, center - 1);
			rightMaxSum = maxSubSum(nums, center + 1, right);
			leftBorderSum = getMax(nums, left, center);
			rightBorderSum = getMax(nums, center, right);
			maxSum = max3(leftMaxSum, rightMaxSum, leftBorderSum + rightBorderSum);
		}
	return maxSum;
}
int main(){
	int N;
	cin >> N;
	int begin = 0, end = N - 1;
	int* nums = new int[N];
	for (int i = 0; i < N; i++)
		cin >> nums[i];
}


#endif
