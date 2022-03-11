#include "header.h"
#include <iostream>
using namespace std;
SportEquipment* SportEquipmentP::getEq(){
    return Equipment;
};
SportEquipmentP* SportEquipmentP::GetNextEq(){
    return nextEq;
};
void SportEquipmentP::ChangeNext_EQ(SportEquipmentP* E){
    nextEq = E;
};
void SportEquipmentP::ChangePrev_EQ(SportEquipmentP* E){
    previousEq = E;
};
void SportEquipmentP::ChangeNext_Type_EQ(SportEquipmentP* E){
    nextEqOfThisType = E;
};
void SportEquipmentP::ChangePrev_Type_EQ(SportEquipmentP* E){
    previousEqOfThisType = E;
};
SportEquipmentP* SportEquipmentP::GetNextEqOfType(){
    return nextEqOfThisType;
};
SportEquipmentP::SportEquipmentP(SportEquipment* Eq){
    this->nextEq = nullptr;
    this->previousEq = nullptr;
    this->nextEqOfThisType = nullptr;
    this->previousEqOfThisType = nullptr;
    this->Equipment = Eq;
};
SportEquipmentP* SportEquipmentP::GetPrevEq(){
    return previousEq;
};
SportEquipmentP* SportEquipmentP::GetPrevEqOfType(){
    return previousEqOfThisType;
};
void SportEquipmentP::PrintEquipment(){
    cout<<endl<<" Eq ID: " << getEq()->getRealEqID() << endl;
    cout<<" Eq type : "<< getEq()->getTypeID() << endl;
    cout<<" occupancy 1: " << getEq()->RefOccupancy(1) << endl;
    cout<<" occupancy 2: " << getEq()->RefOccupancy(2) << endl;
    cout<<" Price: " << getEq()->GetPrice() << endl;
};
