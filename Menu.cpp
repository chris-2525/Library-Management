
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include "Menu.h"
using namespace std;
namespace sdds {

	//MENU ITEM 

	MenuItem::MenuItem(const char* item) {

		content = nullptr;

		if (item != nullptr) {

			content = new char[strlen(item) + 1];
			strcpy(content, item);
		}
	}
	MenuItem::~MenuItem() {

		delete[] content;
	}
	MenuItem::operator bool() const {

		bool result = false;

		if (content != nullptr) {
			result = true;
		}

		return result;
	}
	MenuItem::operator const char* ()const {
		return (const char*)content;
	}
	void MenuItem::displayMenuItem() const {

		if (content != nullptr) {
			cout << content;
		}

	}

	//MENU 

	Menu::Menu(const char* filename, int ptr) {

		int maxItems = MAX_MENU_ITEMS;

		for (int i = 0; i < maxItems; i++) {

			itemArr[i] = nullptr;
		}

		totalPtr = 0;

		if (filename != nullptr && ptr >= 0 && ptr <= maxItems) {

			title.content = new char[strlen(filename) + 1];
			strcpy(title.content, filename);
			totalPtr = ptr;

		}
	}
	Menu::~Menu() {

		for (int i = 0; i < totalPtr; i++) {

			delete itemArr[i];

			itemArr[i] = nullptr;
		}

	}
	ostream& Menu::displayMenu()const {

		if (title != nullptr) {
			displayTitle() << endl;
		}

		if (this) {

			for (int i = 0; i < totalPtr; i++) {

				cout << " " << i + 1 << "- ";
				cout << itemArr[i]->content << endl;
			}

			cout << " 0- Exit" << endl;
		}

		return cout;
	}

	ostream& Menu::displayTitle()const {

		if (title.content != nullptr) {

			cout << title.content;
		}

		return cout;
	}

	unsigned int Menu::run() {

		unsigned int selection = 0;
		int tempSelect = -1;

		displayMenu();

		cout << "> ";

		do {

			cin >> tempSelect;

			if (!cin)
			{
				tempSelect = -1;

				cin.clear();

				//clears input buffer
				while (cin.get() != '\n') {

				}

				cout << "Invalid Selection, try again: ";

			}
			else {

				if (tempSelect < 0 || tempSelect > totalPtr) {

					cout << "Invalid Selection, try again: ";
					tempSelect = -1;
				}
				else {

					selection = tempSelect;

				}
			}


		} while (tempSelect < 0);

		return selection;
	}

	int Menu::operator~() {

		int selection = run();

		return selection;

	}

	Menu& Menu::operator<<(const char* menuitemContent) {

		int idx = 0;
		bool match = false;
		int maxItems = MAX_MENU_ITEMS;

		if (totalPtr < maxItems) {

			for (int i = 0; i < maxItems && !match; i++) {

				if (itemArr[i] == nullptr) {
					idx = i;
					match = true;
				}
			}

			itemArr[idx] = new MenuItem(menuitemContent);
			totalPtr++;
		}

		return *this;
	}
	
	Menu::operator int() const {
		return totalPtr;
	}
	
	Menu::operator unsigned int()  const {
		return totalPtr;
	}
	
	Menu::operator bool() const {

		bool menuItems = false;

		if (totalPtr > 0) {
			menuItems = true;
		}

		return menuItems;
	}
	
	ostream& operator<<(ostream& ostr, const Menu& M) {
		M.displayTitle();
		return ostr;
	}
	
	const char* Menu::operator[](int index) const {

		char* temp = nullptr;
		int idx = index;
		bool match = false;

		if (totalPtr > 0)
		{

			if (idx > totalPtr - 1)
			{
				idx = idx - totalPtr;
			}

			match = false;
			for (int i = 0; i < totalPtr && !match; i++)
			{
				if (i == idx)
				{
					temp = itemArr[i]->content;
					match = true;
				}

			}
		}
		else
		{
			temp = nullptr;
		}

		return temp;

	}



}
