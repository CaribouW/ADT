#include"laucher.h"
#ifdef DICTIONARY
const int DefaultSize = 20;
template <class key,class value>
class dictionary{
public:
	dictionary(int sz = DefaultSize);
	bool IsMember(key k);
	value* Search(Key k);
	void Insert(key k, value val);
	void Remove(key k);
};


#endif