// Final Project Milestone 5
// Date Module
// File	LibApp.h
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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
namespace sdds {
    class LibApp {
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        char filename[256];
        Publication* pubs[SDDS_LIBRARY_CAPACITY]; 
        int pubLoaded;
        int lastLibRef; 
        Menu pubType;

        bool confirm(const char* message);
        void load(); 
        void save();  
        int search(bool loan, bool available);  
        void returnPub();    
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:

        LibApp(const char* fileN, bool change = false);
        void run();
        Publication* getPub(int libRef);
        ~LibApp();
 


    };
}
#endif // !SDDS_LIBAPP_H




