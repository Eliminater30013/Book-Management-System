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
/*Function Declarations*/
using namespace std;

/*ADMIN INTERFACE WITH 4 FUNCTIONS, DELETESTAFF, RESET PASSWORD, ADD STAFF AND SHOW STAFF DETAILS*/
/*                                                                                               */
void AdminInterface()// can add to staff list as well as delete staff
{
    cout << "What would you like to do?\n1. Manage Staff Logins\n2. Manage Book Collection\n3. Check Budget & set Quantity\n4. Login Report\n";
    char option = _getch();
    cout << option << '\n';
    if (option == '1')
    {
        cout << "\n1. Delete Staff\n2. Reset Password\n3. Add Staff\n4. Check Staff details\n";
        char secondOption = _getch();
        char thirdOption = 'N';
        cout << secondOption << '\n';
        string staff, password, newPassword, confirmPassword;;
        switch (secondOption)
        {
        case '1':
            cout << "Please Enter the name of record you want to delete: ";
            getline(cin, staff);
            DeleteStaff(staff); // 0 sucess -1 failure
            break;
        case '2':
            cout << "Please Enter the name of record you want to change the Password of: ";
            getline(cin, staff);
            cout << "\nEnter the old Password: ";
            getline(cin, password);
            // check if user with password exists;
            cout << "\nEnter the new Password: ";
            getline(cin, newPassword);
            cout << "\nConfirm Password: ";
            getline(cin, confirmPassword);
            while (newPassword != confirmPassword)
            {
                cout << "Error, Passwords do not match! Please Re-enter the Password\n";
                cout << "Enter the new Password: ";
                getline(cin, newPassword);
                cout << "\nConfirm Password: ";
                getline(cin, confirmPassword);
            }
            ResetPassword(staff, newPassword); // see above
            break;
        case '3':
            while (thirdOption == 'N' || thirdOption == 'n')
            {
                cout << "Please Enter the Name of the Staff: ";
                getline(cin, staff);
                cout << "\nEnter the Password: ";
                getline(cin, password);
                cout << "\nConfirm Password: ";
                getline(cin, confirmPassword);
                while (newPassword != confirmPassword)
                {
                    cout << "Error, Passwords do not match! Please Re-enter the Password\n";
                    cout << "Enter the new Password: ";
                    getline(cin, newPassword);
                    cout << "\nConfirm Password: ";
                    getline(cin, confirmPassword);
                }
                cout << "Before adding the Staff would you like to change the staff name?\nCurrent Username: " << staff << "\n"
                    << "Press Y for confirmation and N to redo the Process!\n";
                thirdOption = _getch();
                while ((thirdOption != 'N' && thirdOption != 'n') && (thirdOption != 'Y' && thirdOption != 'y'))
                {
                    cout << "\nWrong letter entered, Try Again\nChoice: ";
                    thirdOption = _getch(); // use getch() if this doesn't work ie in Codeblocks
                    cout << thirdOption;
                }
            }
            AddStaff(staff, password); // see above
            break;
        case '4':
            ShowStaffDetails();// see above
            break;
        default:
        {
            cout << "Correct option wasn't found\n";
        }
        }
    }
    //Completed ;}{
    else if (option == '2')
    {
        //BookOptions
    }
    else if (option == '3')
    {
        //ShowBudget() plus give option to set budget need total cost from everything // can define quantity
    }
    else if (option == 4)
    {
        //LoginReport(int time) ie since yesterday, since a week etc
    }
    else
    {
        cout << "Admin Interface error!\n";
    }
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
int DeleteStaff(string staff)
{
    string line;
    ifstream StaffFile;
    ofstream temp;
    bool start = true, found = false;
    StaffFile.open("Existing Users.txt");
    temp.open("temp.txt");
    while (getline(StaffFile, line)) // read line by line
    {
        if (start)
        {
            temp << line;
            start = false;
        }
        else if (line.substr(0, staff.size()) != staff) // Carry all the entrees except the staff that we want to delete to another file
            temp << "\n" << line;
        else
        {
            cout << "Found! The record with the name " << staff << " has been deleted" << endl;
            found = true;
        }
    }
    StaffFile.close();
    temp.close();
    remove("Existing Users.txt");
    rename("temp.txt", "Existing Users.txt");
    int returnValue = (found == true) ? 1 : 0;
    return returnValue;// if succesful
}

int ResetPassword(string staff, string newPassword)
{
    string line;
    ifstream StaffFile;
    ofstream temp;
    StaffFile.open("Existing Users.txt");
    temp.open("temp.txt");
    bool start = true, found = false;;
    while (getline(StaffFile, line)) // read line by line
    {
        if (start)
        {
            temp << line;
            start = false;
        }
        else if (line.substr(0, staff.size()) != staff) // Carry all the entrees except the staff that we want to delete to another file
            temp << "\n" << line;
        else
        {
            cout << "Found!" << endl;
            found = true;
            temp << "\n" << line.substr(0, staff.size()) << '#' << newPassword;
        }
    }
    cout << "The password with the name " << staff << " has been changed if it existed" << endl;
    StaffFile.close();
    temp.close();
    remove("Existing Users.txt");
    rename("temp.txt", "Existing Users.txt");
    int returnValue = (found == true) ? 1 : 0;
    return returnValue;// if succesful
}

int AddStaff(string staff, string password)
{
    ofstream writeToFile("Existing Users.txt", std::ios_base::app);
    writeToFile << "\n" << staff << '#' << password;
    writeToFile.close();
    return 0;
}

void ShowStaffDetails()
{
    ifstream readFromFile; // create an input stream to allow us to read a file in
    string txtFromFile = "";
    int logins = 0;
    vector<vector<string>> LoginDetails(2); // staff + admins
    readFromFile.open("Existing Users.txt", std::ios_base::in);
    /*The following code will return string vector with each even number position being the username and each odd position will contain the password*/
    if (readFromFile.is_open()) // if the file can be opened
    {
        // Read text from file and put it in the spreadsheetformat
        while (readFromFile.good()) //while the end of the file is not reached
        {
            getline(readFromFile, txtFromFile); // read one line in
            if (txtFromFile == "Admins:") // if the string Admins: is found continue the loop as we want the information below this.
                continue;// do not include this word in the LoginDetails vector below
            else if (txtFromFile == "Staff:") // read until the Staff subsection
                logins = 1; // This will ensure that the information will be in the LoginDetail[1]
            else
            {
                stringstream ss(txtFromFile);// create a string stream 
                while (getline(ss, txtFromFile, '#'))
                    LoginDetails[logins].push_back(txtFromFile);
            }
        }
        readFromFile.close();// close the file
    }
    else
    {
        cout << "File can't be opened!\n";
    }
    if (!LoginDetails.empty())
    {
        for (size_t i = 0; i < LoginDetails.size(); i++)
        {
            string message = (i == 0) ? "Admin Details: \n" : "Staff Details: \n";
            cout << message;
            for (size_t j = 0; j < LoginDetails[i].size(); j += 2)
            {
                if (!i)
                    cout << "Username: " << LoginDetails[i][j] << "\t\t\tPassword: " << LoginDetails[i][j + 1] << endl;
                else
                    cout << "Username: " << LoginDetails[i][j] << "\t\t\t\tPassword: " << LoginDetails[i][j + 1] << endl;
            }
        }
    }
    else
        cout << "File is empty!\n";
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////