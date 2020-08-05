#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "Admin.h"
#include "ErrorChecking.h" // checkUsername + int
/*Function Declarations*/
using namespace std;

/*ADMIN INTERFACE WITH 4 FUNCTIONS, DELETESTAFF, RESET PASSWORD, ADD STAFF AND SHOW STAFF DETAILS*/
/*      ADMIN PART 1 HAS BEEN COMPLETED 04/08/2O                                                                                         */
void AdminInterface()// can add to staff list as well as delete staff
{
    char option = ' ';
    do {
        cout << "What would you like to do?\n1. Manage Staff Logins\n2. Manage Book Collection\n3. Check Budget & set Quantity\n4. Login Report\n5. Return\nChoice: ";
        option = _getch();
        cout << option << '\n';
        if (option == '1')
        {
            char secondOption = ' ';
            do {
                cout << "\n1. Delete Staff\n2. Reset Password\n3. Add Staff\n4. Check Staff details\n5. Return\nChoice: ";
                secondOption = _getch();
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
                case '2':// error checking complete
                    int result;
                    do {
                        cout << "Please Enter the name of record you want to change the Password of: ";
                        getline(cin, staff);
                        cout << "\nEnter the old Password: ";
                        getline(cin, password);
                        result = CheckUsername(staff, password, 2);
                        if (result == -2)
                            cout << "Wrong username and Password!\n";
                        else if (result == -4)
                            cout << "Wrong Password, Try again!\n";
                        else
                            cout << "User Exists!\n";
                    } while (result < 0); // check user exists
                    cout << "\nEnter the new Password: ";
                    getline(cin, newPassword);
                    cout << "\nConfirm Password: ";
                    getline(cin, confirmPassword);
                    while (newPassword != confirmPassword) // confirm error
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
                        cout << "Enter the Password: ";
                        getline(cin, password);
                        cout << "Confirm Password: ";
                        getline(cin, confirmPassword);
                        while (password != confirmPassword)
                        {
                            cout << "Error, Passwords do not match! Please Re-enter the Password\n";
                            cout << "Enter the Password: ";
                            getline(cin, password);
                            cout << "Confirm Password: ";
                            getline(cin, confirmPassword);
                        }
                        cout << "Before adding the Staff would you like to change the staff name?\nCurrent Username: " << staff << "\n"
                            << "Press Y for confirmation and N to redo the Process!\nChoice: ";
                        thirdOption = _getch();
                        cout << thirdOption << "\n";
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
                case '5': break;
                default:
                {
                    cout << "Correct option wasn't found\n";
                }
                }
            } while (secondOption != '5');
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
        else if (option == '4')
        {
            //LoginReport(int time) ie since yesterday, since a week etc
        }
        else if (option == '5')
        {
            cout << "Returned!\n"; return;
        }
        else
        {
            cout << "Wrong Choice, Please Try Again! \n";
        }
    } while (option != '5');
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
int DeleteStaff(string staff)
{
    if (staff == "Staff:" || staff == "Admins:") return 0; // error checking
    string line, parts;
    ifstream StaffFile;
    ofstream temp;
    bool start = true, found = false;
    StaffFile.open("Existing Users.txt");
    temp.open("temp.txt");
    while (getline(StaffFile, line)) // read line by line
    {
        stringstream ss(line); // parse line
        getline(ss, parts, '#');
        if (start) // ensures the line Admins: doesnt get deleted
        {
            temp << line;
            start = false;
        }
        else if (parts != staff) // Carry all the entrees except the staff that we want to delete to another file
            temp << "\n" << line;
        else
        {
            cout << "Found! The record with the name " << staff << " has been deleted" << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Error: No user exists with the name: " << staff << "\n";
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