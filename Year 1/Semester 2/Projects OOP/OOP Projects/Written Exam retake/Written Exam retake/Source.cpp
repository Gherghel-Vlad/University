#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
class Object {
public:
	virtual void print() = 0;
};

class Integer: public Object {

private:
	int number;
public:
	Integer(int _number) {
		this->number = _number;
	}

	void print() {
		cout << this->number << " ";
	}
};

class String : public Object {
private:
	string str;
public:
	String(string _str) : str(_str) {

	}

	void print() {
		cout << this->str << " ";
	}

	String operator*() {
		return this->str;
	}

	bool operator==(const string rhs) {
		if (this->str == rhs)
			return true;
		return false;
	}
};

class MyObjectList {
private:
	vector<Object*> objVector;

public:
	MyObjectList() {}

	vector<Object*> getObjectVector() {
		return this->objVector;
	}

	MyObjectList& add(Object* _obj) {
		this->objVector.push_back(_obj);
		return *this;
	}

	int length() {
		return this->objVector.size();
	}
};


class ListIterator {
private:
	int pos;
	vector<Object*> objVector;
public:
	ListIterator(MyObjectList mol) {
		this->pos = 0;
		this->objVector = mol.getObjectVector();
	}

	bool isValid() {
		if (this->pos < this->objVector.size())
			return true;
		return false;
	}

	Object* element() {
		return (Object*)this->objVector[pos];
	}

	void next() {
		this->pos++;
	}
};


void function()
{
	MyObjectList list{};
	list.add(new Integer{ 2 }).add(new String{ "Hi" });
	String* s = new String{ "Bye" };
	assert(*s == "Bye");
	list.add(s).add(new Integer{ 5 });
	assert(list.length() == 4);

	ListIterator i{ list };
	while (i.isValid()) {
		Object* o = i.element();
		o->print();
		i.next();
	} // prints: 2 Hi Bye 5
}


//int main() {
//
//	function();
//
//	return 0;
//
//
//}