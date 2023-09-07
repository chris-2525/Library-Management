// Final Project Milestone 5
// Date Module
// File	Book.h
// Version 1.0
// Author	Christine Ang; Student ID#: 121559223
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments
// 
/////////////////////////////////////////////////////////////////
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