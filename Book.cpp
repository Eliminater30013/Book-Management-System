
#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include <sstream>
#include "Book.h"

using namespace std;
/*Default constructor*/
Book::Book()// default values given when a book is created
{
	id = 0;
	category = "VOID";
	name = "NONAME";
	description = "NO DESCRIPTION";
	publisher = "NO PUBLISHER";
	releaseDate = "UNRELEASED";
	author = "NO AUTHOR";

	price = 0.0;
	quantity = 0;
	rating = 0.0;
	review = "THIS BOOK WAS SO GOOD I WISH IT EXISTED!";
	//numberofBooks++;
}
/*Parameterised constructor*/
Book::Book(int id, string category, string name, string description, string publisher, string releaseDate, string author, float price, int quantity, float rating, string review)
{
	this->id = id;
	this->category = category;
	this->name = name;
	this->description = description;
	this->publisher = publisher;
	this->releaseDate = releaseDate;
	this->author = author;
	this->price = price;
	this->quantity = quantity;
	this->rating = rating;
	this->review = review;
	//numberofBooks++;
}
/*Destructor*/
Book::~Book()
{
	//numberofBooks--;// reduce the number of books since the book has been destroyed
}
/*Copy Constructor*/
Book::Book(const Book& book2)
{
	id = book2.id;
	category = book2.category;
	name = book2.name;
	description = book2.description;
	publisher = book2.publisher;
	releaseDate = book2.releaseDate;
	author = book2.author;
	price = book2.price;
	quantity = book2.quantity;
	rating = book2.rating;
	review = book2.review;
	//numberofBooks++;
}
/*Assignment operator*/
const Book Book::operator=(const Book& book2)
{
	if (this != &book2)
	{
		id = book2.id;
		category = book2.category;
		name = book2.name;
		description = book2.description;
		publisher = book2.publisher;
		releaseDate = book2.releaseDate;
		author = book2.author;
		price = book2.price;
		quantity = book2.quantity;
		rating = book2.rating;
		review = book2.review;
	}
	return *this;
}
ostream& operator<<(ostream &output, const Book &book2) // allows us to write to files easily
{
	output << book2.id << "," << book2.category << "," << book2.name << ",\"" << book2.description
		<< "\"," << book2.publisher << "," << book2.releaseDate << "," << book2.author << ","
		<< book2.price << "," << book2.quantity << "," << book2.rating << ",\"" << book2.review << "\"";
	return output;
}
/*Statics*/
//int Book::numberofBooks = 0;
/*Gets*/
int Book::getId() 
{ 
	return id; 
}

string Book::getCategory() 
{ 
	return category; 
}

string Book::getName() 
{
	return name; 
}

string Book::getDescription() 
{ 
	return description; 
}

string Book::getPublisher() 
{ 
	return publisher; 
}

string Book::getReleaseDate() 
{ 
	return releaseDate; 
}

string Book::getAuthor() 
{ 
	return author; 
}

float Book::getPrice() 
{ 
	return price;
}

int Book::getQuantity() 
{ 
	return quantity; 
}

float Book::getRating() 
{ 
	return rating;
}

string Book::getReview() 
{
	return review; 
}

int Book::getNumberOfBooks()
{
	int number_of_lines = 0;
	string line;
	ifstream myfile("Books.txt");
	while (std::getline(myfile, line))
		++number_of_lines;
	myfile.close();
	return number_of_lines;
}

//int Book::getNumberofBooks() 
//{
//	return numberofBooks;
//}
/*Sets*/
void Book::setId(int id)
{
	this->id = id;
}

void Book::setCategory(string category)
{
	this->category = category;
}

void Book::setName(string name)
{
	this->name = name;
}

void Book::setDescription(string description)
{
	this->description = description;
}

void Book::setPublisher(string publisher)
{
	this->publisher = publisher;
}

void Book::setReleaseDate(string releaseDate)
{
	this->releaseDate = releaseDate;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

void Book::setPrice(float price)
{
	this->price = price;
}

void Book::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Book::setRating(float rating)
{
	this->rating = rating;
}

void Book::setReview(string review)
{
	this->review = review;
}
/*Methods*/
void Book::BTEC_print()
{
	cout << "Information:\nID: " << id << "\nCategory: "<< category << "\nName: " << name 
	<< "\nDescription: " << description << "\nPublisher: " << publisher << "\nReleaseDate: " 
	<< releaseDate << "\nAuthor: " << author << "\nPrice: $"<< price 
	<< "\nQuantity: " << quantity << "\nRating: " << rating << "\nReview: " << review <<"\n"<< endl;
}

void Book::SetAll(int id, string category, string name, string description, string publisher, string releaseDate, string author, float price, int quantity, float rating, string review)
{
	this->id = id;
	this->category = category;
	this->name = name;
	this->description = description;
	this->publisher = publisher;
	this->releaseDate = releaseDate;
	this->author = author;
	this->price = price;
	this->quantity = quantity;
	this->rating = rating;
	this->review = review;
}
