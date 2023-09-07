
#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
using namespace std;
namespace sdds {
	const unsigned int MAX_MENU_ITEMS = 20;
	class MenuItem {

		char* content;
		friend class Menu;
		MenuItem(const char* item = nullptr);
		~MenuItem();
		operator bool() const;
		operator const char* ()const;
		void displayMenuItem() const;

		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;

	};

	class Menu {

		MenuItem title;
		MenuItem* itemArr[MAX_MENU_ITEMS];
		int totalPtr;

	public:
		
		Menu(const char* filename = nullptr, int ptr = 0);
		~Menu();
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
		ostream& displayMenu()const;
		ostream& displayTitle()const;
		unsigned int run();
		int operator~();
		Menu& operator<<(const char* menuitemContent);
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		const char* operator[](int idx) const;
	};
	ostream& operator<<(ostream& ostr, const Menu& M);
}
#endif
