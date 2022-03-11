#include "header.h"
#include <iostream>
using namespace std;
FitnessClub::FitnessClub(int Budget, int price1, int price2){
this->FirstShift = new Shift(1, price1);
this->SecondShift = new Shift(2, price2);
this->Budget = Budget;
this->NumberOfCustomers = 0;
this->NumberOfEmployyes = 0;
this->headEq = nullptr;
};
bool FitnessClub::IS_EMPLOYEE(int ID){
    if(GetShift(1)->isEmployee(ID) || GetShift(2)->isEmployee(ID))
        return true;
    return false;
};
bool FitnessClub::HireEmployee(int ShiftNoumber, int ID, string n, int wage){
    if (wage <= 0)
        return false;
    if(!GetShift(1)||!GetShift(2))
        return false;
    if (IS_EMPLOYEE(ID))
        return false;
    if ((ShiftNoumber != 1 && ShiftNoumber != 2))
        return false;
    if(RefClubBudget() < wage)
        return false;
    RefClubBudget() = RefClubBudget() - wage;
    RefNumOfEmployees() = RefNumOfEmployees() + 1;
    Employee* employee = new Employee(ID, n, wage);
    if (GetShift(ShiftNoumber)->Hire_Employee(employee)){
        return true;
    }
    else
        return false;
};
bool FitnessClub:: SellMembership(int CarnetType, int ID, string Name, int ID_Of_Preferable_Equipment_type, int CustomerBudget){
   if (CustomerBudget <= 0)
        return false;
    if ((CarnetType != 1 && CarnetType != 2))
        return false;
    if(!GetShift(1)||!GetShift(2))
        return false;
    if(!IsNotOccupiedEq(ID_Of_Preferable_Equipment_type,CarnetType))
         return false;
    if(GetShift(CarnetType)->isCustomer(ID) || GetShift(diffrent_shift(CarnetType))->isCustomer(ID))
        return false;
    if(GetShift(CarnetType)->RefCarnetPrice() > CustomerBudget)
        return false;
    if(!GetShift(CarnetType)->CheckRatio()){
            int x = diffrent_shift(CarnetType);
            if(GetShift(x) && GetShift(x)->Check_Changed_Ratio()){
                CarnetType = x;
                ChangeShiftR(CarnetType);
            }
            else{
                return false;
            }
    }
    CustomerBudget = CustomerBudget - GetShift(CarnetType)->RefCarnetPrice();
    Customer* c = new Customer(ID, Name,ID_Of_Preferable_Equipment_type,CustomerBudget);
    if (GetShift(CarnetType)->PutCustomer(c)){
        if(!deletePointers() || !setpointers())
            return false;
        RefNumOfCustomers() = RefNumOfCustomers() + 1;
        return (true && CheckWorkingConditions());
    }
    else
        return false;
};
bool FitnessClub::setpointers(){
    int x = 1;
    CustomerP* current = nullptr;
    SportEquipmentP* EQ = nullptr;
    while(x <3){
        current = GetShift(x)->GetHeadC();
        while(current){
            if(!current->getCustomer())
                return false;
            EQ = Find_EQ_Type(current->getCustomer()->GetCustomerEq());
            if(!EQ || !EQ->getEq())
                return false;
            while(EQ->getEq()->GetEqCapacity() == EQ->getEq()->RefOccupancy(x)){
                EQ = EQ->GetNextEqOfType();
            }
            current->ChangeUsedEq(EQ);
            if(EQ->getEq())
                EQ->getEq()->RefOccupancy(x) = EQ->getEq()->RefOccupancy(x) +1;
            current = current->GetNextCustomerP();
        }
        x = x+1;
    }
    return true;
};
bool FitnessClub::ExpandContract(int CustomerID){
    if(!GetShift(1)||!GetShift(2))
        return false;
    int x;
    x = Find_C_Shift(CustomerID);
    Customer* c = Find_Customer(CustomerID);
    if(!c)
     return false;
    int y = diffrent_shift(x);
    if(!GetShift(y) || GetShift(y)->RefCarnetPrice() > c->RefCustomerBudget())
        return false;
    if(!IsNotOccupiedEq(c->GetCustomerEq(),y))
         return false;
    if(!GetShift(y)->CheckRatio()){
        if(GetShift(x)->Check_Changed_Ratio()){
            ChangeShiftR(y);
            }
        else{
            return false;
            }
    }
    c->RefCustomerBudget() = c->RefCustomerBudget() - GetShift(x)->RefCarnetPrice();
    RefClubBudget() = RefClubBudget() + GetShift(x)->RefCarnetPrice();
    if (GetShift(x)->PutCustomer(c)){
        if(!deletePointers() || !setpointers())
            return false;

        return true;
    }
    else
        return false;
};
int FitnessClub::Find_C_Shift(int ID){
    int x = 1;
    if(GetShift(x)->isCustomer(ID))
        return 1;
    x= x+1;
    if(GetShift(x)->isCustomer(ID))
        return 2;
    else
        return 0;
};
int FitnessClub::Find_E_Shift(int ID){
    int x = 1;
    if(GetShift(x)->isEmployee(ID))
        return 1;
    x= x+1;
    if(GetShift(x)->isEmployee(ID))
        return 2;
    return 0;
};
int FitnessClub::diffrent_shift(int x){
    if(x == 1)
        return 2;
    else if(x == 2)
        return 1;
    else
        return 0;
};
int FitnessClub:: SumWages(){
 int x = GetShift(1)->Sum_Wages() + GetShift(2)->Sum_Wages();
 return x;
};
bool FitnessClub::BuyEquipment(int TypeID, int Real_ID, int Capacity, int price){
    if(!GetShift(1)||!GetShift(2))
        return false;
    if (price <= 0)
        return false;
    if(Real_ID <= 0)
        return false;
    if(IsEquipment(Real_ID))
        return false;
    if (price > RefClubBudget())
        return false;
    RefClubBudget() = RefClubBudget() - price;
    SportEquipment* Eq = new SportEquipment(TypeID,Real_ID,Capacity,price);
    SportEquipmentP* EqP = new SportEquipmentP(Eq);
    if(!headEq){
        headEq = EqP;
        return true;
    }
    SportEquipmentP* current = headEq;
    while(current){
        if(current->GetNextEq() == nullptr){
            current->ChangeNext_EQ(EqP);
            EqP->ChangePrev_EQ(current);
            break;
        }
        else
            current = current->GetNextEq();
    }
    if(IS_TYPE_EQ(TypeID, Real_ID)){
        current = Find_EQ_Type(TypeID);
        while(current){
            if(current->GetNextEqOfType())
                current = current->GetNextEqOfType();
            else{
                    current->ChangeNext_Type_EQ(EqP);
                    EqP->ChangePrev_Type_EQ(current);
                    break;
            }
        }
    }
    return true;
};
int FitnessClub::HowManyEq(){
    SportEquipmentP* curr = headEq;
    int q = 0;
    while(curr){
        if(curr->GetNextEq()){
            curr = curr->GetNextEq();
            q = q+1;
        }
        else{
            q =q+1;
            return q;
        }
    }
    return q;
};
bool FitnessClub::IsEquipment(int RealID){
    SportEquipmentP* current = headEq;
    while(current){
        if(current->getEq())
            if(current->getEq()->getRealEqID()==RealID)
                return true;
        if(current->GetNextEq())
            current = current->GetNextEq();
        else
            return false;
    }
    return false;
};
bool FitnessClub::IS_TYPE_EQ(int TypeID , int ExcludedID){
    SportEquipmentP* current = headEq;
    while(current){
        if(current->getEq())
            if(current->getEq()->getTypeID() == TypeID && current->getEq()->getRealEqID() != ExcludedID)
                return true;
        current = current->GetNextEq();
    }
    return false;
};
int FitnessClub::getNumberOfCustomers(){
    return NumberOfCustomers;
 };
int FitnessClub::getNumberOfEmployes(){
    return NumberOfEmployyes;
};
int& FitnessClub::RefClubBudget(){
    int& x = Budget;
    return x;
};
bool FitnessClub::SellEquipment(int ID){
    if(!IsEquipment(ID))
        return false;
    SportEquipmentP* Eq = FindEq(ID);
    if(Eq->getEq()->RefOccupancy(1) != 0 || Eq->getEq()->RefOccupancy(2) != 0)
        return false;
    SportEquipmentP* Temp = nullptr;
    if(Eq->GetNextEq()){
        Temp = Eq->GetPrevEq();
        Eq->GetNextEq()->ChangePrev_EQ(Temp);
    }
    if(Eq->GetPrevEq()){
        Temp = Eq->GetNextEq();
        Eq->GetPrevEq()->ChangeNext_EQ(Temp); // check pointers
    }
    if(Eq->GetNextEqOfType()){
        Temp = Eq->GetPrevEqOfType();
        Eq->GetNextEqOfType()->ChangePrev_Type_EQ(Temp);
    }
    if(Eq->GetPrevEqOfType()){
        Temp = Eq->GetNextEqOfType();
        Eq->GetPrevEqOfType()->ChangeNext_Type_EQ(Temp); // check pointers
    }
    if(headEq == Eq)
        headEq = Eq->GetNextEq();
    RefClubBudget() = RefClubBudget() + Eq->getEq()->GetPrice();
    delete Eq->getEq();
    Eq->ChangeNext_EQ(nullptr);
    Eq->ChangePrev_EQ(nullptr);
    Eq->ChangeNext_Type_EQ(nullptr);
    Eq->ChangePrev_Type_EQ(nullptr);
    delete Eq;
    return true;
};
SportEquipmentP* FitnessClub::FindEq(int ID){
    SportEquipmentP* current = headEq;
    if(!IsEquipment(ID))
        return nullptr;
    while(current){
        if(current->getEq()->getRealEqID())
            if(current->getEq()->getRealEqID()==ID)
                return current;
        if(current->GetNextEq())
            current = current->GetNextEq();
        else
            return nullptr;
    }
    return current;
};
bool FitnessClub::ChangeWage(int ID, int wage){
    if(!GetShift(1)||!GetShift(2))
        return false;
    if(!IS_EMPLOYEE(ID))
        return false;
    if(GetShift(Find_E_Shift(ID))->FindEmployee(ID)->getEmployee() && RefClubBudget() >= (wage > GetShift(Find_E_Shift(ID))->FindEmployee(ID)->getEmployee()->RefWage())){
    GetShift(Find_E_Shift(ID))->FindEmployee(ID)->getEmployee()->RefWage() = wage;
    return (true && CheckWorkingConditions());
    }
    return false;
};
bool FitnessClub::ChangeShiftR(int num){
    if(!GetShift(1)||!GetShift(2))
        return false;
    int x = diffrent_shift(num);
    if(x != 2 && x!= 1)
        return false;
    bool flag = true;
    flag = flag && GetShift(x)->Hire_Employee(GetShift(num)->GetLastE()->getEmployee());
    flag = flag && GetShift(num)->Fire_Employee(GetShift(num)->GetLastE()->getEmployee()->RefEmployeeID());
    if (flag)
        return (true && CheckWorkingConditions());
    else
        return false;
};
bool FitnessClub::ChangeShift(int ID){
    if(!GetShift(1)||!GetShift(2))
        return false;
    if(!IS_EMPLOYEE(ID))
        return false;
    int num = Find_E_Shift(ID);
    if(!GetShift(num)->Check_Changed_Ratio())
        return false;
    int x = diffrent_shift(num);
    bool flag = true;
    flag = flag && GetShift(x)->Hire_Employee(GetShift(num)->FindEmployee(ID)->getEmployee());
    flag = flag && GetShift(num)->Fire_Employee(GetShift(num)->FindEmployee(ID)->getEmployee()->RefEmployeeID());
    if (flag)
        return (true && CheckWorkingConditions());
    return false;
};
bool FitnessClub::deletePointers(){
    if(!GetShift(1)||!GetShift(2))
        return false;
    if(GetShift(1)->deleteptr() && GetShift(2)->deleteptr())
        return true;
    else
        return false;
};
bool FitnessClub::UsersOfEq(int ID){
    if(!GetShift(1)||!GetShift(2))
        return false;
    SportEquipmentP* EQ = FindEq(ID);
    EQ->PrintEquipment();
     cout << "users of EQ with ID : " << ID << endl;
     CustomerP* current = nullptr;
     int x = 1;
     while(x < 3){
        cout <<"Shift " << x << endl;
        current = GetShift(x)->GetHeadC();
        while(current){
            if(current->GetUsedEq() && current->GetUsedEq()->getEq() && current->GetUsedEq()->getEq()->getRealEqID() == ID)
                current->PrintCustomer();
            current = current->GetNextCustomerP();
        }
        x++;
    }
    return true;
};
Customer* FitnessClub::Find_Customer(int ID){
    if(GetShift(1)->isCustomer(ID)){
        return GetShift(1)->FindCustomer(ID)->getCustomer();
    }
    else if(GetShift(2)->isCustomer(ID))
         return GetShift(1)->FindCustomer(ID)->getCustomer();
    else
        return nullptr;
};
int& FitnessClub::RefNumOfCustomers(){
    int& x = NumberOfCustomers;
    return x;
};
int& FitnessClub::RefNumOfEmployees(){
    int& x = NumberOfEmployyes;
    return x;
};
bool FitnessClub::CheckWorkingConditions(){
    if(!GetShift(1)||!GetShift(2))
        return false;
    EmployeeP* current = GetShift(1)->GetHeadE();
    while(current){
        if(!current->getEmployee())
            return false;
        if(GetShift(2)->isEmployee(current->getEmployee()->RefEmployeeID()))
            return false;
        current = current->GetNextEmployee();
    }
    return true;
};
bool FitnessClub::PrintClub(){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    bool flag = true;
    cout<< endl<<"Number of Customers: "<< RefNumOfCustomers()<<" Number of Employees: " << RefNumOfEmployees();
    cout<<" Number of Sport Equipment: " << HowManyEq()<< endl;
    cout<<" Club's Budget: " << RefClubBudget() << endl;
    cout << endl<< " Employees working in 1 Shift: " << GetShift(1)->HowManyEmployees() <<", Number of Carnets: "<< GetShift(1)->howMannyCustomers()<< endl;
    cout << " Employees working in 2 Shift: " << GetShift(2)->HowManyEmployees()<<", Number of Carnets: "<< GetShift(2)->howMannyCustomers() << endl << endl << endl;
    cout<<" Customers of Our Club: "<< endl;
    flag = flag && PrintCustomers();
    cout<<" Employees of Our Club: "<< endl;
    flag = flag && PrintEmployees();
    cout<<" Equipment of Our Club: "<< endl;
    flag = flag && PrintEquipment();
    if(flag)
        return true;
    else
        return false;
};
bool FitnessClub::PrintCustomers(){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    int x =1;
    CustomerP* current = nullptr;

    while(x < 3){
        current = GetShift(x)->GetHeadC();
        cout<<" "<< x << " Carnet Type:"<< endl;
        if(!current)
            cout<<" None"<< endl;
        while(current){

        current->PrintCustomer();
        current = current->GetNextCustomerP();
        }
        x++;
    }
    return true;
};
bool FitnessClub::PrintEmployees(){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    int x =1;
    EmployeeP* current = nullptr;
    while(x < 3){
        current = GetShift(x)->GetHeadE();
        cout<< " "<< x << " Shift:"<< endl;
         if(!current)
            cout<<" None"<< endl;
        while(current){

        current->PrintEmployee();
        current = current->GetNextEmployee();
        }
        x++;
    }
    return true;
};
int FitnessClub::BudgetBalance(){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return 0;
    }
    int wages = SumWages();
    int x =1;
    int incomes = 0;
     while(x<3){
     incomes = incomes + (GetShift(x)->RefCarnetPrice() * GetShift(x)->howMannyCustomers());
     x = x+1;
     }
     x = incomes - wages;
     return x;
};
bool FitnessClub::swapEmployees(int ID1, int ID2){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    if(!IS_EMPLOYEE(ID1) || !IS_EMPLOYEE(ID2))
        return false;
    Employee* e1 = Find_Employee(ID1);
    Employee* e2 = Find_Employee(ID2);
    EmployeeP* E1 = nullptr;
    EmployeeP* E2 = nullptr;
    if(!e1 || !e2)
        return false;
    int x1 = Find_E_Shift(ID1);
    if(x1 == 0)
        return false;
    E1 = GetShift(x1)->FindEmployee(ID1);

    int x2 = Find_E_Shift(ID2);
    if(x2 == 0)
        return false;
    E2 = GetShift(x2)->FindEmployee(ID2);
    E1->changeEmpl(e2);
    E2->changeEmpl(e1);
    return true;
};
bool FitnessClub::DiagnoseClub(){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    cout<< "Not used EQ: "<< endl;
    SportEquipmentP* Eq = headEq;
    while(Eq){
        if(!Eq->getEq())
            return false;
        if(Eq->getEq()->RefOccupancy(1) == 0 && Eq->getEq()->RefOccupancy(2) == 0)
            Eq->PrintEquipment();
        Eq=Eq->GetNextEq();
    }
    cout<< "Number of Employees with nothing to do:"<< endl;
    int x = 1;
    int y = 0;
    while(x<3){
        int c = GetShift(x)->howMannyCustomers();
        int e = GetShift(x)->HowManyEmployees();
        while(y < e +1){
            if(((e * 5 - c) - (y *5)) > 0)
                y = y + 1;
            else{
                if(y == 0)
                    y = 1;
                cout<<"in " << x << " shift we have " << y -1 <<" employees with nothing to do" << endl;
                break;
            }
        }
    y = 0;
    x = x+1;
    }
    x = BudgetBalance();
    if(x < 0){
        cout<<" your club is not profitable! Get new Customers or fire Employees with nothing to do" << endl;
        return false;
    }
    return true;
};
Employee* FitnessClub::Find_Employee(int ID){
    if(GetShift(1)->isEmployee(ID))
        return GetShift(1)->FindEmployee(ID)->getEmployee();
    else if(GetShift(2)->isEmployee(ID))
         return GetShift(2)->FindEmployee(ID)->getEmployee();
    else
        return nullptr;
};
bool FitnessClub::EndContract(int ID){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    int x =1;
    int y = 0;
    deletePointers();
    while(x < 3){
        if(GetShift(x)->isCustomer(ID)){
            GetShift(x)->End_Membership(ID);
            y = 1;
        }
        x++;
    }
    if(y == 1){
        RefNumOfCustomers() = RefNumOfCustomers() - 1;
        setpointers();
        return true;
    }
    setpointers();
    return false;
};
bool FitnessClub::FireEmployee(int ID){
    if(!GetShift(1)||!GetShift(2)){
        cout<<"At lest one Shift is deconstructed"<< endl;
        return false;
    }
    if(!IS_EMPLOYEE(ID))
        return false;
    int S = Find_E_Shift(ID);
    if(!GetShift(S)->Check_Changed_Ratio())
        return false;
    RefClubBudget() = RefClubBudget() + Find_Employee(ID)->RefWage();
    if(GetShift(S)->Fire_Employee(ID)){
        RefNumOfEmployees() = RefNumOfEmployees() - 1;
        return true;
    };
    return false;
};
bool FitnessClub::IsNotOccupiedEq(int type, int num){
    if(!IS_TYPE_EQ(type, 0))
        return false;
    SportEquipmentP* EQ = Find_EQ_Type(type);
    while(EQ){
    if(EQ->getEq()->GetEqCapacity() > EQ->getEq()->RefOccupancy(num))
        return true;
    EQ = EQ->GetNextEqOfType();
    }
    return false;
};
bool FitnessClub::PrintEquipment(){
    SportEquipmentP* current = headEq;
    if(!headEq)
        cout<<"none"<< endl;
    while(current){
        current->PrintEquipment();
        current = current->GetNextEq();
    }
    return true;
};
Shift* FitnessClub::GetShift(int num){
    if (num == 1)
        return FirstShift;
    else if (num == 2)
        return SecondShift;
    else
        return nullptr;
};
SportEquipmentP* FitnessClub::Find_EQ_Type(int Type){
    if(!IS_TYPE_EQ(Type,0))
        return nullptr;
    SportEquipmentP* current = headEq;
    while(current){
        if(current->getEq()->getTypeID())
            if(current->getEq()->getTypeID() == Type)
                return current;
        current = current->GetNextEq();
    }
    return nullptr;
};
FitnessClub::~FitnessClub(){
    GetShift(1)->~Shift();
    GetShift(2)->~Shift();
    NumberOfCustomers = 0;
    NumberOfEmployyes = 0;
    Budget = 0;
    FirstShift =  nullptr;
    SecondShift =  nullptr;
    SportEquipmentP* Eq = headEq;
    while(Eq){
        headEq = Eq->GetNextEq();
        delete Eq->getEq();
        Eq->ChangeNext_EQ(nullptr);
        Eq->ChangePrev_EQ(nullptr);
        Eq->ChangeNext_Type_EQ(nullptr);
        Eq->ChangePrev_Type_EQ(nullptr);
        delete Eq;
        Eq = headEq;
    }
};
