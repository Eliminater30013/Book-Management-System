// Book Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include<fstream>
#include <sstream>
#include <cmath>
#include <conio.h>
#include "Book.h"
#include "BookList.h"

using namespace std;
istream& getline(std::istream& ins, int& n);
int StartupMessage();//ENSURE ERROR CHECKING PLS
void DisplayBooksInterface();
vector<vector<string>> LoadBooks();
void Printout_BookVector(vector<Book> &BookVector);
void Print2DVector(vector<vector<string>>& Vector2D);
int CheckUsername(string username, string password, char option); // 0 success, 1 failure, -1 wrong password
void AdminInterface();
void StaffInterface();
void SearchBookInterface();
void AddBooksInterface();
void DeleteBooksInterface();
void UpdateBooksInterface();
void AppendtoBookFile(Book& aBook);
int DeleteStaff(string staff);
vector<Book> LoadsBooks_BookVector(vector<vector<string>>& BookVector);
vector<Book> LoadBooksQuickly();
int MAXQUANTITY_SETBY_ADMIN = 100;
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
vector<vector<string>> LoadBooks()
{
    /*  Read in a text file that has Books 
        If the text file exists append books to it else make a new file, the file name will be Books*/
    ifstream readFromFile("Books.txt", std::ios_base::in);
    vector<vector<string>> error {{"Books.txt file was not found"}};
    vector<vector<string>> BookVector;// will contain the book and its information, e.g. BookVector[Book number from 0][Book class members]
    bool success = false;
    if (readFromFile.is_open()) 
    {
        vector<string> BookString;//books will be read in, one book (line) at a time
        string FullBookString;
        while (readFromFile.good()) // keep reading if the state of the stream is OK. And Read text from file
        {
            while (getline(readFromFile, FullBookString)) // Read a Book and keep reading each line
            {
                stringstream BookStream; // create a string stream to better read the Book
                BookStream << FullBookString;
                while (BookStream >> std::ws) // trim any white space characters before each string element and keep reading the stringstream until the end
                {
                    string csvElement;
                    if (BookStream.peek() == '"') // if the next character has a speech mark(look for first speech mark), we know that we are dealing with a string
                    {
                        BookStream >> quoted(csvElement); // Input the string between the two quotation marks and unquote the speech marks.
                        string discard; // discard the comma string
                        getline(BookStream, discard, ',');// since all thats left in the stringstream is ',' followed the whats left of the stringstream, we know that
                    }                               // we have to get rid of the delimiter (the comma) and move onto the next element
                    else
                    {
                        getline(BookStream, csvElement, ',');// else read the the stringstream as csv
                    }
                    BookString.push_back(csvElement);// Put the appropriate informatio in to the Vector for storage
                }
                BookVector.push_back(BookString); // Save the Book
                BookString.clear(); // Clear the vector to be used again.
            }
            success = true;
        }
        readFromFile.close();
    }
    return { success == true ? BookVector : error };
}

vector<Book> LoadsBooks_BookVector(vector<vector<string>> &BookVector)
{
    vector<Book> BooksfromFile(1);
    if (BookVector.empty()) return BooksfromFile;
    BooksfromFile.resize(BookVector.size());
    int j = 0;
    for (unsigned int i = 0; i < BookVector.size(); i++) // Loop through a string 2D Vector and set all the Books within the booksfromFile vector
    {
        BooksfromFile[i].setId(atoi(BookVector[i][j].c_str())); // first convert the id from string to int, then set the id
        BooksfromFile[i].setCategory(BookVector[i][j + 1]);// set the category of the book
        BooksfromFile[i].setName(BookVector[i][j + 2]); // set the name of the book
        BooksfromFile[i].setDescription(BookVector[i][j + 3]);// set the description HAS SPEECH MARKS
        BooksfromFile[i].setPublisher(BookVector[i][j + 4]); // set publisher
        BooksfromFile[i].setReleaseDate(BookVector[i][j + 5]); // set release date
        BooksfromFile[i].setAuthor(BookVector[i][j + 6]); // set authour
        BooksfromFile[i].setPrice((float)atof(BookVector[i][j + 7].c_str())); // set Price
        BooksfromFile[i].setQuantity(atoi(BookVector[i][j + 8].c_str())); // set quantity
        BooksfromFile[i].setRating((float)atof(BookVector[i][j + 9].c_str())); // sets the rating
        BooksfromFile[i].setReview(BookVector[i][j + 10]); // set a review HAS SPEECH MARKS
        //BooksfromFile[i].BTEC_print(); // Once everything had been set Print out the Books Info
    }
    return BooksfromFile;
}

int StartupMessage()
{
    char option = ' ';
    string adminUsername,adminPassword, staffUsername, staffPassword;
    // check if the user is an Admin, Guest, Staff
    cout << "Please enter your Administration level by entering the number relating to you positions:\n";
    cout << "1. Admin\n2. Staff\n3. Guest\nChoice: ";
    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
    while (option != '1' && option != '2' && option != '3')
    {
        cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
        option = _getch(); // use getch() if this doesn't work ie in Codeblocks
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
                    while (option != '1' && option != '2' && option != '3')
                    {
                        cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
                        option = _getch(); // use getch() if this doesn't work ie in Codeblocks
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
                }
                while (option != '1' && option != '2' && option != '3')
                {
                    cout << "\nYou can only choose the numbers 1, 2 or 3, Please try again\nChoice: ";
                    option = _getch(); // use getch() if this doesn't work ie in Codeblocks
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

void AdminInterface()// can add to staff list as well as delete staff
{
    cout << "What would you like to do?\n1. Manage Staff Logins\n2. Manage Book Collection\n3. Check Budget & set Quantity\n4. Login Report\n";
    char option = _getch();
    if (option == '1')
    {
        cout << "\n1. Delete Staff\n2. Reset Password\n3. Add Staff\n4. Check Staff details\n";
        char secondOption = _getch();
        string staff;
        switch (secondOption)
        {
        case '1':
            cout << "Please Enter the name of record you want to delete: ";
            getline(cin, staff);
            DeleteStaff(staff); // 0 sucess -1 failure
            break;
        case '2':
            //ResetPassword(string staff) // see above
            break;
        case '3':
            //AddPassword(string staff) // see above
            break;
        case '4':
            //ShowStaffDetails()// see above
            break;
        default:
        {
            cout << "Correct option wasn't found\n";
        }
        }
    }
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
void StaffInterface()
{
    char option = ' ';
    while (option != '7')
    {
        cout << "\nWhat would you like to do?\n1. Add a Book\n2. Display Books\n3. Search Books\n4. Delete a Book\n5. Update Books\n"
            << "6. Help!\n7. Return to Main Menu\n";
        option = _getch();
        if (option == '1')
        {
            AddBooksInterface();
        }
        else if (option == '2')
        {
            DisplayBooksInterface();
        }
        else if (option == '3')
        {
            SearchBookInterface();
        }
        else if (option == '4')
        {
            DeleteBooksInterface();
        }
        else if (option == '5')
        {
            UpdateBooksInterface();
        }
        else if (option == '6')
        {
            // HelpMenu()
        }
        else if (option == '7')
        {
            return;
        }
        else
        {
            cout << "Invalid Key pressed, Please try again\n" << endl;
        }
    }
}

int DeleteStaff(string staff)
{
    string line;
    ifstream StaffFile;
    ofstream temp;
    StaffFile.open("Existing Users.txt");
    temp.open("temp.txt");
    while (getline(StaffFile, line)) // read line by line
    {
        if (line.substr(0,staff.size()) != staff) // Carry all the entrees excep the staff that we want to delete to another file
            temp << line << endl;
    }
    cout << "The record with the name " << staff << " has been deleted if it existed" << endl;
    StaffFile.close();
    temp.close();
    remove("Existing Users.txt");
    rename("temp.txt", "Existing Users.txt");
    return 0;// if succesful
}

void Print2DVector(vector<vector<string>>& Vector2D)
{
    for (unsigned int i = 0; i < 3; i++) // Size is 11.
    {
        cout << "Vector " << i << " in Catalog\n";
        for (unsigned int j = 0; j < Vector2D[i].size(); j++)
            cout << Vector2D[i][j] << "\n";
    }
}
// Overload function that allows us to check if integer has been entered
istream& getline(std::istream& ins, int& n)
{
    n = 0;

    // Read a line (terminated by ENTER|NEWLINE) from the user
    string s;
    if (getline(ins, s))
    {
        // Get rid of any trailing whitespace
        s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

        // Convert it to integer
        std::istringstream ss(s);
        ss >> n;

        // Check to see that there is nothing left over
        if (!ss.eof()) // if there is still something in cin then set the fail bit
            ins.setstate(std::ios::failbit);
    }
    return ins;
}

void AppendtoBookFile(Book &aBook)
{
    ofstream writeToFile("Books.txt", std::ios_base::app);
    writeToFile << "\n"<< aBook;
}
void RewriteBookFile(vector<Book> &Books)
{
    ofstream writeToFile("Books.txt", std::ios_base::out);
    for (size_t i = 0; i < Books.size(); i++)
    {
        if (i == Books.size() - 1)
            writeToFile << Books[i];
        else
            writeToFile << Books[i] << "\n";
    }
}
void DisplayBooksInterface()
{
    vector<vector<string>> _2DVector = LoadBooks();
    vector<Book> books = LoadsBooks_BookVector(_2DVector);
    Printout_BookVector(books);
}
void Printout_BookVector(vector<Book>& BookVector)
{
    for (unsigned int i = 0; i < BookVector.size(); i++)
    {
        cout << "Book " << i + 1 << " in Catalogue\n";
        BookVector[i].BTEC_print();
    }
}
void SearchBookInterface()
{
    cout << "Search a book by:\n1. ID \n2. Category\n3. Name\n4. Author\n";
    char option = _getch();
    vector<Book> bookVector2D = LoadBooksQuickly();
    vector<int> position;
    while (option == '1' || option == '2' || option == '3' || option == '4')
    {
        if (option == '1')
        {
            int ID;
            cout << "Enter ID Number: ";
            while (!getline(cin, ID))
            {
                cout << "Invalid ID number entered, Try again: ";
            }
            for (size_t i = 0; i < bookVector2D.size(); i++)
            {
                if (bookVector2D[i].getId() == ID)
                {
                    position.push_back(i);
                }
            }
            if (position.empty())
            {
                cout << "No books found with the ID: " << ID << endl;
                return;
            }
            break;
        }
        else if (option == '2')
        {
            string category;
            cout << "Enter Category: ";
            getline(cin, category);
            // Function checks valid categories
            for (size_t i = 0; i < bookVector2D.size(); i++)
            {
                if (bookVector2D[i].getCategory().find(category) != string::npos)
                {
                    position.push_back(i);
                }
            }
            if (position.empty())
            {
                cout << "No books found with the Category: " << category << endl;
                return;
            }
            break;
        }
        else if (option == '3')
        {
            string Name;
            cout << "Enter Name: ";
            getline(cin, Name);
            // do find instead here
            for (size_t i = 0; i < bookVector2D.size(); i++)
            {
                if (bookVector2D[i].getName().find(Name) != string::npos)
                {
                    position.push_back(i);
                }
            }
            if (position.empty())
            {
                cout << "No books found with the Name: " << Name << endl;
                return;
            }
            break;
        }
        else if (option == '4')
        {
            string Author;
            cout << "Enter Author's Name: ";
            getline(cin, Author);
            for (size_t i = 0; i < bookVector2D.size(); i++)
            {
                //cout << bookVector2D[i].getAuthor() << endl;
                if (bookVector2D[i].getAuthor().find(Author) != string::npos)
                {
                    position.push_back(i);
                }
            }
            if (position.empty())
            {
                cout << "No books found with the Author: " << Author << endl;
                return;
            }
            break;
        }
        else
        {
            cout << "Invalid Option, Try again! ";
            option = _getch();
        }
    }
    
    for (vector<int>::iterator i = position.begin(); i < position.end(); i++) // print out the book content of the position vector
    { // use of iterators to allow easy movement along the position vector
        bookVector2D[*i].BTEC_print();
        cout << endl; // write it out - new line for every book
    }
}
void AddBooksInterface()
{
    Book newbook;
    //cout << newbook.getNumberofBooks() << endl;
    cout << "ID: ";
    int input_ID;
    while (!getline(cin, input_ID) || input_ID != newbook.getNumberOfBooks()) // Check if greater than ID count! change 8 later
    {
        cin.clear();
        cout << "Try again, current ID number available: " << newbook.getNumberOfBooks()  << "\nID: ";
    }

    cout << "Category: ";
    string category;
    getline(cin, category);
    //checkcategoryFunction

    cout << "Name: ";
    string name;
    getline(cin, name);
    //checknameFunction

    cout << "Description: ";
    string description;
    getline(cin, description);
    //checkdescriptionFunction

    cout << "Publisher: ";
    string publisher;
    getline(cin, publisher);
    //checkpublisherFunction

    cout << "ReleaseDate: ";
    string releaseDate;
    getline(cin, releaseDate);
    //checknReleaseDateFunction

    cout << "Author: ";
    string author;
    getline(cin, author);
    //checkAuthorFunction

    cout << "Price: ";
    string s_price;
    getline(cin, s_price);
    float price = stof(s_price);
    //checkPriceFunction

    cout << "Quantity: ";
    int quantity = 0;
    while (!getline(cin, quantity) || quantity > MAXQUANTITY_SETBY_ADMIN) // Ensure not more than 100 quantity
    {
        cin.clear();
        cout << "Try again";
    }
    cout << "Rating: ";
    string s_rating;
    getline(cin, s_rating);
    float rating = stof(s_rating);

    cout << "Review: ";
    string review;
    getline(cin, review);
    //checkReviewFunction

    newbook.SetAll(input_ID, category, name, description, publisher, releaseDate, author, price, quantity, rating, review);
    AppendtoBookFile(newbook);
    cout << "Success!\n";
}
void DeleteBooksInterface()
{
    vector<Book> Books = LoadBooksQuickly();

    vector<int> position;
    string line;
    ifstream BookFile;
    ofstream temp;
    cout << "Enter the ID of the Book you would like to delete: ";
    int input_ID;
    //cout << Books[0].getNumberOfBooks() << endl;
    while (!getline(cin, input_ID) || input_ID <= 0 || input_ID >= Books[0].getNumberOfBooks()) // Ensue that ID is in valid range
    {
        cin.clear();
        cout << "Try again, the ID number must be greater than 0: ";
    }
    BookFile.open("Books.txt");
    temp.open("temp.txt");
    for (size_t i = 0; i < Books.size(); i++)
    {
        if (Books[i].getId() == input_ID)
        {
            position.push_back(i);
        }
    }
    if (position.empty())
    {
        cout << "No books found with the ID: " << input_ID << endl;
        return;
    }
    else
    {
        for (vector<int>::iterator i = position.begin(); i < position.end(); i++) // print out the book content of the position vector
        { // use of iterators to allow easy movement along the position vector
            Books[*i].BTEC_print();
            cout << endl; // write it out - new line for every book
        }
    }
    cout << "Would you like to delete this Book? Press 'Y' for Yes and 'N' for No";
    char choice = _getch();
    while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y')
    {
        cout << "Wrong Key pressed, Try again!\n";
        choice = _getch();
    }
    if (choice == 'n' || choice == 'N')
        return;
    cout << "Checking the File" << endl;
    bool foundline = false;
    while (getline(BookFile, line)) // read line by line
    {
        stringstream bit(line);
        string parts;
        getline(bit, parts, ',');
        if (( parts != to_string(input_ID)) && !foundline)
        {
            // Carry all the entrees except the staff that we want to delete to another file
            temp << line << endl;
        }
        else if(parts == to_string(input_ID))
        {
            foundline = true;
            continue;
        }
        else
        {
            int new_id = stoi(parts) - 1;
            line.replace(0, parts.length(), to_string(new_id));
            temp << line << endl;
        }
    }
    cout << "The record with the ID Number " << input_ID << " has been deleted" << endl;
    BookFile.close();
    temp.close();
    remove("Books.txt");
    rename("temp.txt", "Books.txt");
}
void UpdateBooksInterface()
{
    cout << "Update a book by:\n1. Rating \n2. Category\n3. Name\n4. Description"
        << "\n5. Publisher\n6. ReleaseDate, \n7. Author"
        << "\n8. Price\n9. Review";
    char option = _getch();
    while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5' && option != '6' && option != '7' && option != '8' && option != '9')
    {
        cout << "\nWrong Option entered Try again: ";
    }
    vector<Book> Books = LoadBooksQuickly();
    cout << "Enter ID of Book you would like to update: ";
    int input_ID;
    while (!getline(cin, input_ID) || input_ID < 0 || input_ID >= Books[0].getNumberOfBooks()) // Check if greater than ID count! change 8 later
    {
        cin.clear();
        cout << "Invalid ID, Try again\nID: ";
    }
    Books[input_ID].BTEC_print();
    cout << "Would you like to Update this Book? Press 'Y' for Yes and 'N' for No";
    char choice = _getch();
    while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y')
    {
        cout << "Wrong Key pressed, Try again!\n";
        choice = _getch();
    }
    if (choice == 'n' || choice == 'N')
    return;
    if (option == '1')
    {
        cout << "Enter new Rating: ";
        string s_rating;
        getline(cin, s_rating);
        float rating = stof(s_rating);
        Books[input_ID].setRating(rating);
    }
    else if (option == '2') 
    {
        cout << "Category: ";
        string category;
        getline(cin, category);
        //checkcategoryFunction
        Books[input_ID].setCategory(category);
    }
    else if (option == '3')
    {
        cout << "Name: ";
        string name;
        getline(cin, name);
        //checknameFunction
        Books[input_ID].setCategory(name);
    }
    else if (option == '4')
    {
        cout << "Description: ";
        string description;
        getline(cin, description);
        //checkdescriptionFunction 
        Books[input_ID].setDescription(description);
    }
    else if (option == '5')
    {
        cout << "Publisher: ";
        string publisher;
        getline(cin, publisher);
        //checkpublisherFunction
        Books[input_ID].setPublisher(publisher);
    }
    else if (option == '6')
    {
        cout << "ReleaseDate: ";
        string releaseDate;
        getline(cin, releaseDate);
        //checknReleaseDateFunction
        Books[input_ID].setReleaseDate(releaseDate);
    }
    else if (option == '7')
    {
        cout << "Author: ";
        string author;
        getline(cin, author);
        //checkAuthorFunction
        Books[input_ID].setAuthor(author);
    }
    else if (option == '8')
    {
        cout << "Price: ";
        string s_price;
        getline(cin, s_price);
        float price = stof(s_price);
        //checkPriceFunction
        Books[input_ID].setPrice(price);
    }
    else if (option == '9')
    {
        cout << "Review: ";
        string review;
        getline(cin, review);
        Books[input_ID].setReview(review);
    }
    else {
        cout << "ERROR 812" << endl;
            return;
    }
    ofstream writeToFile("Books.txt", std::ios_base::out);
    RewriteBookFile(Books);
}
vector<Book> LoadBooksQuickly() 
{
    vector<vector<string>> books2d = LoadBooks();
    vector<Book> books = LoadsBooks_BookVector(books2d);
    //cout << books[0].getNumberOfBooks() << endl;
    return books;
}