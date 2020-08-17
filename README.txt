Copyright: Ahmed Osman

Use of this project is allowed, however please do not simply copy paste the entire project and claim it as your own!

This Text File contains my plan on making a book management system, my first personal large project to practise file handling, classes, overloading functions, functional programming, try-except + error handling, loops, vectors, maps all programmed in C++!

Book management system with Admin, Staff interface:

The Admin interface contain 3 options, with the first being able to manage staff logins - being able to delete staff, change their username and password, adding staff and checking staff details. The second option is being able to set budget and quantity of books, setting goals and checking how much money has already been spent on books. The last option is just a LoginReport that shows who logged in at what time, which is an option that was implemented to allow some security to the system. LoginReport.txt, Budget.txt and Existing Users.txt are both used by this interface

The Staff interface contained 5 simple functions, with the first option being able to add books (provided the relevant information is supplied (e.g. id, name, author, price etc...). The second option allowed books to be displayed in id-chronological order with correct formatting. The third option enabled books to be searched by id, name, author, and category(a dictionary/map was used to contain the allowed categories of books). The fourth option allowed the deletion of books by id only(which can be expanded on), with user being able to cancel the deletion by pressing N. Finally, books can be updated by name, author, id, review, rating etc... to allow staff members to change any mistakes they have previously made. Books.txt is used here.

A file for error checking exists (ErrorChecking.cpp) which contain functions that handle error conditions such as when an invalid integer is entered and checking that correct username + passwords have been entered. A date and time function also resides here which is used when a login report is created.

Finally a class file was created for the books in the book management system called Book. This interacts with the Books.txt file, a file which contains CSV with quote handling. The Book.h file contains comments explaining this further.

Temp.txt is used to allow quick deletion.

Project can be expanded and improved by including more error-checking, cleaner interface, a GUI or perhaps storing book data using sql?
