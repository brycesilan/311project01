//table.cpp
//Richards, Connor
//crichards14

#include "table.h"

using namespace std;

//no arg class constructor
Table::Table() {
  tableID=nullptr;
  numSeats=0;
  serverName=nullptr;
  timer=0;
  party=nullptr;
}

//class constructor definition
Table::Table(const string& tableID, int numSeats, const string& serverName) {
  this->tableID=new string(tableID);
  this->numSeats=numSeats;
  this->serverName=new string(serverName);
  this->timer=timer;
  party=nullptr;
}

//class destructor definition
Table::~Table() {
  delete tableID;
  delete serverName;
}

//party seating function definition
void Table::seatParty(const Party* newParty) {
  party=newParty;
  timer=party->getTimeRequired();
}
