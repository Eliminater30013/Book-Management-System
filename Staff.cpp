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

int MAXQUANTITY_SETBY_ADMIN = 100;



void StaffInterface()
{
    char option = ' ';
    while (option != '7')
    {
        cout << "What would you like to do?\n1. Add a Book\n2. Display Books\n3. Search Books\n4. Delete a Book\n5. Update Books\n"
            << "6. Help!\n7. Return to Main Menu\nChoice: ";
        option = _getch();
        cout << option << '\n';
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
            cout << "Invalid Key pressed, Please try again!\n";
        }
    }
}
void SearchBookInterface()
{
    vector<Book> bookVector2D = LoadBooksQuickly();
    vector<int> position;
    char option = ' ';
    while (option != '5')
    {
        cout << "Search a book by:\n1. ID \n2. Category\n3. Name\n4. Author\n5. Return\nChoice: ";
        option = _getch();
        cout << option << "\n";
        if (option == '1')
        {
            int ID;
            cout << "Enter ID Number: ";
            while (!getline(cin, ID))
            {
                cout << "Invalid ID number entered, Try again: ";
            }
            for (unsigned int i = 0; i < bookVector2D.size(); i++)
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
            for (unsigned int i = 0; i < bookVector2D.size(); i++)
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
            for (unsigned int i = 0; i < bookVector2D.size(); i++)
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
            for (unsigned int i = 0; i < bookVector2D.size(); i++)
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
        else if (option == '5') {
            cout << "Success!\n";
            break;
        }
        else {
            cout << "Wrong Choice. Try Again\n";
        }
    }
    if (!position.empty()) {
        for (vector<int>::iterator i = position.begin(); i < position.end(); i++) // print out the book content of the position vector
        { // use of iterators to allow easy movement along the position vector
            bookVector2D[*i].BTEC_print();
            cout << endl; // write it out - new line for every book
        }
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
        cout << "Try again, current ID number available: " << newbook.getNumberOfBooks() << "\nID: ";
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
    for (unsigned int i = 0; i < Books.size(); i++)
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
    cout << "Would you like to delete this Book? Press 'Y' for Yes and 'N' for No\nChoice: ";
    char choice = _getch();
    cout << choice;
    while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y')
    {
        cout << "Wrong Key pressed, Try again!\nChoice: ";
        choice = _getch();
        cout << choice;
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
        if ((parts != to_string(input_ID)) && !foundline)
        {
            // Carry all the entrees except the staff that we want to delete to another file
            temp << line << endl;
        }
        else if (parts == to_string(input_ID))
        {
            foundline = true;
            continue;
        }
        else if (BookFile.eof())
        {
            int new_id = stoi(parts) - 1;
            line.replace(0, parts.length(), to_string(new_id));
            temp << line;
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
        << "\n8. Price\n9. Review\n0.Return \nChoice: ";
    char option = _getch();
    cout << option;
    while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5' && option != '6' && option != '7' && option != '8' && option != '9' && option != '0')
    {
        cout << "\nWrong Option entered Try again: ";
        option = _getch();
        cout << option;
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
    cout << "Would you like to Update this Book? Press 'Y' for Yes and 'N' for No\nChoice: ";
    char choice = _getch();
    cout << choice;
    while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y')
    {
        cout << "Wrong Key pressed, Try again!\nChoice: ";
        choice = _getch();
        cout << choice;
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
    else if (option == '0') return;
    else {
        cout << "ERROR 420" << endl;
        return;
    }
    ofstream writeToFile("Books.txt", std::ios_base::out);
    RewriteBookFile(Books);
}
void DisplayBooksInterface()
{
    vector<vector<string>> _2DVector = LoadBooks();
    vector<Book> books = LoadsBooks_BookVector(_2DVector);
    Printout_BookVector(books);
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

int CheckUsername(string username, string password, char option)
{
    int itExists = 1; // assume the username initially doesn't exist e.g failure
    ifstream readFromFile; // create an input stream to allow us to read a file in
    string txtFromFile = "";
    vector<string> IndidvidualStrings;
    readFromFile.open("Existing Users.txt", std::ios_base::in);
    /*The following code will return string vector with each even number position being the username and each odd position will contain the password*/
    if (readFromFile.is_open() && (option == '1' || option == 1)) // if the file can be opened
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
    else if (readFromFile.is_open() && (option == '2' || option == 2) ) // if the file can be opened
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
    if (itExists == 0 && (option == '1'|| option == 1))
        return 1; // Admin success
    else if (itExists == 0 && (option == '2'|| option == 2))
        return 2; // Staff sucess
    else if (itExists == 1 && (option == '1'|| option == 1))
        return -1; // Admin failure
    else if (itExists == 1 && (option == '2'|| option == 2))
        return -2; // Staff Failure
    else if (itExists == -1 && (option == '1'|| option == 1))
        return -3; // Admin wrong password
    else if (itExists == -1 && (option == '2'|| option == 2))
        return -4; // Staff wrong password
    else
    {
        cout << "Error: Combination does not exist - code has been broken" << endl;
        return -100; // wont happen
    }
}
