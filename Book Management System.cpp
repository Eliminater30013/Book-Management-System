// Book Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <conio.h>
#include "Book.h"
#include "Admin.h"
#include "Staff.h"

/*Function Declarations*/
using namespace std;
int StartupMessage();//ENSURE ERROR CHECKING PLS

int CheckUsername(string username, string password, char option); // 0 success, 1 failure, -1 wrong password

/*Main*/
int main()
{
    vector<vector<string>> StoredBooks = LoadBooks();
    if (StoredBooks[0][0] != "Books.txt file was not found" )// Load in the books from storage (txt file) if your cant, then end the program later do a try catch
    {
        cout << "Books have been loaded successfully..." << endl;
        vector<Book> books;
        books = LoadsBooks_BookVector(StoredBooks);
        //Printout_BookVector(books);
        int result = StartupMessage();
        cout << "\nResult: " << result << "\n";
        switch (result)
        {
        case 0:
            //GuestInterface();
            cout << "Guest" << endl;
            break;
        case 1:
            AdminInterface();
            cout << "Admin Success!" << endl;
            // move on to Admin interface
            break;
        case 2:
            StaffInterface();
            cout << "Staff Success!" << endl;
            // Staff interface
            break;
        default:
        {
            cout << "The code has been broken, and an error log has been created as a text file" << endl;
            // text file with what was entered in but most likely nothing as this will never happen
        }
        }
    }
    
    
    /*Book one;
    one.BTEC_print();
    one.SetAll(1, "Horror", "Mom's basement", "A story about how a fat man somehow defeated his worst nemesis", "Pelican Foundation",
        "01/12/2003", "James Patterson", 2.99, 20, 4.5, " I loved this book, it was sso interesting to see how Weebs live and go about their day to day life");
    one.BTEC_print();*/
}

int StartupMessage()
{
    char option = ' ';
    string adminUsername, adminPassword, staffUsername, staffPassword;
    // check if the user is an Admin, Guest, Staff
    cout << "Please enter your Administration level by entering the number relating to you positions:\n";
    cout << "1. Admin\n2. Staff\n3. Guest\nChoice: ";
    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
    cout << option;
    while (option != '1' && option != '2' && option != '3')
    {
        cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
        option = _getch(); // use getch() if this doesn't work ie in Codeblocks
        cout << option;
    }
    if (option == '1' || option == '2') // if Admin or Staff
    {
        cout << "\nEnter your username\nUsername: ";
        getline(cin, adminUsername); // get the Admins username whilst ignoring option 
        cout << "Enter your password\nPassword: ";
        getline(cin, adminPassword);
        int result = CheckUsername(adminUsername, adminPassword, option); // returns a integer which shows the result to check if username,password combination exists.
        while (result == -1 || result == -2 || result == -3 || result == -4) // let the user try to renter their password
        {
            if (result == -1 || result == -2)
            {
                cout << "Wrong username entered, Please enter your username again," <<
                    "or enter 'REDO' to go back to the start menu \nUsername: ";
                getline(cin, adminUsername);
                if (adminUsername == "REDO") // since we redid it option has a chance of being threee so we need to account for it
                {
                    cout << "Please enter your Administration level by entering the number relating to you positions:\n";
                    cout << "1. Admin\n2. Staff\n3. Guest\nChoice: ";
                    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
                    cout << option;
                    while (option != '1' && option != '2' && option != '3')
                    {
                        cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
                        option = _getch(); // use getch() if this doesn't work ie in Codeblocks
                        cout << option;
                    }
                    if (option == '3')
                    {
                        return 0; // option 3 guestScreen
                    }
                    cout << "\nEnter your username\nUsername: ";
                    getline(cin, adminUsername); // get the Admins username whilst ignoring option 
                    cout << "Enter your password\nPassword: ";
                    getline(cin, adminPassword);
                }
                else // just enter the password
                {
                    cout << "Enter your password\nPassword: ";
                    getline(cin, adminPassword);
                }
                result = CheckUsername(adminUsername, adminPassword, option);
            }
            else if (result == -3 || result == -4)
            {
                cout << "Wrong password entered, Please enter your password again or type 'BACK' to re-enter username," <<
                    "or enter 'REDO' to go back to the start menu \nPassword: ";
                getline(cin, adminPassword);
                if (adminPassword == "REDO") // since we redid it option has a chance of being threee so we need to account for it
                {
                    cout << "Please enter your Administration level by entering the number relating to you positions:\n";
                    cout << "1. Admin\n2. Staff\n3. Guest\nChoice: ";
                    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
                    cout << option;
                }
                while (option != '1' && option != '2' && option != '3')
                {
                    cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
                    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
                    cout << option;
                }
                if (option == '3')
                {
                    return 0; // option 3 guestScreen
                }
                if (adminPassword == "BACK" || adminPassword == "REDO")
                {
                    cout << "Enter your username\nUsername: ";
                    getline(cin, adminUsername); // get the Admins username whilst ignoring option 
                    cout << "Enter your password\nPassword: ";
                    getline(cin, adminPassword);
                }
                result = CheckUsername(adminUsername, adminPassword, option);
            }
        }
        return result; // will only return 0, 1 , 2 for sucess
    }
    else if (option == '3')
    {
        return 0;
    }
    else
    {
        cout << "Option was neither 1, 2,3" << endl;
        return 100; // unknown error
    }
}



int CheckUsername(string username, string password, char option)
{
    int itExists = 1; // assume the username initially doesn't exist e.g failure
    ifstream readFromFile; // create an input stream to allow us to read a file in
    string txtFromFile = "";
    vector<string> IndidvidualStrings;
    readFromFile.open("Existing Users.txt", std::ios_base::in);
    /*The following code will return string vector with each even number position being the username and each odd position will contain the password*/
    if (readFromFile.is_open() && option == '1' ) // if the file can be opened
    {
        // Read text from file
        while (readFromFile.good()) //while the end of the file is not reached
        {
            getline(readFromFile, txtFromFile); // read one line in
            if (txtFromFile == "Staff:") // read until the Staff subsection
                break;
            if (txtFromFile == "Admins:") // if the string Admins: is found continue the loop as we want the information below this.
                continue;// do not include this word in the IndidvidualStrings vector below
            stringstream ss(txtFromFile);// create a string stream 
            while (getline(ss, txtFromFile, '#'))
                IndidvidualStrings.push_back(txtFromFile);
        }
    }
    else if (readFromFile.is_open() && option == '2') // if the file can be opened
    {
        bool isitStaff = false;
        // Read text from file
        while (readFromFile.good()) //while the end of the file is not reached
        {
            getline(readFromFile, txtFromFile); // read one line in
            if (txtFromFile != "Staff:" && isitStaff == false) // find the Staff subsection
                continue;
            isitStaff = true;
            stringstream ss(txtFromFile);// create a string stream 
            while (getline(ss, txtFromFile, '#'))
                IndidvidualStrings.push_back(txtFromFile);
        }
        IndidvidualStrings.erase(IndidvidualStrings.begin()); // get rid of the Staff: title
    }
    else
    {
        cout << "Error: The option received is neither 1 nor 2! " << endl;
    }
    readFromFile.close();// close the file
    for (size_t i = 0; i < IndidvidualStrings.size(); i += 2) // check every username in the database
    {
        if (IndidvidualStrings.at(i) == username) // if the username matches, check the password
        {
            if (IndidvidualStrings.at(i + 1) == password) // if the password matches then the username "Exists!"
                itExists = 0;
            else
                itExists = -1; // wrong password has been entered
            break;// get out of for loop and return result
        }
    }
    if (itExists == 0 && option == '1')
        return 1; // Admin success
    else if (itExists == 0 && option == '2')
        return 2; // Staff sucess
    else if (itExists == 1 && option == '1')
        return -1; // Admin failure
    else if (itExists == 1 && option == '2')
        return -2; // Staff Failure
    else if (itExists == -1 && option == '1')
        return -3; // Admin wrong password
    else if (itExists == -1 && option == '2')
        return -4; // Staff wrong password
    else
    {
        cout << "Error: Combination does not exist - code has been broken" << endl;
        return -100; // wont happen
    }
}

