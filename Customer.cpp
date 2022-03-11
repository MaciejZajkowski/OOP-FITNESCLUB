#include "header.h"
#include <iostream>
using namespace std;
Customer::Customer(int CustomerID, string Name, int IDEq, int CustomerBudget){
    this->CustomerID = CustomerID;
    this->CustomerName = Name;
    this-> ID_Of_Preferable_Equipment_type = IDEq;
    this->CustomerBudget = CustomerBudget;
};
CustomerP::CustomerP(Customer* C){
    this->customer = C;
    this->next = nullptr;
    this->previous = nullptr;
    this-> UsedEquipment = nullptr;
};
int Customer::GetCustomerEq(){
    return ID_Of_Preferable_Equipment_type;
};
string Customer::GetCustomerName(){
    return CustomerName;
};
int& Customer::RefCustomerBudget(){
    int& x = CustomerBudget;
    return x;
};
int& Customer::RefCustomerID(){
    int& x = CustomerID;
    return x;
};
