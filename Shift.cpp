#include "header.h"
#include <iostream>
using namespace std;
bool Shift::isCustomer(int ID){
    CustomerP* current = headC;
    if(!current)
        return false;
    while (current){
        if (current->getCustomer() && current->getCustomer()->RefCustomerID() == ID)
            return true;
        current = current->GetNextCustomerP();
    }
    return false;
};
CustomerP* Shift::FindCustomer(int ID){
    if (isCustomer(ID)){
        CustomerP* current = headC;
        while (current){
        if (current->getCustomer() && current->getCustomer()->RefCustomerID()== ID){
            return current;
        }
            current = current->GetNextCustomerP();
        }
    }
    return nullptr;
}
bool Shift::isEmployee(int ID){
    EmployeeP* current = headE;
    if(!current)
        return false;
    while (current){
        if (current ->getEmployee() && current->getEmployee()->RefEmployeeID() == ID)
            return true;
        current = current->GetNextEmployee();
    }
    return false;
};
EmployeeP* Shift::FindEmployee(int ID){
    if (isEmployee(ID) == true){
        EmployeeP* current = headE;
        while (current){
        if (current ->getEmployee() && current->getEmployee()->RefEmployeeID() == ID){
            return current;
        }
            current = current->GetNextEmployee();
        }
    }
    return nullptr;
};
int Shift::HowManyEmployees(){
    EmployeeP* current = headE;
    if(!current){
        return 0;
    };
    int q =0;
    while(current){
        q++;
    current = current->GetNextEmployee();
    }
    return q;

};
int Shift::howMannyCustomers(){
    CustomerP* current = headC;
    int q =0;
    if(!headC)
        return 0;
    while(current){
        q++;
    current = current->GetNextCustomerP();
    }
    return q;

};
bool Shift::PutCustomer(Customer* c){
    if(c->RefCustomerBudget() < RefCarnetPrice())
        return false;
    c->RefCustomerBudget() =  c->RefCustomerBudget() - RefCarnetPrice();
    CustomerP* Cus = new CustomerP(c);
    if(headC == nullptr){
        headC = Cus;
        return true;
    }
    else{
        Cus->ChangeNext_CP(headC);
        headC->ChangePrev_CP(Cus);
        headC = Cus;
    return true;
    }
};
bool Shift::Hire_Employee(Employee* e){
    EmployeeP* E = new EmployeeP(e);
    if(headE == nullptr){
        headE = E;
        return true;
    }
    else{
    E->ChangeNext_EP(headE);
    headE->ChangePrev_EP(E);
    headE = E;
    return true;
    }
};
bool Shift::Fire_Employee(int ID){
    EmployeeP* E = FindEmployee(ID);
    if(!E)
        return false;
    EmployeeP* Temp = nullptr;
    if(E->GetNextEmployee()){
        Temp = E->GetPrevEmployee();
        E->GetNextEmployee()->ChangePrev_EP(Temp);
    }
    if(E->GetPrevEmployee()){
        Temp = E->GetNextEmployee();
        E->GetPrevEmployee()->ChangeNext_EP(Temp);
    }
    if(E == headE)
        headE = E->GetNextEmployee();
    E->ChangeNext_EP(nullptr);
    E->ChangePrev_EP(nullptr);
    E->changeEmpl(nullptr);
    delete E;
    return true;
};
bool Shift::End_Membership(int ID){
    CustomerP* E = FindCustomer(ID);
    if(!E)
        return false;
    CustomerP* Temp = nullptr;
    if(E->GetNextCustomerP()){
            Temp = E->GetPrevCustomerP();
        E->GetNextCustomerP()->ChangePrev_CP(Temp);
    }
    if(E->GetPrevCustomerP()){
            Temp = E->GetNextCustomerP();
        E->GetPrevCustomerP()->ChangeNext_CP(Temp);
    }
    if(E == headC)
        headC = E->GetNextCustomerP();
    E->ChangeNext_CP(nullptr);
    E->ChangePrev_CP(nullptr);
    delete E->getCustomer();
    E->ChangeUsedEq(nullptr);
    delete E;
    return true;
};
int& Shift::RefCarnetPrice(){
    int& x = CarnetPrice;
    return x;
};
Shift::Shift(int n, int price){
this->CarnetPrice = price;
this->ShiftNumber = n;
this->headC = nullptr;
this->headE = nullptr;
};
int Shift::Sum_Wages(){
    EmployeeP* current = headE;
    int x = 0;
    while(current){
        if(current->getEmployee())
            x = x+ current->getEmployee()->RefWage();
        current = current->GetNextEmployee();
    }
    return x;
};
bool Shift::CheckRatio(){
    if(HowManyEmployees() == 0)
        return false;
    if((HowManyEmployees() *5)>= (howMannyCustomers() +1)){
        return true;
    }

    return false;
};
bool Shift::Check_Changed_Ratio(){
    if(HowManyEmployees() == 0)
        return false;
    else if(((HowManyEmployees() - 1 ) * 5 )>=howMannyCustomers())
        return true;
    else
        return false;
};
EmployeeP* Shift::GetLastE(){
    EmployeeP* curr = headE;
    while(curr){
        if(curr->GetNextEmployee()== nullptr)
            return curr;
        else
            curr = curr->GetNextEmployee();
    }
    return curr;
};
bool Shift::deleteptr(){
    CustomerP* curr = headC;
    SportEquipmentP* Eq = nullptr;
    while(curr){
        if(curr->GetUsedEq()){
            Eq = curr->GetUsedEq();
            Eq->getEq()->RefOccupancy(GetShiftNum()) = 0;
            curr->ChangeUsedEq(nullptr);
        }
        curr = curr->GetNextCustomerP();
    }
    return true;
};
CustomerP* Shift::GetHeadC(){
return headC;
};
EmployeeP* Shift::GetHeadE(){
return headE;
};
int Shift::GetShiftNum(){
    return ShiftNumber;
};
Shift::~Shift(){
    EmployeeP* E = headE;
    while(E){
        headE = E->GetNextEmployee();
        E->ChangeNext_EP(nullptr);
        E->ChangePrev_EP(nullptr);
        E->changeEmpl(nullptr);
        delete E;
        E = headE;
    }
    CustomerP* C = headC;
    while(C){
        headC = C->GetNextCustomerP();
        C->ChangeNext_CP(nullptr);
        C->ChangePrev_CP(nullptr);
        C-> ChangeCustomer(nullptr);
        C->ChangeUsedEq(nullptr);
        delete C;
        C = headC;
    }
};
