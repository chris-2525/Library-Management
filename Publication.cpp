
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Publication.h"
#include "Lib.h"

using namespace std;
namespace sdds {

	Publication::Publication() {

		setToDefault();

	}

	void Publication::setToDefault() {

		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}

	Publication::~Publication() {
		delete[] m_title;
	}

	void Publication::setRef(int value) {
		if (value > -1) {
			m_libRef = value;
		}
	}

	void Publication::resetDate() {

		m_date = Date();
	}

	void Publication::set(int member_id) {
		if (member_id > 9999) {

			m_membership = member_id;
		}
		else {

			m_membership = 0;
		}
	}

	char Publication::type()const {
		return 'P';
	}

	bool Publication::onLoan()const {
		bool checkout = 0;

		if (m_membership > 0) {
			checkout = 1;
		}

		return checkout;
	}

	Date Publication::checkoutDate()const {
		return m_date;
	}

	bool Publication::operator==(const char* title)const {

		bool found = false;
		char* res = nullptr;

		res = strstr(m_title, title);
		if (res != nullptr) {
			found = true;
		}

		return found;
	}

	Publication::operator const char* ()const {
		return m_title;
	}

	int Publication::getRef()const {
		return m_libRef;
	}

	bool Publication::conIO(ios& io)const {

		bool sameAddr = false;

		if ((&io == &cout) || (&io == &cin)) {
			sameAddr = true;
		}

		return sameAddr;
	}

	ostream& Publication::write(ostream& os)const {

		if (conIO(os)) {

			os << "| " << m_shelfId << " | ";

			if ((strlen(m_title)) > SDDS_TITLE_WIDTH) {
				for (int i = 0; i < SDDS_TITLE_WIDTH; i++) {
					os << m_title[i];
				}
			}
			else {
				os << setfill('.') << setw(SDDS_TITLE_WIDTH);
				os.setf(ios::left);
				os << m_title;
			}

			os << setfill(' ');
			os.unsetf(ios::left);
			os << " | ";
			if (m_membership > 0) {
				os << m_membership;
			}
			else {
				os << " N/A ";
			}
			os << " | " << m_date << " |";


		}
		else {

			os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t';
			os << m_membership << '\t' << m_date;

			if (type() == 'P') {
				os << endl;
			}

		}
		return os;
	}

	istream& Publication::read(istream& istr) {

		Date tempD;
		string title;
		char sId[5]{};
		int mem = 0;
		int libRef = 0;

		setToDefault();

		if (conIO(istr)) {

			cout << "Shelf No: ";
			istr.getline(sId, SDDS_SHELF_ID_LEN + 1, '\n');

			if ((strlen(sId) != SDDS_SHELF_ID_LEN)) {
				istr.setstate(ios::failbit);
			}

			cout << "Title: ";
			getline(istr, title, '\n');
			cout << "Date: ";
			tempD.read(istr);


		}

		else {


			istr >> libRef;
			istr.ignore();
			istr.getline(sId, SDDS_SHELF_ID_LEN + 1, '\t');
			getline(istr, title, '\t');
			istr >> mem;
			istr.ignore();
			tempD.read(istr);

		}

		if (tempD.errCode() != 0) {
			istr.setstate(ios::failbit);
		}

		if (istr) {

			setToDefault();

			delete[] m_title;
			m_title = new char[title.length() + 1];
			strcpy(m_title, title.c_str());
			strcpy(m_shelfId, sId);
			m_membership = mem;
			m_libRef = libRef;
			m_date = tempD;

		}

		return istr;
	}

	Publication::operator bool() const {
		
		bool valid = 0;
		
		if (m_title != nullptr && m_shelfId[0] != '\0') {
			valid = true;
		}

		return valid;
	}


	Publication::Publication(const Publication& pub) {

		strncpy(m_shelfId, pub.m_shelfId, 4);
		m_membership = pub.m_membership;
		m_libRef = pub.m_libRef;
		m_date = pub.m_date;
		
		delete[] m_title;

		if (pub.m_title != nullptr) {

			m_title = new char[strlen(pub.m_title) + 1];
			strcpy(m_title, pub.m_title);

		}
		else
		{
			m_title = nullptr;
		}

	}

	Publication& Publication::operator=(const Publication& pub) {
		
		if (this != &pub) {
			
			strncpy(m_shelfId, pub.m_shelfId, 4);
			m_membership = pub.m_membership;
			m_libRef = pub.m_libRef;
			m_date = pub.m_date;
			
			delete[] m_title;
			
			if (pub.m_title != nullptr) {

				m_title = new char[strlen(pub.m_title) + 1];
				strcpy(m_title, pub.m_title);
			}
			else
			{
				m_title = nullptr;
			}
		
		}
		
		return *this;
	}
}
