//party.cpp
//Richards, Connor
//crichards14

#include "party.h"

using namespace std;

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
