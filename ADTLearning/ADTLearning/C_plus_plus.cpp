#include<iostream>
#include<string>
#ifdef inlineOne
inline void run(int& x);

inline void run(int& x){
	cout << x << 2 << endl;
	return;
}

#endif
#ifdef free_throws_
using namespace std;
struct free_throws{
	string name;
	int made;
	int attempts;
	float percent;
};
void display(const free_throws& ft);
void set_pc(free_throws & ft);
free_throws & accumulate(free_throws& target, const free_throws& source);


void display(const free_throws& ft){
	cout << "Name: " << ft.name << endl;
	cout << "Made: " << ft.made << endl;
	cout << "Attempts: " << ft.attempts << endl;
	cout << "Percent: " << ft.percent << endl;
}
void set_pc(free_throws& ft){
	if (ft.attempts != 0)
		ft.percent = 100.0f*float(ft.made) / float(ft.attempts);
	else
		ft.percent = 0;
}
free_throws & accumulate(free_throws& target, const free_throws& source){
	target.attempts += source.attempts;
	target.made += source.made;
	set_pc(target);
	return target;
}

#endif
#ifdef Default_Parameter
using namespace std;
void run(const char* p);
void run(char* p);
void run(int p){
	cout << p << "run int p" << endl;
}
void run(int& p){
	cout << p << 2 << "run int& p" << endl;
}




#endif
#ifdef tmplate
using namespace std;
template <typename T> 
void swap(T& a, T& b){
	T tmp = a;
	a = b;
	b = tmp;
}  //model
template<>
void swap<int>(int& a, int& b);  //explict specialization
template void swap<char>(char& a, char& b);//explict instanilization.

template<typename T1,typename T2>
void ft(T1 a, T2 b){
	decltype(a + b) result = a + b;
}
template<typename T1,typename T2>
auto f(T1 a, T2 b)->decltype(a + b){
	return a + b;
}

#endif
#ifdef New
#include<new>
#define N 1024
using std::cout;
using std::endl;
using std::cin;
char buffer[N];


#endif
#ifdef Class
#include<string>
#include<cstring>
using namespace std;
class stock{
private:
	long shares=412;
	double share_val;
	double total_val;
	double a;
	double c;
	int cas;
	char ch;
	long as;
	char* cs;
	__int32 th;

public:
	void acquire(const std::string& co, long n, double pr)const;
	void run(){
		cout << shares<<endl;
	}
	void run(int x);
	stock(long shares=532){
		this->shares = shares;
		this->share_val = 3.1;
	}
	~stock(){
		cout << "Delete" << endl;
	}
};

void stock::run(int x){
	cout << x + this->th << endl;
}

class person{
public:
	enum {Month = 12};
	void run(){
		cout << Month << endl;
	}
};
#endif
#ifdef Operation
class Time{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int h, int m = 0);
	void AddMin(int m);
	void AddHr(int h);
	void Reset(int h = 0, int m = 0);
	Time Sum(const Time& t)const;
	void Show()const;
	Time Time::operator+(const Time& t)const;
};


Time::Time(){
	hours = minutes = 0;
}
Time::Time(int h, int m = 0){
	hours = h;
	minutes = m;
}
void Time::AddHr(int h){
	hours += h;
}
void Time::AddMin(int min){
	minutes += min;
}
Time Time::operator+(const Time& t)const{

}


#endif
#ifdef friends
using namespace std;
class F{
public:
	int val;
	friend F operator*(double m, const F & t);
	friend void operator<<(ostream& os, const F& f);
	F operator*(double m){ return m*(*this); };
	F(){ val = 3; };
	F(int val){ this->val = val; };
	void setVal(int val){ this->val = val; };
};
F operator*(double m, const F & t){
	F result;
	result.setVal(m*t.val);
	return result;
 }
void operator<<(ostream& os, const F& f){
	os << f.val << "as"<<endl;
}

#endif
#ifdef VECTORCLASS
namespace VECTOR{
	class Vector{
	public:
		enum Mode{RECT,POL};
	private:
		double x;
		double y;
		double mag;
		double ang;
		Mode mode;

		void set_mag();
		void set_ang();
		void set_x();
		void set_y();

	public:
		Vector();
		Vector(double n1, double n2, Mode form = RECT);
		void reset(double n1, double n2, Mode form = RECT);
		double x_val()const{ return x; }
		double y_val()const{ return y; }
		double angval()const{ return ang; }
		void polar_mode();
		void rect_mode();

		Vector operator+(const Vector& b)const;
		Vector operator-(const Vector& b)const;

	};
}
#endif
