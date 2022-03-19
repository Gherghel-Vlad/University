#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
class Rational {
private:
	int num;
	int den;

public:

	Rational(int _num=0, int _den=1);

	Rational(const Rational& rat);

	int getNumerator() {
		return this->num;
	}

	int getDenominator() {
		return this->den;
	}

	bool operator==(const Rational& rhs);

	friend Rational operator/(Rational lhs, Rational rhs);

	friend std::ostream& operator<<(std::ostream& os, const Rational& rat);

};


Rational::Rational(const Rational& rat) {
	this->num = rat.num;
	this->den = rat.den;
}

Rational::Rational(int _num, int _den) {
	this->num = _num;
	this->den = _den;
}

bool Rational::operator==(const Rational& rhs) {
	if (this->num == rhs.num && this->den == rhs.den) {
		return true;
	}
	return false;
}


std::ostream& operator<<(std::ostream& os, const Rational& rat) {
	os << rat.num << "/" << rat.den;
	return os;
}


Rational operator/(Rational lhs, Rational rhs) {
	if (rhs.num == 0 || lhs.den == 0)
		throw runtime_error("Division by zero!");

	Rational res{};

	res.num = lhs.num * rhs.den;
	res.den = lhs.den * rhs.num;

	return res;
}

template <typename T>
class Vector {
private:
	vector<T> vector;

public:

	Vector(std::vector<T> v) {
		this->vector = v;
	}

	/// <summary>
	/// Prints all the elements from the vector with ", " after each element and a new line at the end
	/// </summary>
	/// <param name="os">The output stream</param>
	void printAll(ostream& os);

};


template <typename T>
void Vector<T>::printAll(ostream& os) {
	for (auto a : this->vector) {
		os << a;
		os << ", ";
	}
	os << "\n";
}



void rational()
{
	Rational a{}, b{ 6, 15 }, c{ 3, 5 }, d{ b };
	assert(a.getNumerator() == 0);
	assert(c.getDenominator() == 5);
	assert(b == d);
	Rational res1 = b / c;
	cout << res1 << "\n"; // prints: 30/45
	try {
		Rational res2 = b / a;
	}
	catch (runtime_error& e) {
		assert(strcmp(e.what(), "Division by zero!") == 0);
	}

	Vector<int> v1{ std::vector<int>{1, 2, 3 } };
	v1.printAll(std::cout); // prints: 1, 2, 3

	Vector<Rational> v2{ std::vector<Rational>{a, b, c, d} };
	v2.printAll(std::cout); // prints: 0/1, 6/15, 3/5, 6/15,
}

//int main() {
//
//	rational();
//
//	return 0;
//}