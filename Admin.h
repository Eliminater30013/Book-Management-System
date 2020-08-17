#pragma once
#include <string>
class Admin {
private:
	int maxQuantity;
	int maxBudget;
	int totalBudget;
	int totalQuantity;
public:
	/*Constructors & Destructor*/
	Admin();
	Admin(int M_Q, int M_B, int T_B, int T_Q);
	~Admin();
	/*getters & setters*/
	int getMaxQuantity() { return maxQuantity; }
	int getMaxBudget() { return maxBudget; }
	int getTotalBudget() { return totalBudget; }
	int getTotalQuantity() { return totalQuantity; }
	void setMaxQuantity(int M_quantity) { maxQuantity = M_quantity; }
	void setMaxBudget(int M_budget) { maxBudget = M_budget; }
	void setTotalBudget(int T_budget) { totalBudget = T_budget; }
	void setTotalQuantity(int T_quantity) { totalQuantity = T_quantity; }
	void setall(int M_Q, int M_B, int T_B, int T_Q);
};
void AdminInterface(std::string user);
///////////////////////////Manage Staff Logins///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
int DeleteStaff(std::string staff);

int ResetPassword(std::string staff, std::string newPassword);

int AddStaff(std::string staff, std::string password);

void ShowStaffDetails();
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void CheckBudget_and_Quantity();

bool file_exists(std::string& name);