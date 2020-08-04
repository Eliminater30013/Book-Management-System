#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <conio.h>
#include "Book.h"
using namespace std;

/*Function Declarations*/
void StaffInterface();
void SearchBookInterface();
void AddBooksInterface();
void DeleteBooksInterface();
void UpdateBooksInterface();
void DisplayBooksInterface();
int CheckUsername(string username, string password, char option); // 0 success, 1 failure, -1 wrong password [option = 1 = staff]
istream& getline(std::istream& ins, int& n);


