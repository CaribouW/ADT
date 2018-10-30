#include<iostream>
#include<stack>
#include<deque>
#include<vector>
#include<memory>
#include<queue>
#include<map>
#include<algorithm>
#define alg
using namespace std;
#ifdef VEC
long f(int x){
	stack<int> s;
	s.push(x);
	long result = 0;
	while (!s.empty()){
		int num = s.top();
		s.pop();
		if (num <= 1){
			result++;
		}
		else{
			s.push(num - 1);
			s.push(num - 2);
		}
	}
	return result;
}
void vec(){
	vector<int> v;
}

ostream& operator<<(ostream& out, queue<int> q);
int main(){
	vector<int> v;
	v.push_back(3);
	v.push_back(-12);
	v.push_back(1);
	v.assign(4, 51);
	vector<int>::iterator it = v.begin();
	it=v.insert(it, 1, 3);
	it=v.insert(it, 4);
	for (int i : v)
		cout << i << endl;
	cin.get();

}

ostream& operator<<(ostream& out, queue<int> q){
	out << "front: " << q.front() << endl;
	out << "end: " << q.back() << endl;
	return out;
}
#endif
#ifdef smartPtr
void p(){
	int k = 3;
	unique_ptr<int> p_int(new int(k));
	k = 341;
	int s = 341;
	cout << *p_int << endl;

	unique_ptr<int> p = (unique_ptr<int>)&s;
	cout << *p << endl;
	cin.get();
}

#endif
#ifdef MAP
typedef map<int, string> map_int2string_;
typedef pair<int, string> map_pair;
typedef map<int, string>::value_type Pair;

int main(){
	
	map_int2string_ x;
	x.insert(map_pair(3, "first"));
	x.insert(map_pair(412, "c++"));
	x.insert(map_pair(1, "java"));
	x.insert(Pair(3, "a"));
	x[3] = "a";
	for (map_pair pair: x){
		cout << "key: " << pair.first << "\t"
			<< "val: " << endl;
	}
	cout << x.at(3).size() << endl;
	cout << "size: " << x.size() << endl;
	cout << "maxSize " << x.max_size() << endl;
	auto it = x.begin();
	for (; it != x.end(); it++){
		cout << (*it).first << endl;
	}
	cin.get();
}
#endif

#ifdef alg
void run(){
}

#endif