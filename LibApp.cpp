
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;
namespace sdds {
    
    bool LibApp::confirm(const char* message) {

        bool confirmation = false;
        Menu temp(message);
        temp << "Yes";
        if (temp.run()) {
            confirmation = true;
        }
        else
        {
            cout << endl;
        }

        return confirmation;
    }

    void LibApp::load(){
                        
        ifstream file(filename);
        char type{};

        cout << "Loading Data" << endl;

        if (filename != nullptr) {

            for (int i = 0; file; i++) {

                if (file) {

                    file >> type;
                    file.ignore();

                    if (type == 'P') {
                        pubs[i] = new Publication;
                    }

                    else if (type == 'B') {
                        pubs[i] = new Book;
                    }

                    file >> *pubs[i];
                    if ((pubs[i]->getRef()) > 0) {
                        pubLoaded++;
                        lastLibRef = pubs[i]->getRef();
                    }
                    else {
                        delete pubs[i];
                        pubs[i] = nullptr;
                    }

                }

            }


        }


    }

    void LibApp::save() {

        cout << "Saving Data" << endl;

        ofstream file(filename);

        if (filename != nullptr) {
            if (file) {
                for (int i = 0; i < pubLoaded; i++) {

                    if (pubs[i]) {

                        if ((pubs[i]->getRef()) != 0) {
                            file << *pubs[i];
                        }
                    }

                }
            }
        }

    }

    int LibApp::search(bool loan, bool available) {

        int selection = -1;
        char search[TITLE +1] = "\0";
        int ref = -1; 
        PublicationSelector ps("Select one of the following found matches:");

        pubType.displayMenu();
        cout << "> ";
        cin >> selection;

        //clear input buffer
        while (cin.get() != '\n') {

        }

        if ((selection == 1) || (selection == 2)) {

            cout << "Publication Title: ";

            cin.get(search, TITLE + 1, '\n');

            if (!cin) {

                cin.clear(); 
                cin.ignore(); 
            }

            for (int i = 0; i < pubLoaded; i++) {
                
                if (selection == 1) {
     
                    if (pubs[i]->type() == 'B') {

                        //search all 
                        if (loan && available) {

                            if (strstr(*pubs[i], search)) {
                                ps << pubs[i];
                            }
                        }
                        //search available
                        if (!loan && available) {

                            if (strstr(*pubs[i], search)) {
                                if (!(pubs[i]->onLoan())) {
                                    ps << pubs[i];
                                }
                            }
                        }
                        //search only on loan
                        if (loan && !available) {

                            if (strstr(*pubs[i], search)) {
                                if (pubs[i]->onLoan()) {
                                    ps << pubs[i];
                                }
                            }
                        }

                    }
                    
                }
                if (selection == 2) {

                    if (pubs[i]->type() == 'P') {
                        //search all 
                        if (loan && available) {

                            if (strstr(*pubs[i], search)) {
                                ps << pubs[i];
                            }
                        }
                        //search available
                        if (!loan && available) {

                            if (strstr(*pubs[i], search)) {
                                if (!(pubs[i]->onLoan())) {
                                    ps << pubs[i];
                                }
                            }
                        }
                        //search only on loan
                        if (loan && !available) {

                            if (strstr(*pubs[i], search)) {
                                if (pubs[i]->onLoan()) {
                                    ps << pubs[i];
                                }
                            }
                        }
                    }
                    
                }
            }
        }
        else {
            cout << "Aborted!" << endl << endl;
        }

        if (ps) {
            ps.sort();
            ref = ps.run(); 
            if (ref > 0) {
                cout << *getPub(ref) << endl;
            }
            else {
                cout << "Aborted!" << endl << endl;
            }
        }
        else {
            cout << "No matches found!" << endl << endl; 
        }
       
        return ref; 
    }

    void LibApp::returnPub() {
        
        int libRef = -1;
        Date date; 
        Date dateRes; 
        int dateDiff = 0;

        cout << "Return publication to the library" << endl;

        libRef = search(true, false);

        if (libRef > 0) {
            if (confirm("Return Publication?")) {
               
               dateRes = getPub(libRef)->checkoutDate();
               dateDiff = (date - dateRes);

               if (dateDiff > 15) {
                   cout << fixed; 
                   cout << setprecision(2);
                   cout << "Please pay " << "$" << (dateDiff-15) * .50 << " penalty for being "<< 
                       dateDiff-15 << " days late!" << endl;
               }

               getPub(libRef)->set(0);
               m_changed = true;
               cout << "Publication returned" << endl << endl;
            }
        }

    }

    void LibApp::newPublication() {
        
        int selection = -1; 
        Publication* temp{};

        if (pubLoaded == SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl << endl;
        }
        else {

            cout << "Adding new publication to the library" << endl;

            pubType.displayMenu();
            cout << "> ";
            cin >> selection;

            if (selection == 1 || selection == 2) {
                
                if (selection == 1) {
                    
                    temp = new Book;
     
                    while (cin.get() != '\n') {

                    }

                    cin >> *temp;

                }

                else if (selection == 2) {

                    temp = new Publication;

                    while (cin.get() != '\n') {

                    }

                    cin >> *temp;

                }

                if (cin) {

                    if (confirm("Add this publication to the library?")) {

                        if (temp != nullptr) {

                            lastLibRef++;
                            temp->setRef(lastLibRef);
                            pubs[pubLoaded] = temp;
                            pubLoaded++;
                            m_changed = true;
                            cout << "Publication added" << endl << endl;
                          
                        }
                        else {
                            cout << "Failed to add publication!";
                            delete temp;
                        }
                    }
                  
                }

                else {
                    cout << "Aborted!" << endl << endl;

                    cin.clear();
                    while (cin.get() != '\n') {

                    }

                    delete temp;
                }
            }
            else {
                cout << "Aborted!" << endl << endl;
            }

        }

    }

    void LibApp::removePublication() {
        int libRef = -1; 
        
        cout << "Removing publication from the library" << endl;
        libRef = search(true, true);
        if (libRef > 0) {
            if (confirm("Remove this publication from the library?")) {
                getPub(libRef)->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl << endl;
            }
        }

    }
    void LibApp::checkOutPub() {
        int libRef = -1;
        int membership = -1;
        cout << "Checkout publication from the library" << endl;
        libRef = search(false, true);

        if (libRef > 0) {
            if (confirm("Check out publication?")) {
                cout << "Enter Membership number: ";
                do {
                    cin >> membership;
                    if (membership > 9999 && membership < 99999) {
                        m_changed = true;
                        getPub(libRef)->set(membership);
                        cout << "Publication checked out" << endl << endl;
                    }
                    else {
                        cout << "Invalid membership number, try again: ";
                    }
                } while (membership < 9999 || membership > 99999);
            }
        }
    }

    LibApp::LibApp(const char* fileN, bool change) : m_mainMenu("Seneca Library Application"),
        m_exitMenu("Changes have been made to the data, what would you like to do?"), pubType("Choose the type of publication:") {

        m_changed = false;
        change = m_changed;
        
        m_mainMenu << "Add New Publication" << "Remove Publication" <<
            "Checkout publication from library" << "Return publication to library";
        
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        pubType << "Book" << "Publication";

        if (fileN!= nullptr) {
            strcpy(filename, fileN);
        }

        pubLoaded = 0; 
        lastLibRef = 0; 

        for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++) {
            pubs[i] = nullptr; 
        }

        load();

    }

    void LibApp::run() {

        int selection = -1;
        int exitSelect = -1;

        do {

            m_mainMenu.displayMenu();
            cout << "> ";
            cin >> selection;
            switch (selection) {
            case 1:
                newPublication();
                break;
            case 2:
                removePublication();
                break;
            case 3:
                checkOutPub();
                break;
            case 4:
                returnPub();
                break;
            default:

                if (m_changed) {

                    exitSelect = m_exitMenu.run();

                    switch (exitSelect) {
                    case 1:
                        save();
                        break;
                    case 2:
                        selection = -1;
                        cout << endl;
                        break;
                    case 0:
                        confirm("This will discard all the changes are you sure?");
                        break;
                    }

                }


            }

        } while (selection != 0);


        cout << endl;
        cout << "-------------------------------------------" << endl << "Thanks for using ";
        m_mainMenu.displayTitle() << endl;

    }

    Publication* LibApp::getPub(int libRef) {
        
        Publication* temp = nullptr; 

        for (int i = 0; i < pubLoaded; i++) {
            if (libRef == pubs[i]->getRef()) {

                temp = pubs[i];
            }
        }

        return temp; 
    }

    LibApp::~LibApp() {
        
        for (int i = 0; i < pubLoaded; i++) {
            delete pubs[i];
            pubs[i] = nullptr; 
        }
        
    }



}
