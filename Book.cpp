// Final Project Milestone 5
// Date Module
// File	Book.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Book.h"
#include "Lib.h"

using namespace std;
namespace sdds {
	
	Book::Book() : Publication() {
		author = nullptr;
	}

	Book::Book(const Book& book) : Publication(book) {
		*this = book;
	}
	
	Book& Book::operator=(const Book& book) {

		(Publication&)*this = book;
		delete[] author;
		if (book.author != nullptr) {
			author = new char[strlen(book.author) + 1];
			strncpy(author, book.author, (strlen(book.author) + 1));
		}
		else {
			author = nullptr;
		}

		return *this;
	}
	
	Book::~Book() {
		delete[] author;
	}

	char Book::type()const {
		return 'B';
	}
	
	ostream& Book::write(ostream& os) const {

		Publication::write(os);

		if (Publication::conIO(os)) {

			os << " ";

			if ((strlen(author)) > SDDS_AUTHOR_WIDTH) {
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
					os << author[i];
				}
			}
			else {
				os << setfill(' ') << setw(SDDS_AUTHOR_WIDTH);
				os.setf(ios::left);
				os << author;
			}

			os << " |";

		}
		else {
			os << '\t' << author << endl;
		}

		return os;
	}
	
	istream& Book::read(istream& is) {

		char authorTemp[256] = "\0";

		Publication::read(is);

		if (Publication::conIO(is)) {
			is.ignore();
			cout << "Author: ";
			is.getline(authorTemp, 256, '\n');
		}
		else {
			is.ignore();
			is.getline(authorTemp, 256, '\n');
		}

		if (is) {
			delete[] author;
			author = new char[strlen(authorTemp) + 1];
			strcpy(author, authorTemp);
		}
		return is;
	}
	
	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}
	
	Book::operator bool() const {

		bool validAuthor = false;

		if (author != nullptr) {
			validAuthor = true;
		}

		return validAuthor;

	}

}