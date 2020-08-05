#pragma once
#include <iostream>
#include <string>
using namespace std;
/*Function Declarations*/
int CheckUsername(string username, string password, char option); // 0 success, 1 failure, -1 wrong password [option = 1 = staff]
istream& getline(istream& ins, int& n);

