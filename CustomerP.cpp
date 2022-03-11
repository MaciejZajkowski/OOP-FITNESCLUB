#include "header.h"
#include <iostream>
using namespace std;
CustomerP* CustomerP::GetPrevCustomerP(){
    CustomerP* x = previous;
    return x;
};
CustomerP* CustomerP::GetNextCustomerP(){
    return next;
};
Customer* CustomerP::getCustomer(){
    return customer;
};
SportEquipmentP* CustomerP::GetUsedEq(){
    return UsedEquipment;
};
void CustomerP:: ChangePrev_CP(CustomerP* C){
    this->previous = C;
};
void CustomerP:: ChangeNext_CP(CustomerP* C){
    this->next = C;
};
void CustomerP::PrintCustomer(){
    cout<<" Customers ID: " << getCustomer()->RefCustomerID()<< endl;
    cout<<" Used type : "<< getCustomer()->GetCustomerEq() << endl;
    cout<<" Used Equipment: " << GetUsedEq()->getEq()->getRealEqID() << endl;
    cout<<" Customers Budget: " <<getCustomer()->RefCustomerBudget() << endl;
    cout<<" Customers Name: " <<getCustomer()->GetCustomerName()<<endl<<endl;
};
void CustomerP::ChangeUsedEq(SportEquipmentP* E){
    this->UsedEquipment = E;
};
void CustomerP::ChangeCustomer(Customer* c){
this->customer = c;
};
