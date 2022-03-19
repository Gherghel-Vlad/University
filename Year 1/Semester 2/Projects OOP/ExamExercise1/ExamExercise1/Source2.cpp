#include <iostream>
#include <vector>
#include <crtdbg.h>
using namespace std;


class Action {
public:
	virtual void execute() = 0;
};

class CreateAction : public Action {
public:

	void execute() {
		cout << "Create file\n";
	}

};

class ExitAction : public Action {
public:

	void execute() {
		cout << "Exit application\n";
	}

};

class MenuItem {
private:
	Action* action = nullptr;
	string text;

public:
	MenuItem(string _text, Action* _action = nullptr);

	virtual void print();

	void clicked();

	~MenuItem();

	friend class Menu;
};

MenuItem::~MenuItem() {
	if (this->action != nullptr) {
		delete this->action;
	}
}

MenuItem::MenuItem(string _text, Action* _action) {
	this->text = _text;
	this->action = _action;
}

void MenuItem::print() {
	cout << this->text << endl;
}

void MenuItem::clicked() {
	cout << this->text << endl;
	if (this->action != nullptr) {
		this->action->execute();
	}

}


class Menu: public MenuItem{
private:
	vector<MenuItem*> menuItemVector;
public:
	Menu(string _text, Action* _action = nullptr);

	void add(MenuItem* m);

	void print() override;

	~Menu();

};

Menu::~Menu() {
	if (MenuItem::action != nullptr) {
		delete MenuItem::action;
	}

	for (auto m : this->menuItemVector) {
		delete m;
	}
}

Menu::Menu(string _text, Action* _action): MenuItem(_text, _action) {

}

void Menu::add(MenuItem* m) {
	this->menuItemVector.push_back(m);
}

void Menu::print() {
	cout << MenuItem::text << endl;

	for (auto m : this->menuItemVector) {
		m->print();
	}
}

class MenuBar {
private:
	vector<Menu*> menuVector;

public:
	void add(Menu* m);

	void print();

	~MenuBar();

};

void MenuBar::add(Menu* m) {
	this->menuVector.push_back(m);
}

void MenuBar::print() {
	for (auto a : this->menuVector) {
		a->print();
	}
}

MenuBar::~MenuBar() {
	for (auto a : this->menuVector) {
		delete a;
	}
}

int main() {

	Menu* fileMenu = new Menu("File");
	Menu* aboutMenu = new Menu("About");

	Menu* newMenu = new Menu("New");
	Menu* textMenu = new Menu("Text", new CreateAction());
	Menu* cMenu = new Menu("C++", new CreateAction());
	newMenu->add(textMenu);
	newMenu->add(cMenu);


	Menu* exitMenu = new Menu("Exit", new ExitAction());

	fileMenu->add(newMenu);
	fileMenu->add(exitMenu);


	fileMenu->print();
	cout << endl;
	newMenu->print();
	cout << endl;
	cMenu->clicked();
	cout << endl;
	exitMenu->clicked();
	cout << endl;

	delete fileMenu;
	_CrtDumpMemoryLeaks();
	return 0;
}