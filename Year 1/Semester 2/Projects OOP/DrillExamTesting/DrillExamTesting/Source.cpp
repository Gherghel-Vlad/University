#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Activity {
private:
	string name;
	string date;

public:
	Activity(string name, string date);

	friend ostream& operator<<(ostream& os, const Activity& a);

};

Activity::Activity(string name, string date) : name(name), date(date) {

}

ostream& operator<<(ostream& os, const Activity& a) {
	os << "Activity " + a.name + " will take place at " + a.date;
	return os;
}

template <typename T>
class ToDo {
private:
	std::vector<Activity> v;

public:

	ToDo& operator+=(const T& rhs) {
		reverse(this->v.begin(), this->v.end());
		this->v.push_back(rhs);
		reverse(this->v.begin(), this->v.end());
		return *this;
	}

	std::vector<Activity>::iterator begin() {
		return this->v.begin();
	}


	std::vector<Activity>::iterator end() {
		return this->v.end();
	}

	void reversePrint(ostream& os);
};

//template <typename T>
//ToDo<T>& operator+=(ToDo<T>& lhs, const T& rhs) {
//	lhs.v.push_back(rhs);
//	return &lhs;
//}

template <typename T>
void ToDo<T>::reversePrint(ostream& os){
	vector<Activity> v1 = v;

	reverse(v1.begin(), v1.end());

	for (auto a : v1) {
		os << a << endl;
	}
	
}


void ToDoList()
{
	ToDo<Activity> todo{};
	Activity tiff{ "go to TIFF movie", "20:00" };
	todo += tiff;
	Activity project{ "present project assignment", "09.20" };
	todo += project;

	// iterates through the activities and prints them as follows:
	// Activity present project assignment will take place at 09.20.
	// Activity go to TIFF movie will take place at 20.00.
	for (auto a : todo)
		std::cout << a << '\n';

	// Prints the activities as follows:
	// Activity go to TIFF movie will take place at 20.00.
	// Activity present project assignment will take place at 09.20.
	todo.reversePrint(std::cout);
}




//int main() {
//
//	ToDoList();
//
//	return 0;
//}