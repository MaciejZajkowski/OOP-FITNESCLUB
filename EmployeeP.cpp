#include "header.h"
#include <iostream>
using namespace std;
EmployeeP::EmployeeP(Employee* e){
    this-> next = nullptr;
    this->previous = nullptr;
    this->employee = e;
};
EmployeeP* EmployeeP::GetNextEmployee(){
    EmployeeP* x = next;
    return x;
};
EmployeeP* EmployeeP::GetPrevEmployee(){
    return previous;
};
Employee* EmployeeP::getEmployee(){
    return employee;
};
void EmployeeP::ChangePrev_EP(EmployeeP* E){
    this->previous = E;
};
void EmployeeP:: ChangeNext_EP(EmployeeP* E){
    this->next = E;
};
void EmployeeP::changeEmpl(Employee* e){
    this->employee = e;
};
void EmployeeP::PrintEmployee(){
    cout<<endl<<" Employee ID: " << getEmployee()->RefEmployeeID() << endl;
    cout<<" Wage : "<< getEmployee()->RefWage() << endl;
    cout<<" Name: " << getEmployee()->GetEmployeeName() << endl <<endl;
};
