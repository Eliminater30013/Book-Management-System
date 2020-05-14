#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
class Book
{
private:
	/*Every Book has these basic properties*/
	int id; // each book will have their own unique id which allows them to easily be sorted
	string category; // category is basically the themes of the book e.g. romance, horror action etc
	string name; // self-explanatory
	string description; // just a nice description of the book - preferably 3 sentences long next to a rating
	string publisher; // the people who sponsored the author ie Bloomsbury for Harry Potter
	string releaseDate; // in the form of dd/mm/year
	string author; // first + last name
	// for a book shop
	float price; // in £pounds
	int quantity;// ie 100 books of Eragon
	float rating;// usually out of 5 // star review here GRAPHICS // to 1 dp
	string review; // nice comment on if they enjoyed the book
	// enums
	//static int numberofBooks; // self-explanatory
public:
	/*Rule of 3 + operators*/
	Book();// default constructor
	Book(int id, string category, string name, string description, string publisher, string releaseDate,string author, float price, int quantity, float rating, string review);// parameterised constructor
	~Book();// destructor for management of data //not really required
	Book(const Book& book2); // copy constructor // not really required
	const Book operator= (const Book& book2); // assignment operator // not really required
	friend ostream &operator<< (ostream &output, const Book &book2);
	/*Gets*/
	int getId();
	string getCategory();
	string getName(); 
	string getDescription(); 
	string getPublisher(); 
	string getReleaseDate(); 
	string getAuthor(); 
	float getPrice();
	int getQuantity(); 
	float getRating(); 
	string getReview(); 
	//static int getNumberofBooks();
	int getNumberOfBooks();
	/*Sets*/
	void setId(int id);
	void setCategory(string category);
	void setName(string name);
	void setDescription(string description);
	void setPublisher(string publisher);
	void setReleaseDate(string releaseDate);
	void setAuthor(string author);
	void setPrice(float price);
	void setQuantity(int quantity);
	void setRating(float rating);
	void setReview(string review);
	/*Methods*/
	void BTEC_print();
	void SetAll(int id, string category, string name, string description, string publisher, string releaseDate, string author, float price, int quantity, float rating, string review);

};