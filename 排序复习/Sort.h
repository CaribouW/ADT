#include<iostream>
#define Childern(x)(2*(x)+1)
#define Father(x)((x+1)/2 -1)
class Sort{
public:
	void bubble_sort(int* nums, int N);
	void select_sort(int* nums, int N);
	void insert_sort(int* nums, int N);
	void binary_insert_sort(int* nums, int left, int right);
	void shell_sort(int* nums, int N);
	void quick_sort(int* nums, int N){
		using namespace std;
		cout << "before------" << endl;
		print_arr(nums, N);
		quick_sort(nums, 0, N - 1);
		cout << "after-------" << endl;
		print_arr(nums, N);
	}

	void merge_sort(int * nums, int N){
		merge_sort(nums, 0, N - 1);
	}

	void swap(int* nums, int index_a, int index_b){
		int tmp = nums[index_a];
		nums[index_a] = nums[index_b];
		nums[index_b] = tmp;
	}
	void print_arr(int* nums, int N){
		using namespace std;
		cout << "[";
		for (int i = 0; i < N - 1; i++)
			cout << nums[i] << ',';
		cout << nums[N - 1] << ']' << endl;
	}
	void print_arr(int* nums, int left, int right){
		using namespace std;
		cout << "[";
		for (int i = left; i < right; i++)
			cout << nums[i] << ',';
		cout << nums[right] << ']' << endl;
	}
private:
	void merge_sort(int* nums, int left, int right);
	void quick_sort(int* nums, int left, int right){
		if (right - left < 2){
			binary_insert_sort(nums, left, right);
			return;
		}
		int pivot_pos = partition(nums, left, right);
		print_arr(nums, left, right);
		quick_sort(nums, left, pivot_pos - 1);
		quick_sort(nums, pivot_pos + 1, right);
	}
	int median3(int* nums, int left, int right){
		int mid = (left + right) / 2;
		if (nums[left] > nums[mid])
			swap(nums, left, right);
		if (nums[mid] > nums[right])
			swap(nums, mid, right);
		if (nums[left] > nums[right])
			swap(nums, left, right);
		swap(nums, mid, right);
		return nums[right];
	}
	int partition(int* nums, int left, int right){
		int i = left; int j = right - 1;
		if (left < right){
			int pivot = median3(nums, left, right);
			for (;;){
				while (i < j&&nums[i] < pivot)
					++i;
				while (i < j&&nums[j] > pivot)
					--j;
				if (i < j){
					swap(nums, i++, j--);
				}
				else
					break;
			}
			if (nums[i]>pivot){
				nums[right] = nums[i];
				nums[i] = pivot;
			}
		}
		return i;
	}
};

class Heap{
public:
	Heap(int n){
		this->size = n;
		nums = new int[n];
		for (int i = 0; i < n; i++)
			nums[i] = 0;
	}
	~Heap(){
		delete[] nums;
	}
	void heap_sort(int* nums, int N){
		using namespace std;
		cout << "before------" << endl;
		print_arr(nums, N );
		heap_sort(nums, 0, N - 1);
		cout << "after-------" << endl;
		print_arr(nums, N );
	}
	void buildHeap(int* nums, int N);
	void scroUp(int* nums, int end);
	void scroDown(int* nums, int begin, int end);
	int delete_max(int* nums);
	void print_heap(int* nums, int begin, int end);

private:
	int size;
	int* nums;
	void heap_sort(int* nums, int left, int right){
		buildHeap(nums, right - left + 1);
		print_arr(nums, left, right);
		for (int i = right; i >= left; i--){
			swap(nums, left, i);
			scroDown(nums, left, i - 1);
			print_arr(nums, left, right);
		}
	}
	void swap(int* nums, int index_a, int index_b){
		int tmp = nums[index_a];
		nums[index_a] = nums[index_b];
		nums[index_b] = tmp;
	}
	void print_arr(int* nums, int N){
		using namespace std;
		cout << "[";
		for (int i = 0; i < N - 1; i++)
			cout << nums[i] << ',';
		cout << nums[N - 1] << ']' << endl;
	}
	void print_arr(int* nums, int left, int right){
		using namespace std;
		cout << "[";
		for (int i = left; i < right; i++)
			cout << nums[i] << ',';
		cout << nums[right] << ']' << endl;
	}
};