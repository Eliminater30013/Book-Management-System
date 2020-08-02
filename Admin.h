#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include<fstream>
#include <sstream>
#include <cmath>
#include <conio.h>
#include "Book.h"
using namespace std;

/*Function Declarations*/

void AdminInterface();

int DeleteStaff(string staff);

int ResetPassword(string staff, string newPassword);

int AddStaff(string staff, string password);

void ShowStaffDetails();

