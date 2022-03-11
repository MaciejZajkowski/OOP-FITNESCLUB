#include "header.h"
#include <iostream>
using namespace std;
Employee::Employee(int ID, string n, int wage){
    this->EmployeeName = n;
    this->wage = wage;
    this-> employeeID = ID;
};
int& Employee::RefWage(){
    int& x = wage;
    return x;
};
int& Employee::RefEmployeeID(){
    int& x = employeeID;
    return x;
};
bool Employee::PutEmployeeName(string n){
    EmployeeName =  n;
    if(EmployeeName == n)
        return true;
    else
        return false;
};
string Employee::GetEmployeeName(){
    return EmployeeName;
};
