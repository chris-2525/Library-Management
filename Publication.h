
#ifndef SDDS_PUB_H__
#define SDDS_PUB_H__
#include <iostream>
#include "Date.h"
#include "Streamable.h"
namespace sdds {
	class Publication : public Streamable {
		char* m_title;
		char m_shelfId[5]{};
		int m_membership;
		int m_libRef;
		Date m_date;

		void setToDefault();

	public:


		Publication();
		~Publication();
		void setRef(int value);
		void resetDate();
		virtual void set(int member_id);
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;
		bool conIO(ios& io)const;
		ostream& write(ostream& os) const;
		istream& read(istream& istr);
		operator bool() const;
		Publication(const Publication&);
		Publication& operator=(const Publication&);


	};
}
#endif
