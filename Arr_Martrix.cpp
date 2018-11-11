#include<iostream>
#include<stdlib.h>
#define My_arr_9_30
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
	~SparseMartrix(){ delete[] smArr;}
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
	SparseMartrix(const int rows, const int cols) :Terms(0),Row_amount(rows), Col_amount(cols){
		MaxTerms = rows*cols;
		arr = new Triple<T>[MaxTerms];
	}
	SparseMartrix(const SparseMartrix<T>& x){
		Terms = x.Terms; MaxTerms = x.MaxTerms; Col_amount = x.Col_amount; Row_amount = x.Row_amount;
		arr = new Triple<T>[MaxTerms];
		for (int i = 0; i < MaxTerms; i++)
			arr[i] = x.arr[i];
	}
	SparseMartrix(const int size):MaxTerms(size){
		Row_amount = Col_amount = Terms = 0;
		arr = new Triple<T>[size];
	}
	~SparseMartrix(){ delete[] arr; }
	SparseMartrix& operator=(const SparseMartrix<T> x);
	SparseMartrix<T> transpose();
	SparseMartrix<T> operator+(const SparseMartrix<T> x);
	SparseMartrix<T> operator*(const SparseMartrix<T> x);
};
template <typename T>
ostream& operator<<(ostream& out, SparseMartrix<T>& x){
	out << "Nonzero Terms: " << x.Terms<<endl;
	out << "Rows: " << x.Row_amount << endl;
	out << "Cols: " << x.Col_amount << endl;
	for (int i = 0; i < x.Terms; i++){
		cout << "M[" << x.arr[i].row<<"]["<<x.arr[i].col<<"]";
		cout << "= " << x.arr[i].val << endl;
	}
	return out;
}

template <typename T>
istream& operator>>(istream& in, SparseMartrix<T>& x){
	cout << "input row,col and nonzero terms:" << endl;
	in >> x.Row_amount >> x.Col_amount >> x.Terms;
	if (x.Terms > x.MaxTerms){
		cout << "Numbers of terms overflow" << endl;
		exit(1);
	}
	for (int i = 0; i < x.Terms; i++){
		cout << "enter row ,col, valu of the term" << endl;
		in >> x.arr[i].row >> x.arr[i].col >> x.arr[i].val;
	}
	return in;
}

template <typename T>
SparseMartrix<T> SparseMartrix<T>::transpose(){
	SparseMartrix<T> result(this->MaxTerms);
	result.Terms = Terms;
	result.Col_amount = Row_amount;
	result.Row_amount = Col_amount;
	int* rowSize = new int[Col_amount];
	int* rowStart = new int[Col_amount];
	if (Terms > 0){
		rowStart[0] = 0;
		for (int i = 0; i < Col_amount; i++)rowSize[i] = 0;
		for (int i = 0; i < Terms; i++)rowSize[arr[i].col]++;
		for (int i = 1; i < Col_amount; i++){
			rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
		}
		for (int i = 0; i < Terms; i++){
			int pos = rowStart[arr[i].col];
			result.arr[pos].row = arr[i].col;
			result.arr[pos].col = arr[i].row;
			result.arr[pos].val = arr[i].val;
			rowStart[arr[i].col]++;          //move the start of the target backet.
		}
	}
	delete[] rowSize; delete[] rowStart;
	return result;

}

template <typename T>
SparseMartrix<T> SparseMartrix<T>::operator+(const SparseMartrix<T> x){
	if (Row_amount != x.Row_amount || Col_amount != x.Col_amount){
		cout << "incompatible matrix while adding!" << endl;
		return *this;
	}
	SparseMartrix<T> result(Row_amount, Col_amount);
	int index_a, index_b;
	int i = 0, j = 0;
	while (i < Terms&&j < Terms){
		index_a =arr[i].row*Col_amount + arr[i].col;
		index_b = x.arr[j].row*x.Col_amount + x.arr[j].col;
		if (index_a < index_b){
			result.arr[result.Terms++] = arr[i++];
		}
		else if (index_a>index_b){
			result.arr[result.Terms++] = x.arr[j++];
		}
		else{
			result.arr[result.Terms] = x.arr[i];
			result.arr[result.Terms++].val = x.arr[j].val + arr[i].val;
			++i; ++j;
		}
	}
	for (; i < Terms; i++){
		result.arr[result.Terms++] = arr[i];
	}
	for (; j < x.Terms; j++){
		result.arr[result.Terms++] = x.arr[j];
	}
	return result;
}

#endif // My_arr_9_30
/*
5 5 9
0 0 12
0 1 34 
0 3 16
0 4 17
1 0 246
1 3 1613
2 3 65
2 1 4613
4 0 163


*/
int main(){
	int t = 30;
	SparseMartrix<int>* p = new SparseMartrix<int>(t);
	cin >> *p;
	cout << *p;
	SparseMartrix<int> k = (*p) + *(new SparseMartrix<int>(*p));
	cout << k;
	cin.get();
	cin.get();
}