/**
 * @file party.cpp
 *
 * @brief
 *    definitions of party class functions
 *
 * @author Connor Richards
 */

#include "party.h"

//no arg class constructor
Party::Party() {
  //set all vars. to 0/null
  reservationName=nullptr;
  numDiners=0;
  timeRequired=0;
}

//class constructor definition
Party::Party(const string& reservationName, int numDiners, int timeRequired) {
  //set all vars. to respective things passed in
  this->reservationName=new string(reservationName);
  this->numDiners=numDiners;
  this->timeRequired=timeRequired;
}

//class destructor definition
Party::~Party() {
  //deleted string
  delete reservationName;
}
