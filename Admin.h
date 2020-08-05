#pragma once
#include <string>
/*Function Declarations*/

void AdminInterface();

int DeleteStaff(std::string staff);

int ResetPassword(std::string staff, std::string newPassword);

int AddStaff(std::string staff, std::string password);

void ShowStaffDetails();

