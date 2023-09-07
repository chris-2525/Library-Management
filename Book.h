
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include <iostream>
#include "Publication.h"
namespace sdds {
	class Book : public  Publication {

		char* author;

	public:

		Book();
		Book(const Book&);
		Book& operator=(const Book&);
		~Book();
		char type()const;
		ostream& write(ostream& os) const;
		istream& read(istream& is);
		void set(int member_id);
		operator bool() const;

	};
}
#endif
