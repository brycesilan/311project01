//table.cpp
//Richards, Connor
//crichards14

#include "table.h"

using namespace std;

Table::Table(const string& tableID, int numSeats, const string& serverName) {
  this->tableID=new string(tableID);
  this->numSeats=numSeats;
  this->serverName=new string(serverName);
  this->timer=timer;
  party=nullptr;
}

Table::~Table() {
  delete tableID;
  delete serverName;
}
