#include "header.h"
#include <iostream>
using namespace std;
SportEquipment::SportEquipment(int TypeID, int Real_ID, int Capacity, int price){
    this->Capacity = Capacity;
    this->occupancy1 = 0;
    this->occupancy2 = 0;
    this->price = price;
    this->Real_ID = Real_ID;
    this->TypeID = TypeID;
};
int& SportEquipment::RefOccupancy(int num){
    if (num == 1){
        int& x = occupancy1;
        return x;
    }
    else{
        int& x = occupancy2;
        return x;
    }
};
int SportEquipment::getTypeID(){
    return TypeID;
};
int SportEquipment::GetEqCapacity(){
    return Capacity;
};
int SportEquipment::GetPrice(){
    return price;
};
int SportEquipment::getRealEqID(){
    return Real_ID;
};
