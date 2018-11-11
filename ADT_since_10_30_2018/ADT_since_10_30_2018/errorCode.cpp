#include"errorCode.h"
Code::Code(int i){
	this->data_len = i;
	data = k_code = 0;
	k_len = 0;
	while ((1 << k_len) - 1 < k_len + data_len)
		k_len++;
	total_len = k_len + data_len + 1;  //We put table[0] to be 0;
	data_index = new int[data_len];
	k_index = new int[k_len];
	table = new bool[total_len];
	groups = new int*[k_len];
	table[0] = 0;
	for (int i = 1, index_k = 0, index_data = 0; i < total_len; i++){
		table[i] = 0;
		if (counter(i) == 1){
			k_index[index_k++] = i;
		}
		else{
			data_index[index_data++] = i;
		}
	}
	for (int i = 0; i < k_len; i++){
		int val = k_index[i];
		//Let the group's first element denotes the size
		//The following elements contains the index of data_index
		groups[i] = new int[data_len + 1];
		int counter = 0;
		int index = 1;
		for (int j = 0; j < data_len; j++){
			int T = val&data_index[j];
			if (T == val){
				counter++;
				groups[i][index++] = j;
			}
		}
		groups[i][0] = counter;
	}
}
int Code::counter(int i){
	int result = 0;
	while (i > 0){
		if (i & 1)
			result++;
		i = i >> 1;
	}
	return result;
}
std::ostream& operator<<(std::ostream& out, Code& c){
	using namespace std;
	out << "Total" << endl;
	for (int i = c.total_len - 1; i >= 0; i--){
		out << c.table[i] << '\t';
	}
	out << endl;
	out << "data" << endl;
	for (int i = c.data_len - 1; i >= 0; i--){
		out << c.data_index[i] << '\t';
	}
	out << endl;
	out << "Ci code" << endl;
	for (int i = c.k_len - 1; i >= 0; i--){
		out << c.k_index[i] << '\t';
	}
	out << endl;
	out << "groups" << endl;
	for (int i = 0; i < c.k_len; i++){
		//out << c.data_index[i] << '\t';
		out << "group : " << c.k_index[i] << "¡ª¡ª";
		for (int j = 0; j < c.groups[i][0]; j++){
			out << '\t' << c.groups[i][j + 1] + 1 << '\t';
		}
		out << endl;
	}
	return out;
}

void Code::analysis(char* str){
	for (int i = 0; i < data_len; i++){
		int val = str[data_len - 1 - i] - '0';
		table[data_index[i]] = val;
	}
	for (int i = 0; i < k_len; i++){
		int * grp = groups[i];
		bool result = 0;
		for (int j = 0; j < grp[0]; j++){
			int index = data_index[grp[j + 1]];
			result = result^table[index];
		}
		table[k_index[i]] = result;
	}
}

void Code::check(char* str){
	Code tmpC(data_len);
	tmpC.analysis(str);
	
}