#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Discount {

	virtual double calc(Sale s) = 0;


};

class ItemDiscount: public Discount {
private:
	int code;
	int percentage;

public:
	ItemDiscount(int code, int percentage);

	double calc(Sale s) override;


};

ItemDiscount::ItemDiscount(int code, int percentage): code(code), percentage(percentage) {

}

double ItemDiscount::calc(Sale s) {

	for (SaleItem a : s.v) {
		if (a.getCode() == this->code) {
			a.setPrice((double)a.getPrice() * this->percentage / 100);
		}
	}
}

class SaleItem {
private:
	int code;
	double price;
public:
	SaleItem(int code, double price);

	int getCode() {
		return this->code;
	}

	void setCode(int value) {
		this->code = value;
	}

	double getPrice() {
		return this->price;
	}

	void setPrice(double value) {
		this->price = value;
	}
};
SaleItem::SaleItem(int _code, double _price) : code(_code), price(_price) {

}

class Sale {
private:
	vector<SaleItem> v;
public:

	friend class ItemDiscount;
};


int main() {


	return 0;
}