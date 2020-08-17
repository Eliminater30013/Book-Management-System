#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <map>
#include <algorithm>
#include "Book.h"
#include "Staff.h"
#include "ErrorChecking.h"
using namespace std;
//Dictionary for Categories of Books. 
map<int, string> CategoriesofBooks{
    {0, "ACTION"},
    {1, "ADVENTURE"},
    {2, "CLASSIC"},
    {3, "COMIC BOOK"},
    {4, "GRAPHIC NOVEL"},
    {5, "MYSTERY"},
    {6, "FANTASY"},
    {7, "HISTORICAL FICTION"},
    {8, "HISTORY"},
    {9, "HORROR"},
    {10, "LITERARY FICTION"}, // ADD A DO U MEAN LITERARY FICTION?
    {11, "ROMANCE"},
    {12, "SCI-FI"},
    {13, "SHORT STORIES"},
    {14, "THRILLER"},
    {15, "SUSPENSE"},
    {16, "BIOGRAPHY"},
    {17, "AUTOBIOGRAPHY"},
    {18, "COOKBOOK"},
    {19, "ESSAY"},
    {20, "POETRY"},
    {21, "SELF-HELP"},
    {22, "CRIME"}
};

map<int, string> GetCategoriesofBooks()
{
    return CategoriesofBooks;
}
// avr quantity, total quantity, money spent
vector<int> getNumberOfBooks() // later change this vector to have total per category rather than average number of books.
{
    vector <int> vec(3);
    vec[0] = int(CategoriesofBooks.size());
    vector<Book> books = LoadBooksQuickly();
    int output = 0, total = 0;
    for (int i = 0; i < books.size(); i++) {
        output += books[i].getQuantity();
        total += int(round(books[i].getPrice()));
    }
    vec[1] = output;
    vec[2] = total;
    return vec;
}
void StaffInterface(string& user)
{
    char option = ' ';
    string start = getDate_Time();
    while (option != '6')
    {
        cout << "What would you like to do?\n1. Add a Book\n2. Display Books\n3. Search Books\n4. Delete a Book\n5. Update Books\n"
            << "6. Return to Main Menu\nChoice: ";
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
            break;
        }
        else
        {
            cout << "Invalid Key pressed, Please try again!\n";
        }
    }
    string end = getDate_Time();
    ofstream LoginReport("LoginReport.txt", ios_base::app);
    LoginReport << "        Name: " << user << "\nStart time: " << start << "End time:   " << end;
    LoginReport.close();
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
            while (!inDictionary(category, CategoriesofBooks))
            {
                cout << "Invalid Category. Type \"_CATEGORIES_\" to get the available Categories.\nOr just enter a category: ";
                getline(cin, category);
                if (category == "_CATEGORIES_")
                {
                    map<int, string> cat = GetCategoriesofBooks();
                    PrintMap(cat);
                    cout << "Enter Category: ";
                    getline(cin, category);
                }
            }
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
            while (Name.length() < 3)
            {
                cout << "Name is too short. Name must be minimum 3 letters long.";
                getline(cin, Name);
            }
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
            while (Author.length() < 3)
            {
                cout << "Author's name is too short. Name must be minimum 3 letters long.";
                getline(cin, Author);
            }
            for (unsigned int i = 0; i < bookVector2D.size(); i++)
            {
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
            bookVector2D[*i].print();
            // write it out - new line for every book
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
    while (!inDictionary(category, CategoriesofBooks)) 
    {
        cout << "Invalid Category\nCategory: ";
        getline(cin, category);
    }
    cout << "Name: ";
    string name;
    getline(cin, name);
    while (name.length() < 3 && !checkAlpha(name))
    {
        cout << "Name is either too short (Name must be minimum 3 letters long)\nOr invalid(Please ensure that the letters in the name is between A-Z)\nName: ";
        getline(cin, name);
    }
    cout << "Description: ";
    string description;
    getline(cin, description);
    while (description.length() < 20)
    {
        cout << "Description is too short. Description must be minimum 20 letters long.\nDescription: ";
        getline(cin, description);
    }
    cout << "Publisher: ";
    string publisher;
    getline(cin, publisher);
    while (publisher.length() < 3)
    {
        cout << "Publisher's name is too short. Name must be minimum 3 letters long.\nPublisher: ";
        getline(cin, publisher);
    }
    cout << "ReleaseDate: ";
    string releaseDate;
    getline(cin, releaseDate);
    while (true) {
        try
        {
            Correct_format_Date(releaseDate);
            break;
        }
        catch (invalid_argument)
        {
            cout << "Please enter the release date in the format dd/mm/yyyy.\nReleaseDate: ";
            getline(cin, releaseDate);
        }
        catch (exception& e)
        {
            cout << e.what() << ".\nReleaseDate: ";
            getline(cin, releaseDate);
        }
    }
    cout << "Author: ";
    string author;
    getline(cin, author);
    while (author.length() < 3)
    {
        cout << "The name of the Author is too short. The name must be minimum 3 letters long.\nAuthor: ";
        getline(cin, author);
    }
    cout << "Price: ";
    string s_price;
    getline(cin, s_price); float price;
    while (true) {
        try {
            price = stof(s_price);
            if (price < 0) throw out_of_range("Price of books must be greater than or equal to 0");
            break;
        }
        catch (...)
        {
            cout << "Please enter a valid double!\nPrice: ";
            getline(cin, s_price);

        }
    }
    cout << "Quantity: ";
    int quantity = 0;
    while (!getline(cin, quantity) || quantity > 100) // Ensure not more than 100 quantity
    {
        cin.clear();
        cout << "Quantity: ";
    }
    cout << "Please enter a Rating out of 5: ";
    string s_rating;
    getline(cin, s_rating);
    float rating;
    while (true) {
        try {
            rating = stof(s_rating);
            if (rating < 0 || rating > 5) throw out_of_range("Out of Range! ");
            break;
        }
        catch (...)
        {
            cout << "Please enter a valid numerical rating.\nEnter a Rating out of 5: ";
            getline(cin, s_rating);
        }
    }
    cout << "Review: ";
    string review;
    getline(cin, review);
    while (review.length() < 20)
    {
        cout << "Review is too short. A review must be minimum 20 letters long.\nReview: ";
        getline(cin, review);
    }
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
        cout << "Try again, the ID number must be greater than 0 and smaller than or equal to " << Books[0].getNumberOfBooks() << ":";
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
            Books[*i].print();
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
    char option = ' ';
    vector<Book> Books;
    while (option != '0') {
        cout << "Update a book by:\n1. Rating \n2. Category\n3. Name\n4. Description"
            << "\n5. Publisher\n6. ReleaseDate \n7. Author"
            << "\n8. Price\n9. Review\n0. Return \nChoice: ";
        option = _getch();
        cout << option << "\n";
        while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5' && option != '6' && option != '7' && option != '8' && option != '9' && option != '0')
        {
            cout << "\nWrong Option entered Try again: ";
            option = _getch();
            cout << option << "\n";
        }
        Books = LoadBooksQuickly();
        int input_ID;
        char choice = ' ';
        do 
        {
            if (option == '0') break;
            cout << "Enter ID of Book you would like to update: ";
            while (!getline(cin, input_ID) || input_ID < 0 || input_ID >= Books[0].getNumberOfBooks()) // Check if greater than ID count! change 8 later
            {
                cin.clear();
                cout << "Invalid ID, Try again\nID: ";
            }
            Books[input_ID].print();
            cout << "Would you like to Update this Book? Press 'Y' for Yes and 'N' for No\nChoice: ";
            char choice = _getch();
            cout << choice << "\n";
            while (choice != 'Y' && choice != 'N' && choice != 'n' && choice != 'y')
            {
                cout << "Wrong Key pressed, Try again!\nChoice: ";
                choice = _getch();
                cout << choice << "\n";
            }
            if (choice == 'Y' || choice == 'y') break;
        } while (choice != 'n' && choice != 'N');
        if (option == '1')
        {
            cout << "New Rating: ";
            string s_rating;
            getline(cin, s_rating);
            float rating;
            while (true) {
                try {
                    rating = stof(s_rating);
                    if (rating < 0 || rating > 5) throw out_of_range("Out of Range! ");
                    break;
                }
                catch (...)
                {
                    cout << "Please enter a valid numerical rating.\nEnter a Rating out of 5: ";
                    getline(cin, s_rating);
                }
            }
            auto old = Books[input_ID].getRating();
            Books[input_ID].setRating(rating);
            cout << "The book with ID " << input_ID << " has had its rating changed from " << old << " to " << rating << endl;
        }
        else if (option == '2')
        {
            cout << "New Category: ";
            string category;
            getline(cin, category);
            while (!inDictionary(category, CategoriesofBooks))
            {
                cout << "Invalid Category\nCategory: ";
                getline(cin, category);
            }
            auto old = Books[input_ID].getCategory();
            Books[input_ID].setCategory(category);
            cout << "The book with ID " << input_ID << " has had its category changed from " << old << " to " << category << endl;
        }
        else if (option == '3')
        {
            cout << "New Name: ";
            string name;
            getline(cin, name);
            while (name.length() < 3 && !checkAlpha(name))
            {
                cout << "Name is either too short (Name must be minimum 3 letters long)\nOr invalid(Please ensure that the letters in the name is between A-Z)\nName: ";
                getline(cin, name);
            }
            auto old = Books[input_ID].getName();
            Books[input_ID].setName(name);
            cout << "The book with ID " << input_ID << " has had its name changed from " << old << " to " << name << endl;
        }
        else if (option == '4')
        {
            cout << " New Description: ";
            string description;
            getline(cin, description);
            while (description.length() < 20)
            {
                cout << "Description is too short. Description must be minimum 20 letters long.\nDescription: ";
                getline(cin, description);
            }
            auto old = Books[input_ID].getDescription();
            Books[input_ID].setDescription(description);
            cout << "The book with ID " << input_ID << " has had its description changed from " << old << " to " << description << endl;
        }
        else if (option == '5')
        {
            cout << " New Publisher: ";
            string publisher;
            getline(cin, publisher);
            while (publisher.length() < 3)
            {
                cout << "Publisher's name is too short. Name must be minimum 3 letters long.\nPublisher: ";
                getline(cin, publisher);
            }
            auto old = Books[input_ID].getPublisher();
            Books[input_ID].setPublisher(publisher);
            cout << "The book with ID " << input_ID << " has had its publisher changed from " << old << " to " << publisher << endl;
        }
        else if (option == '6')
        {
            cout << "New Release date: ";
            string releaseDate;
            getline(cin, releaseDate);
            while (true) {
                try
                {
                    Correct_format_Date(releaseDate);
                    break;
                }
                catch (invalid_argument)
                {
                    cout << "Please enter the release date in the format dd/mm/yyyy.\nReleaseDate: ";
                    getline(cin, releaseDate);
                }
                catch (exception& e)
                {
                    cout << e.what() << ".\nReleaseDate: ";
                    getline(cin, releaseDate);
                }
            }
            auto old = Books[input_ID].getReleaseDate();
            Books[input_ID].setReleaseDate(releaseDate);
            cout << "The book with ID " << input_ID << " has had its release date changed from " << old << " to " << releaseDate << endl;
        }
        else if (option == '7')
        {
            cout << "New Author: ";
            string author;
            getline(cin, author);
            while (author.length() < 3)
            {
                cout << "The name of the Author is too short. The name must be minimum 3 letters long.\nAuthor: ";
                getline(cin, author);
            }
            auto old = Books[input_ID].getAuthor();
            Books[input_ID].setAuthor(author);
            cout << "The book with ID " << input_ID << " has had its author changed from " << old << " to " << author << endl;
        }
        else if (option == '8')
        {
            cout << "New Price: ";
            string s_price;
            getline(cin, s_price); float price;
            while (true) {
                try {
                    price = stof(s_price);
                    if (price < 0) throw out_of_range("Price of books must be greater than or equal to 0");
                    break;
                }
                catch (...)
                {
                    cout << "Please enter a valid double!\nPrice: ";
                    getline(cin, s_price);

                }
            }
            auto old = Books[input_ID].getPrice();
            Books[input_ID].setPrice(price);
            cout << "The book with ID " << input_ID << " has had its price changed from " << old << " to " << price << endl;
        }
        else if (option == '9')
        {
            cout << "Review: ";
            string review;
            getline(cin, review);
            while (review.length() < 20)
            {
                cout << "Review is too short. A review must be minimum 20 letters long.\nReview: ";
                getline(cin, review);
            }
            auto old = Books[input_ID].getReview();
            Books[input_ID].setReview(review);
            cout << "The book with ID " << input_ID << " has had its review changed from " << old << " to " << review << endl;
        }
        /* This will only happen if we have updated at least one book therefore we will need to rewrite the book file
        Therefore we break instead of returning!*/
        else {
            cout << "Returning..." << endl;
            return;
        }
        RewriteBookFile(Books); // can be optimized by rewriting one book only to the file!
    }
}
void DisplayBooksInterface()
{
    vector<vector<string>> _2DVector = LoadBooks();
    vector<Book> books = LoadsBooks_BookVector(_2DVector);
    Printout_BookVector(books);
}

bool checkAlpha(string& str) {
    bool alpha = true;
    for (int i = 0; i < str.size(); i++)
        if (!isalpha(str[i])) {
            alpha = false;
        }
    return alpha;
}

bool inDictionary(string& str, map<int, string>& dict) 
{
    transform(str.begin(), str.end(), str.begin(), ::toupper); // ensures that it can be matched wih the dictionary
    bool found = false;
    for (auto it = CategoriesofBooks.begin(); it != CategoriesofBooks.end(); it++)
        if (it->second == str)
            found = true;
    return found;
}
bool Correct_format_Date(string& date) // improve this by ensuring that the days matches the months which matches the year e.g leap year!
{
    string parts; int i_parts, i = 0;
    stringstream ss(date);
    while (getline(ss, parts, '/')) 
    {
        i_parts = stoi(parts);
        if ((i_parts < 1 || i_parts > 31) && i == 0)
        {
            throw out_of_range("Days can only be between 1 and 31");
        }
        if ((i_parts < 1 || i_parts > 12) && i == 1)
        {
            throw out_of_range("Months can only be between 1 and 12");

        }
        if ((i_parts < 1800 || i_parts > 2020) && i == 2)
        {
            throw out_of_range("Please enter the year correctly e.g 2001 instead of 01");

        }
        i++;
    }
    if (date.length() != 10) throw length_error("Please enter the release date in the format dd/mm/yyyy");
    return true;
}
void PrintMap(map<int, string>& dict, bool withKey)
{
    for (auto y : dict)
    {
        if (withKey)
        {
            cout << y.first << ' ';
        }
        cout << y.second << "\n";
    }
}