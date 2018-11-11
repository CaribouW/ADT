#include"Arr_Martrix.h"

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

template <typename T>
SparseMartrix<T> SparseMartrix<T>::operator*(const SparseMartrix<T> x){
	SparseMartrix<T> result(Row_amount, x.Col_amount);
	if (Col_amount != x.Row_amount){
		cout << "Incompatible Multiple!" << endl;
		return *this;
	}
	if (Terms == MaxTerms || x.Terms == x.MaxTerms){
		cout << "No more space for the Multiple!" << endl;
		return *this;
	}
	T* rowBuffer = new T[x.Col_amount];
	int* rowSize = new int[x.Row_amount];
	int* rowStart = new int[x.Row_amount + 1];
	for (int i = 0; i < x.Row_amount; i++)rowSize = 0;
	for (int i = 0; i < x.Terms; i++)rowSize[x.arr[i].row]++;
	rowBuffer[0] = 0;
	for (int i = 1; i <= x.Row_amount; i++)
		rowBuffer[i] = rowSize[i - 1] + rowBuffer[i - 1];
	int current_order = 0;
	int size_of_result = -1;
	int row_A;
	while (current_order < Terms){
		row_A = arr[current_order].row;                      //indicate the current row of in A.
		for (int i = 0; i < x.Col_amount; i++)rowBuffer[i] = 0; //clear the buffer of each line
		while (current_order < Terms&&row_A == arr[current_order].row){
			int col_A = arr[current_order].col;                 //indicate the current col in A.
																//As well as the current row in B.
			for (int i = rowStart[col_A]; i < rowStart[col_A + 1]; i++){
				int col_B = x.arr[i].col;
				rowBuffer[col_B] += arr[current_order].val*
					x.arr[i].val;
			}
			current_order++;
		}
		/*
		Put the whole row of row_buffer into the result.
		*/
		for (int i = 0; i < x.Col_amount; i++){
			if (rowBuffer[i] != 0){
				size_of_result++;
				result.arr[size_of_result].row = row_A;
				result.arr[size_of_result].col = i;
				result.arr[size_of_result].val = rowBuffer[i];
			}
		}
	}
}

template <typename T>
SparseMartrix<T> SparseMartrix<T>::operator&(const SparseMartrix<T> x){
	SparseMartrix<T> result(Row_amount, x.Col_amount);
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
