#include <iostream>
#include "header.h"
#include "Testing.h"
using namespace std;

int main()
{
   //Testing();
   // example of program usage:
    FitnessClub* Club = new FitnessClub(1000, 50, 40);
    Club->SellMembership(1,3,"henryk",1,30);
    Club->SellMembership(1,4,"maciek",1,300);
   Club->SellMembership(1,1,"Adrian",1,300);
    Club->SellMembership(1,11,"Andrzej",1,300);
    Club->PrintCustomers();
    Club->BuyEquipment(1,1,4,40);
    Club->BuyEquipment(1,3,4,40);
    Club->BuyEquipment(2,5,3,40);
    Club->BuyEquipment(2,6,4,40);
    Club->HireEmployee(1,1,"adam",20);
    Club->HireEmployee(1,6,"wojtek",20);
    Club->HireEmployee(1,4,"kuba",20);
    Club->HireEmployee(1,3,"ania",20);
    Club->HireEmployee(1,8,"kamil",20);
    Club->HireEmployee(1,9,"mariola",20);
    Club->SellMembership(2,16,"Antoni",1,300);
    Club->ChangeWage(1, 40);
    Club->PrintEmployees();
    //Club->DiagnoseClub();
    Club->ExpandContract(2);
    Club->PrintClub();
    Club->~FitnessClub();

}
