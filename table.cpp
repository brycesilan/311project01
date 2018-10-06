/**
 * @file table.cpp
 *
 * @breif
 *    definitions of table class functions
 *
 * @author Connor Richards
 */

#include "table.h"

//no arg class constructor
Table::Table() {
  //set all vars. to 0/null
  tableID=nullptr;
  serverName=nullptr;
  party=nullptr;
  numSeats=0;
  timer=0;
}

//class constructor definition
Table::Table(const string& tableID, int numSeats, const string& serverName) {
  //set the vars. to each respective arg. that was passed in (party is null)
  this->tableID=new string(tableID);
  this->numSeats=numSeats;
  this->serverName=new string(serverName);
  this->timer=timer;
  party=nullptr;
}

//class destructor definition
Table::~Table() {
  //deleted the strings
  delete tableID;
  delete serverName;
}

//party seating function definition
void Table::seatParty(const Party* newParty) {
    //sets party var. to the party passed in, and sets timer
    party=newParty;
    timer=party->getTimeRequired();
}
