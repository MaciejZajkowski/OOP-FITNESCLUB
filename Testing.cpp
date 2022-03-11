#include <iostream>
#include "Testing.h"
#include "header.h"

using namespace std;
//Assumptions and restrictions = A&R
bool Test_1(){ // adding employee/customer adds new place in appropriate list
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
     Club->BuyEquipment(1,3,4,4);
     Club->HireEmployee(1,10,"adam",10);
     Club->SellMembership(1,1,"adam",1,300);
     if(Club->getNumberOfEmployes() == 1 && Club->getNumberOfCustomers() == 1 && Club->HowManyEq() == 1)
        return true;
    else
        return false;
};
bool Test_2(){ // Budget Balance returns right value
     FitnessClub* Club = new FitnessClub(1000, 50, 40);
     Club->BuyEquipment(1,3,4,4);
     Club->HireEmployee(1,10,"adam",10);
     Club->SellMembership(1,1,"adam",1,300);
     if(Club->BudgetBalance()== 40)
        return true;
     else
        return false;
};
bool Test_3(){ // diagnose club works properly
    FitnessClub* Club = new FitnessClub(1000, 5, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,10,"adam",10);
    Club->SellMembership(1,10,"adam",1,300);
    FitnessClub* Club2 = new FitnessClub(1000, 50, 40);
    Club2->BuyEquipment(1,3,4,4);
    Club2->HireEmployee(1,1,"adam",10);
    Club2->SellMembership(1,1,"adam",1,300);
    if(!Club->DiagnoseClub() && Club2->DiagnoseClub())
        return true;
    else
        return false;
};
bool Test_4(){//you can not sel membership if you have no right eq
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(2,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    if(!Club->SellMembership(1,1,"adam",1,300))
        return true;
    else
        return false;
};
bool Test_5(){//you cant fire employee that is working
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    if(!Club->FireEmployee(1))
        return true;
    else
        return false;
};
bool Test_6(){//you cant sell eq that is occupied
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    if(!Club->SellEquipment(1))
        return true;
    else
        return false;
};
bool Test_7(){ //you can not fire employee that doesn't exist
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    if(!Club->FireEmployee(2))
        return true;
    else
        return false;
};
bool Test_8(){ //you cannot add customer with ID that  already exist in the shift
FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    if(!Club->SellMembership(1,1,"adam",1,300))
        return true;
    else
        return false;
};
bool Test_9(){ //if you remove every element from club it is empty
FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    Club->EndContract(1);
    Club->FireEmployee(1);
    Club->SellEquipment(3);
    if(Club->HowManyEq() == 0  && Club->getNumberOfCustomers()==0&&Club->getNumberOfEmployes()==0)
        return true;
    else
        return false;
};
bool Test_10(){ // Swap employees work correctly ( doesn't swap employees that dos not exist and so on)
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->HireEmployee(2,2,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    Club->PrintEmployees();
    if(!Club->swapEmployees(8,2) && Club->swapEmployees(1,2)){
        return true;
    }
    else
        return false;
};
bool Test_11(){ // Checks if there is Change shift works properly
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    Club->SellMembership(1,2,"adam",1,300);
    Club->SellMembership(1,3,"adam",1,300);
    Club->HireEmployee(1,2,"adam",10);
    FitnessClub* Club2 = new FitnessClub(1000, 50, 40);
    Club2->BuyEquipment(1,3,4,4);
    Club2->HireEmployee(1,1,"adam",10);
    Club2->SellMembership(1,1,"adam",1,300);
    if(Club->ChangeShift(1)&& !Club2->ChangeShift(1))
        return true;
    else
        return false;
};
bool Test_12(){ // you can't sell membership before you hire employees or buy equipment
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    if(!Club->SellMembership(1,1,"adam",1,300))
        return true;
    else
        return false;
};
void Test_13(){ // you can print empty club
    cout<< endl<<"welcome in test number 13, we are testing if you can print empty club" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->PrintClub();
    cout<< endl;
};
void Test_14(){ // you can print empty Equipment list
     cout<< endl<<"welcome in test number 14, we are testing if you can print empty Equipment list" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->PrintEquipment();
    cout<< endl;
};
void Test_15(){ // you can print empty Customer list
    cout<< endl<<"welcome in test number 15, we are testing if you can print empty Customer list" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->PrintCustomers();
    cout<<endl;
};
void Test_16(){ // you can print empty Employee list
    cout<< endl<<"welcome in test number 16, we are testing if you can print empty Employees list" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->PrintEmployees();
    cout<< endl;
};
void Test_17(){ // you can print empty club that was previously full
    cout<< endl<<"welcome in test number 17, we are testing what happenes if you remove all elements of club and try to print it" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->BuyEquipment(1,1,4,1);
    Club->HireEmployee(1,1,"wojtek",90);
    Club->SellMembership(1,1,"ania",1,300);
    Club->EndContract(1);
    Club->SellEquipment(1);
    Club->FireEmployee(1);
    Club->PrintClub();
    cout<< endl;
};
void Test_18(){ // you can't print club after using destructor
    cout<< endl<<"welcome in test number 18, we are testing what happenes if you use destructor and try to print it" << endl;
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->BuyEquipment(1,1,4,1);
    Club->HireEmployee(1,2,"wojtek",90);
    Club->SellMembership(1,1,"ania",1,300);
    Club->~FitnessClub();
    Club->PrintClub();
    cout<< endl;
};
bool Restriction_1(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    return(Club->BuyEquipment(1,0,4,4));
};
bool Restriction_2(){
    bool flag = false;
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    if(!Club->SellMembership(1,3,"adam",1,300))
        flag =true;
    Club->BuyEquipment(1,3,4,4);
    Club->BuyEquipment(2,2,4,4);
    Club->HireEmployee(1,10,"adam",10);
    Club->HireEmployee(2,6,"adam",10);
    flag = (Club->SellMembership(1,1,"adam",1,300)&& Club->SellMembership(2,10,"adam",1,300));
    return flag;
};
bool Restriction_3(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->HireEmployee(1,10,"adam",10);
    Club->HireEmployee(2,10,"adam",10);
    return(Club->CheckWorkingConditions());
};
bool Restriction_4(){
    FitnessClub* Club = new FitnessClub(1000, 50, 20);
    Club->HireEmployee(1,1,"adam",10);
    Club->HireEmployee(2,6,"adam",10);
    Club->BuyEquipment(1,3,4,4);
    Club->BuyEquipment(1,4,4,4);
    Club->SellMembership(1,1,"adam",1,300);
    Club->SellMembership(2,2,"adam",1,60);
   // Club->PrintClub();
    return(Club->ExpandContract(1) /* &&!Club->ExpandContract(2)  */&& !Club->ExpandContract(4) );
};
bool Restriction_5(){
    FitnessClub* Club = new FitnessClub(10, 50, 40);
    return(!Club->HireEmployee(1,10,"adam",1000));
};
bool Restriction_6(){
    FitnessClub* Club = new FitnessClub(30, 50, 40);
    return(!Club->BuyEquipment(1,1,5,500));
};
bool Restriction_7(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->HireEmployee(1,10,"adam",10);
    Club->HireEmployee(2,6,"adam",10);
    Club->BuyEquipment(1,3,4,4);
    Club->SellMembership(1,1,"adam",1,300);
    return(!Club->SellMembership(2,1,"adam",1,60));
};
bool Restriction_8(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->HireEmployee(1,10,"adam",10);
    return(!Club->HireEmployee(1,10,"adam",10));
};
bool Restriction_9(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->HireEmployee(1,1,"adam",10);
    Club->HireEmployee(1,2,"adam",10);
    return(Club->swapEmployees(1,2) && !Club->swapEmployees(5,4));
};
bool Restriction_10(){
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    if(!Club->SellMembership(1,1,"adam",1,300))
        return true;
    else
        return false;
};
bool Restriction_11(){
    FitnessClub* Club = new FitnessClub(1000, 500, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    if(!Club->SellMembership(4,1,"adam",1,300))
        return true;
    else
        return false;
};
bool Restriction_12(){
 FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    if(!Club->SellEquipment(2))
        return true;
    else
        return false;
};
bool Restriction_13(){
 FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->BuyEquipment(1,3,4,4);
    Club->HireEmployee(1,1,"adam",10);
    Club->SellMembership(1,1,"adam",1,300);
    return(!Club->SellEquipment(3));
};
bool Restriction_14(){
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    bool flag = true;
    flag =  Club->BuyEquipment(1,3,4,-4);
    if(flag)
        return false;
    Club->BuyEquipment(1,3,4,4);
    flag = flag && Club->HireEmployee(1,1,"adam",-10);
    if(flag)
        return false;
    Club->HireEmployee(1,1,"adam",10);
    flag = flag && Club->SellMembership(1,1,"adam",1,-300);
    return(!flag);
};
void Testing(){
    if ( /* Restriction_1() &&Restriction_2() && Restriction_3()  && */
        Restriction_4() && Restriction_5() && Restriction_6() &&  Restriction_7() && Restriction_8() &&
        Restriction_9() && Restriction_10() && Restriction_11() && Restriction_12() &&
        Restriction_13() && Restriction_14())
    cout<< endl<<endl<<endl<<endl<<"restrictions checked positive" << endl<<endl<<endl<<endl<<endl;
    else
        cout<< endl<<endl<<endl<<endl<<"restrictions checked negative" << endl;
    if(Test_1()&&Test_2()&&Test_3()&&Test_4()&&Test_5()&&Test_6()&&Test_8()&&Test_9()&&
       Test_10()&&Test_11()&& Test_12())
        cout<< endl<<endl<<endl<<endl<<"bool testing checked positive" << endl;
    else
        cout<< endl<<endl<<endl<<endl<<"bool testing checked negative" << endl;
    cout<<"Starting doing test void types :" << endl;
    Test_13();
    Test_14();
    Test_15();
    Test_16();
    Test_17();
    Test_18();
    cout<< "end of testing"<< endl;
};
