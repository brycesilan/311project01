//party.cpp
//Richards, Connor
//crichards14

#include "party.h"

//no arg class constructor
Party::Party() {
  reservationName=nullptr;
  numDiners=0;
  timeRequired=0;
}

//class constructor definition
Party::Party(const string& reservationName, int numDiners, int timeRequired) {
  this->reservationName=new string(reservationName);
  this->numDiners=numDiners;
  this->timeRequired=timeRequired;
}

//class destructor definition
Party::~Party() {
  delete reservationName;
}
