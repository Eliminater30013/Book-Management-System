#pragma once
#include <map>
/*Function Declarations*/
map<int, string> GetCategoriesofBooks();
void StaffInterface();
void SearchBookInterface();
void AddBooksInterface();
void DeleteBooksInterface();
void UpdateBooksInterface();
void DisplayBooksInterface();

bool checkAlpha(string& str);
bool Correct_format_Date(string& date);

bool inDictionary(string& str, map<int, string>& dict);
void PrintMap(map<int, string>& dict, bool withKey=true);

