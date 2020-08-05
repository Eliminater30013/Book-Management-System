#include <vector>
#include <fstream>
#include <sstream>
#include "ErrorChecking.h" // get other file dependencies from this .h file
using namespace std;



// Overload function that allows us to check if integer has been entered
istream& getline(istream& ins, int& n)
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
    else if (readFromFile.is_open() && (option == '2' || option == 2)) // if the file can be opened
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
    if (itExists == 0 && (option == '1' || option == 1))
        return 1; // Admin success
    else if (itExists == 0 && (option == '2' || option == 2))
        return 2; // Staff sucess
    else if (itExists == 1 && (option == '1' || option == 1))
        return -1; // Admin failure
    else if (itExists == 1 && (option == '2' || option == 2))
        return -2; // Staff Failure
    else if (itExists == -1 && (option == '1' || option == 1))
        return -3; // Admin wrong password
    else if (itExists == -1 && (option == '2' || option == 2))
        return -4; // Staff wrong password
    else
    {
        cout << "Error: Combination does not exist - code has been broken" << endl;
        return -100; // wont happen
    }
}
