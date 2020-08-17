// Book Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "Book.h"
#include "Admin.h"
#include "Staff.h"
#include "ErrorChecking.h" //mfor checkusername

using namespace std;
/*Function Declarations*/
int StartupMessage(string &user);
/*Main*/
int main()
{
    vector<Book> StoredBooks = LoadBooksQuickly(); string user = " ";
    while (!StoredBooks.empty())// Load in the books from storage (txt file) if your cant, then end the program later do a try catch
    {
        switch (StartupMessage(user))
        {
        case 0:
            cout << "\nProgram Terminated" << endl;
            return 0;
        case 1:
            AdminInterface(user);
            cout << "Admin Success!" << endl;
            // move on to Admin interface
            break;
        case 2:
            StaffInterface(user);
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
}

int StartupMessage(string &user)
{
    char option = ' ';
    string username, password;
    // check if the user is an Admin, Guest, Staff
    cout << "Please enter your Administration level by entering the number relating to your position:\n";
    cout << "1. Admin\n2. Staff\n3. Exit\nChoice: ";
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
        getline(cin, username); // get the Admins username whilst ignoring option 
        cout << "Enter your password\nPassword: ";
        getline(cin, password);
        int result = CheckUsername(username, password, option); // returns a integer which shows the result to check if username,password combination exists.
        while (result == -1 || result == -2 || result == -3 || result == -4) // let the user try to renter their password
        {
            if (result == -1 || result == -2)
            {
                cout << "Wrong username entered, Please enter your username again," <<
                    "or enter 'REDO' to go back to the start menu \nUsername: ";
                getline(cin, username);
                if (username == "REDO") // since we redid it option has a chance of being threee so we need to account for it
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
                    getline(cin, username); // get the Admins username whilst ignoring option 
                    cout << "Enter your password\nPassword: ";
                    getline(cin, password);
                }
                else // just enter the password
                {
                    cout << "Enter your password\nPassword: ";
                    getline(cin, password);
                }
                result = CheckUsername(username, password, option);
            }
            else if (result == -3 || result == -4)
            {
                cout << "Wrong password entered, Please enter your password again or type 'BACK' to re-enter username," <<
                    "or enter 'REDO' to go back to the start menu \nPassword: ";
                getline(cin, password);
                if (password == "REDO") // since we redid it option has a chance of being threee so we need to account for it
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
                if (password == "BACK" || password == "REDO")
                {
                    cout << "Enter your username\nUsername: ";
                    getline(cin, username); // get the Admins username whilst ignoring option 
                    cout << "Enter your password\nPassword: ";
                    getline(cin, password);
                }
                result = CheckUsername(username, password, option);
            }
        }
        user = username;
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

