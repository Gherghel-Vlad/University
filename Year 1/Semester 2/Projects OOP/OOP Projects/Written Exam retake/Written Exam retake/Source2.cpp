#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>
#include <ctype.h>
using namespace std;



class Section {
protected:
	string title;
	string content;

public:

	Section(string t, string c) : title(t), content(c) {

	}
	
	string getTitle() {
		return this->title;
	}

	string getContent() {
		return this->content;
	}


	virtual void addSection(Section s) {};

	void generate() {

		DoubleChecker dc{};
		if (dc.check(*this) == true) {
			cout << this->title << " " << this->content;
		}

	}

};


class Preface : public Section {
public:

	Preface(string t, string c) : Section(t, c) {

	}

	void addSection(Section s) {
		cout << "It cannot have any aggragated sections\n";
	}
};

class Chapter : public Section {
private:
	vector<Section> sections;
public:
	Chapter(string t, string c) : Section(t, c) {

	}

	void addSection(Section s) {
		DoubleChecker dc{};
		if (dc.check(s) == true)
			this->sections.push_back(s);

	}

	
};

class Checker {
public:
	virtual bool check(Section s) = 0;
};

class TitleChecker : public Checker {
public:
	bool check(Section s) override {
		if (s.getTitle().size() > 2)
			return true;
		return false;
	}
};

class ContentChecker : public Checker {
public:
	bool check(Section s) override {
		
		int ok = 0;

		string contentStr = s.getContent();
		int i = 0;
		// checking if the first letter of the content is an uppercase
		while (i < contentStr.size() && !isalpha(contentStr[i])) {
			i++;
		}

		if (i == contentStr.size())
			return false; 

		if (!isupper(contentStr[i])) {
			return false; // first letter of first sentence is not uppercase
		}

		string sentenceStopCharacter = ".?!";

		while (i < contentStr.size()) {
			while (i < contentStr.size() && sentenceStopCharacter.find(contentStr[i]) == string::npos) {
				i++;
			}
			i++;

			if (i == contentStr.size())
				return false;

			while (i < contentStr.size() && !isalpha(contentStr[i])) {
				i++;
			}

			if (i == contentStr.size())
				return false; 

			if (!isupper(contentStr[i])) {
				return false; // first letter of sentence is not uppercase
			}
		}

		return true;


	}

};

class DoubleChecker: public Checker {
public:

	bool check(Section s) {
		TitleChecker tc{};
		ContentChecker cc{};

		if (tc.check(s) == true && cc.check(s) == true) {
			return true;
		}

		return false;

	}
};




int main() {

	return 0;
}