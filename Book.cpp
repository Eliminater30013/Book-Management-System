#include <iomanip> // for quoted
#include "Book.h" // get all other files from .h file

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
vector<vector<string>> LoadBooks()
{
	/*  Read in a text file that has Books
		If the text file exists append books to it else make a new file, the file name will be Books*/
	ifstream readFromFile("Books.txt", std::ios_base::in);
	vector<vector<string>> error{ {"Books.txt file was not found"} };
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

vector<Book> LoadsBooks_BookVector(vector<vector<string>>& BookVector)
{
	vector<Book> BooksfromFile(1);
	if (BookVector.empty()) return BooksfromFile;
	BooksfromFile.resize(BookVector.size());
	for (unsigned int i = 0; i < BookVector.size(); i++) // Loop through a string 2D Vector and set all the Books within the booksfromFile vector
	{
		BooksfromFile[i].setId(atoi(BookVector[i][0].c_str())); // first convert the id from string to int, then set the id
		BooksfromFile[i].setCategory(BookVector[i][1]);// set the category of the book
		BooksfromFile[i].setName(BookVector[i][2]); // set the name of the book
		BooksfromFile[i].setDescription(BookVector[i][3]);// set the description HAS SPEECH MARKS
		BooksfromFile[i].setPublisher(BookVector[i][4]); // set publisher
		BooksfromFile[i].setReleaseDate(BookVector[i][5]); // set release date
		BooksfromFile[i].setAuthor(BookVector[i][6]); // set authour
		BooksfromFile[i].setPrice((float)atof(BookVector[i][7].c_str())); // set Price
		BooksfromFile[i].setQuantity(atoi(BookVector[i][8].c_str())); // set quantity
		BooksfromFile[i].setRating((float)atof(BookVector[i][9].c_str())); // sets the rating
		BooksfromFile[i].setReview(BookVector[i][10]); // set a review HAS SPEECH MARKS
		//BooksfromFile[i].BTEC_print(); // Once everything had been set Print out the Books Info
	}
	return BooksfromFile;
}

vector<Book> LoadBooksQuickly()
{
	vector<vector<string>> books2d = LoadBooks();
	vector<Book> books = LoadsBooks_BookVector(books2d);
	//cout << books[0].getNumberOfBooks() << endl;
	return books;
}
void AppendtoBookFile(Book& aBook)
{
	ofstream writeToFile("Books.txt", std::ios_base::app);
	writeToFile << "\n" << aBook;
}
void RewriteBookFile(vector<Book>& Books)
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
void Printout_BookVector(vector<Book>& BookVector)
{
	for (unsigned int i = 0; i < BookVector.size(); i++)
	{
		cout << "Book " << i + 1 << " in Catalogue\n";
		BookVector[i].BTEC_print();
	}
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

/*Book one;
	one.BTEC_print();
	one.SetAll(1, "Horror", "Mom's basement", "A story about how a fat man somehow defeated his worst nemesis", "Pelican Foundation",
		"01/12/2003", "James Patterson", 2.99, 20, 4.5, " I loved this book, it was sso interesting to see how Weebs live and go about their day to day life");
	one.BTEC_print();
	*/