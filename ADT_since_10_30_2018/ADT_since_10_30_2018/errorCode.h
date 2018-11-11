#include<iostream>
#include<cstdint>

//Hamming code.
struct Code{
private:
	uint8_t data_len;
	uint8_t k_len;
	uint32_t data;
	uint32_t k_code;
	bool* table;    //The data plus the error code. and table[0]=0;
	int* data_index;//pointed to the table  
	int* k_index;	//pointed to the table

	int** groups;   //We have several groups , group[i][j] means the 
	//Ci error code's group,and the length of the group[i] equals the 1 + elements.
	//group[i][j]= index of data.
public:
	uint8_t total_len;
	friend std::ostream& operator<<(std::ostream& out, Code& c);
	int counter(int i);
	Code(int data_len);
	bool* getTotalData(){
		return table;
	}
	void analysis(char* str);
	void check(char* str);
	int getCode(){
		int result = 0;
		for (int i = k_len - 1; i >= 0; i--){
			result <<= 1;
			int index = k_index[i];
			bool val = table[index];
			result += val;
		}
		return result;
	}
};

struct Data{
	int data_size;
	int short_size;
	int code;
	Code* c;
	Data(int i){
		c = new Code(i);
		short_size = i;
		data_size = c->total_len;
	}
	void putData(char* str){
		using namespace std;
		c->analysis(str);
		code = c->getCode();
		cout << "put str = " << str << endl;
		cout << "generating code: " << code << endl;
		cout << *c;
	}
	void checkData(char* str){
		using namespace std;
		Code* tmp = new Code(short_size);
		tmp->analysis(str);
		int tmpVal = tmp->getCode();
		int index = tmpVal^code;
		switch (index)
		{
		case 0 :
			cout << "No error" << endl;
			break;
		default:
			if (tmp->counter(index) == 1){
				int i;
				cout << "error occurs in code bit " << endl;
			}
			else{
				cout << "error occurs in origin bit" << endl;
				cout << "index is "<< index << endl;
			}
			break;
		}
	}
	
};