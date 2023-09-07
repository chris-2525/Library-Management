
#ifndef SDDS_STREAM_H__
#define SDDS_STREAM_H__
#include <iostream>
using namespace std;
namespace sdds {
	class Streamable {

	public:
		virtual ostream& write(ostream& ostr) const = 0;
		virtual istream& read(istream& istr) = 0;
		virtual bool conIO(ios& iostr) const = 0;
		virtual operator bool() const = 0;
		virtual ~Streamable() {};
	};

	std::ostream& operator<<(ostream& ostr, const Streamable& str);
	std::istream& operator>>(istream& istr, Streamable& str);
}
#endif
