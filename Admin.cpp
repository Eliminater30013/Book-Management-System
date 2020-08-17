#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Admin.h"
#include "Staff.h"
#include "ErrorChecking.h" // checkUsername + valid int
using namespace std;
/*class Admin*/
Admin::Admin() // initial budgets
{
    maxQuantity = 100;
    maxBudget = 1000;
    totalQuantity = 100 * maxQuantity; // can be varied later on
    totalBudget = 100 * maxBudget;
}

Admin::Admin(int M_Q, int M_B, int T_B, int T_Q) : maxQuantity(M_Q), maxBudget(M_B), totalBudget(T_B), totalQuantity(T_Q)
{
}

Admin::~Admin()
{
}

void Admin::setall(int M_Q, int M_B, int T_B, int T_Q)
{
    maxQuantity = M_Q;
    maxBudget = M_B;
    totalBudget = T_B;
    totalQuantity = T_Q;
}


/*Function Declarations*/

/*ADMIN INTERFACE WITH 4 FUNCTIONS, DELETESTAFF, RESET PASSWORD, ADD STAFF AND SHOW STAFF DETAILS*/
/*      ADMIN PART 1 HAS BEEN COMPLETED 04/08/2O                                                                                         */
void AdminInterface(string user)// can add to staff list as well as delete staff
{
    char option = ' '; 
    string start = getDate_Time();
    do {
        cout << "\nWhat would you like to do?\n1. Manage Staff Logins\n2. Check Budget & set Quantity\n3. Login Report\n4. Return\nChoice: ";
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
                        cout << "Before adding the new staff member, could you please confirm the staff's username?\nCurrent Username: " << staff << "\n"
                            << "Press Y for confirmation and N to start the process over again.\nChoice: ";
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
            CheckBudget_and_Quantity();// plus give option to set budget need total cost from everything // can define quantity
        }
        else if (option == '3')
        {
            ifstream getLoginReport("LoginReport.txt", ios_base::in);
            cout << getLoginReport.rdbuf();
            getLoginReport.close();
        }
        else if (option == '4')
        {
            cout << "Returned!\n"; break;
        }
        else
        {
            cout << "Wrong Choice, Please Try Again! \n";
        }
    } while (option != '4');
    string end = getDate_Time();
    ofstream LoginReport("LoginReport.txt", ios_base::app);
    LoginReport << "        Name: " << user << "\nStart time: " << start << "End time:   " << end;
    LoginReport.close();
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
            cout << left;
            for (size_t j = 0; j < LoginDetails[i].size(); j += 2)
            {
                if (!i)
                    cout <<  "Username: "<< setw(20) << LoginDetails[i][j] <<  "Password: " << LoginDetails[i][j + 1] << endl;
                else
                    cout << "Username: " << setw(20) << LoginDetails[i][j] << "Password: " << LoginDetails[i][j + 1] << endl;
            }
        }
    }
    else
        cout << "File is empty!\n";
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void CheckBudget_and_Quantity() // later add a method to get the live total of the number of books per category, total number of books, how mush money has already been spent etc.
{
    Admin admin;
    string fileName = "Budget.txt";
    if (file_exists(fileName))
    {
        string bits, line;
        vector<int> budget;
        ifstream file(fileName, ios_base::in);
        getline(file, line);
        file.close();
        stringstream ss(line);
        while (getline(ss, bits, ','))
        {
            try {
                budget.push_back(stoi(bits));
            }
            catch (exception& e)
            {
                cout << e.what();
                return;
            }
        }
        admin.setall(budget[2], budget[0], budget[1], budget[3]);
    }
    char choice = ' ';
    vector<int> book_size = getNumberOfBooks();
    while (choice != 'R' && choice != 'r') {
        cout << "The current budget is $" << admin.getMaxBudget() << " per genre and the total is $" << admin.getTotalBudget() 
            << ".\nCurrently, total money spent = $" << book_size.at(2)<< "\nThe maximum number of books per category to aim for is " << admin.getMaxQuantity()
            << " and the total number of books to aim for is " << admin.getTotalQuantity() << ".\nCurrently, the total number of books is: " << book_size.at(1) << "\nWould you like to update the buget/quantity? Press B to update the budget, Q to update the quantity and R to return\nChoice: ";
        choice = _getch();
        cout << choice << endl;
        while (choice != 'r' && choice != 'R' && choice != 'b' && choice != 'B' && choice != 'q' && choice != 'Q')
        {
            cout << "Invalid option. Please try again\nChoice: ";
            choice = _getch();
            cout << choice << endl;
        }
        if (choice == 'q' || choice == 'Q')
        {
            string str1, str2;
            while (true)
            {
                cout << "Enter new Quantity per category: "; // later you can set each quantity seperately per category 
                getline(cin, str1);
                try {
                    int i_str1 = stoi(str1);
                    if (i_str1 < book_size[0]) throw i_str1;
                    admin.setMaxQuantity(i_str1);
                    break;
                }
                catch (...) {
                    cout << "Invalid number entered, please try again.\n";
                }
            }
            while (true)
            {
                cout << "Enter total Quantity: ";
                getline(cin, str2);
                try {
                    int i_str2 = stoi(str2);
                    if (i_str2 < book_size[1]) throw i_str2;
                    admin.setTotalQuantity(i_str2);
                    break;
                }
                catch (...) {
                    cout << "Invalid number entered, please try again.\n";
                }
            }
        }
        else if (choice == 'b' || choice == 'B')
        {
            string str1, str2;
            int i_str1, i_str2;
            while (true)
            {
                cout << "Enter new Budget per category:$"; // later you can set each budget seperately per category
                getline(cin, str1);
                try {
                    i_str1 = stoi(str1);
                    if (i_str1 < 0) throw i_str1;
                    admin.setMaxBudget(i_str1);
                    break;
                }
                catch (...) {
                    cout << "Invalid number entered, please try again.\n";
                }
            }
            while (true)
            {
                cout << "Enter total Budget:$";
                getline(cin, str2);
                try {
                    i_str2 = stoi(str2);
                    if (i_str2 < 0 || i_str1 > i_str2) throw i_str2;
                    admin.setTotalBudget(i_str2);
                    break;
                }
                catch (...) {
                    cout << "Invalid number entered, please try again.\n";
                }
            }
        }
        else
        {
            cout << "Returning..." << endl;
        }
        ofstream file("Budget.txt", ios_base::out); // max per category then total
        file << admin.getMaxBudget() << ',' << admin.getTotalBudget() << ',' << admin.getMaxQuantity() << ',' << admin.getTotalQuantity();
        file.close();
    }
}

bool file_exists(string& name) {
    ifstream f(name.c_str()); // ensures that the argument is in correct format 
    return f.good();
}