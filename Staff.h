#pragma once
#include <map>
#include <string>
using namespace std;
/*Function Declarations*/
map<int, string> GetCategoriesofBooks();
vector<int> getNumberOfBooks();
void StaffInterface(string& user);
void SearchBookInterface();
void AddBooksInterface();
void DeleteBooksInterface();
void UpdateBooksInterface();
void DisplayBooksInterface();

bool checkAlpha(string& str);
bool Correct_format_Date(string& date);

bool inDictionary(string& str, map<int, string>& dict);
void PrintMap(map<int, string>& dict, bool withKey=true);

