#include<iostream>
#include<stdlib.h>
#ifdef ARR
#define Max_Size 1024
using namespace std;
template <typename T>
struct Tripule{
	int row, col;
	T val;
	Tripule<T>& operator=(const Tripule<T>& x){
		row = x.row; col = x.col; val = x.val;
		return *this;
	};
};

template <typename T>
class SparseMartrix{
	friend ostream& operator<<(ostream& out, SparseMartrix& x);
	friend istream& operator>>(istream& in, SparseMartrix& x);
private:
	int Rows, Cols, Terms;  //Terms means the current numbers of the nonZero in the arr.
	//Which is also the numbers of the nonzero value.
	Tripule<T>* smArr;
	int maxTerms;           //capacity of the Arr.
public:
	SparseMartrix(int maxSz = Max_Size);
	SparseMartrix(const SparseMartrix<T>& x);
	SparseMartrix(int cols, int rows);
	~SparseMartrix(){ delete[] smArr; }
	SparseMartrix<T> & operator=(const SparseMartrix<T>& x);
	SparseMartrix<T> transpose();        //transpose the martrix.
	SparseMartrix<T> operator+(const SparseMartrix<T>& x);
	SparseMartrix<T> operator*(const SparseMartrix<T>& x);
};
template <typename T>
SparseMartrix<T>& SparseMartrix<T>::operator=(const SparseMartrix<T>& x){
	SparseMartrix<T> result(x.maxTerms);
	if (Rows != x.Rows || Cols != x.Cols){
		cout << "incompatible matric" << endl;
		return result;
	}
	return SparseMartrix(x);
}

template <typename T>
SparseMartrix<T>::SparseMartrix(int maxSz) :maxTerms(maxSz){
	if (maxSz < 1){ cerr << "Initial error!" << endl; exit(1); }
	smArr = new Tripule<T>[maxSz];
	Rows = Cols = Terms = 0;
}
template <typename T>
SparseMartrix<T>::SparseMartrix(int col, int row) :Cols(col), Rows(row), Terms(col*row){
	maxTerms = Terms;
	smArr = new Tripule<T>[maxTerms];
}

template <typename T>
SparseMartrix<T>::SparseMartrix(const SparseMartrix<T>& x){
	Rows = x.Rows; Cols = x.Cols; Terms = x.Terms;
	maxTerms = x.maxTerms;
	smArr = new Tripule<T>[maxTerms];
	for (int i = 0; i < maxTerms; i++)smArr[i] = x.smArr[i];
}
template <typename T>
SparseMartrix<T> SparseMartrix<T>::transpose(){
	int *rowSize = new int[Cols];
	int *rowStart = new int[Cols];
	SparseMartrix<T> b(maxTerms);
	b.Rows = Cols;
	b.Cols = Rows;
	b.Terms = Terms;
	if (Terms > 0){
		int i, j;
		for (i = 0; i < Cols; i++)rowSize[i] = 0;
		for (i = 0; i < Terms; i++)rowSize[smArr[i].col]++;
		rowStart[0] = 0;
		for (i = 1; i < Terms; i++)rowStart[i] = rowSize[i - 1] + rowStart[i - 1];
		for (i = 0; i < Terms; i++){
			j = rowStart[smArr[i].col];
			b.smArr[j].row = smArr[i].col;
			b.smArr[j].col = smArr[i].col;
			b.smArr[j].val = smArr[i].val;
		}
	}
	delete[] rowSize;
	delete[] rowStart;
	return b;
}

template <class T>
SparseMartrix<T> SparseMartrix<T>::operator+(const SparseMartrix<T>& x){
	SparseMartrix<T> result(Rows, Cols);
	if (Rows != x.Rows || Cols != x.Cols){
		cout << "incompatible martrics" << endl;
		return result;
	}
	int i = 0, j = 0;
	int index_a, index_b;
	result.Terms = 0;
	while (i < Terms&&j < Terms){
		index_a = Cols*smArr[i].row + smArr[i].col;
		index_b = Cols*x.smArr[j].row + smArr[j].col;
		if (index_a < index_b){
			result.smArr[result.Terms] = smArr[i];
			i++;
		}
		else if (index_a>index_b){
			result.smArr[result.Terms] = x.smArr[j];
			j++;
		}
		else{
			result.smArr[result.Terms] = smArr[i];
			result.smArr[result.Terms].value =
				smArr[i].value + x.smArr[j].value;
			i++;
			j++;
		}
		result.Terms++;
	}
	for (; i < Terms; i++){
		result.smArr[result.Terms++] = smArr[i];
	}
	for (; j < Terms; j++){
		result.smArr[result.Terms++] = x.smArr[j];
	}
	return result;
}

template <class T>
SparseMartrix<T> SparseMartrix<T>::operator*(const SparseMartrix<T>& x){

}
#endif
#ifdef My_arr_9_30
using namespace std;
template <typename T>
class SparseMartrix{
	template <typename T>
	struct Triple{
	public:
		T val;
		int row, col;
		Triple<T>(){}
		Triple<T>(const int row, const int col, const T val){
			this->row = row;
			this->col = col;
			this->val = val;
		}
		Triple<T>& operator=(const Triple<T>& x){
			val = x.val;
			row = x.row;
			col = x.col;
			return Triple<T>(val, row, col);
		}
	};
	friend ostream& operator<<(ostream& out, const SparseMartrix<T>& x);
	friend istream& operator>>(istream& in, const SparseMartrix<T>& x);
public:
	Triple<T>* arr;
	int Row_amount, Col_amount;  //Total amount of the rows and the cols
	int MaxTerms, Terms;			//Terms means the nonzero value in the matricx.
	void printMar()const;
	SparseMartrix(const int rows, const int cols) :Terms(0), Row_amount(rows), Col_amount(cols){
		MaxTerms = rows*cols;
		arr = new Triple<T>[MaxTerms];
	}
	SparseMartrix(const SparseMartrix<T>& x){
		Terms = x.Terms; MaxTerms = x.MaxTerms; Col_amount = x.Col_amount; Row_amount = x.Row_amount;
		arr = new Triple<T>[MaxTerms];
		for (int i = 0; i < MaxTerms; i++)
			arr[i] = x.arr[i];
	}
	SparseMartrix(const int size) :MaxTerms(size){
		Row_amount = Col_amount = Terms = 0;
		arr = new Triple<T>[size];
	}
	~SparseMartrix(){ delete[] arr; }
	SparseMartrix& operator=(const SparseMartrix<T> x);
	SparseMartrix<T> transpose();
	SparseMartrix<T> operator+(const SparseMartrix<T> x);
	SparseMartrix<T> operator*(const SparseMartrix<T> x);
	SparseMartrix<T> operator&(const SparseMartrix<T> x);
};
#endif