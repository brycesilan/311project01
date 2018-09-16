//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"

using namespace std;

int main() {
  Restaurant myDiner;
  myDiner.getInput();
  myDiner.printLists(); //TODO just for testing
  myDiner.serveParties();

  return 0;
}


void Restaurant::printLists() {//TODO just for testing
  if(available.empty()==false) {
    Table* tmp=available.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getTableID() << " **available table**" << endl;
      tmp=available.next();
    }
  }
  else {
    cout << "----------- available is empty -----------" << endl;
  }
  if(waiting.empty()==false) {
    Party* tmp=waiting.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getReservationName() << " **waiting**" << endl;
      tmp=waiting.next();
    }
  }
  else {
    cout << "----------- waiting is empty -----------" << endl;
  }
  if(occupied.empty()==false) {
    Table* tmp=occupied.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getTableID() << " **occupied**" << endl;
      tmp=occupied.next();
    }
  }
  else {
    cout << "----------- occupied is empty -----------" << endl;
  }
}

//input function definition
//gets input, places in table or party, applies to available or waiting lists
void Restaurant::getInput() {
  string input;
  string tableID;
  string serverName_partyName;
  int partySize;
  int timeNeeded;

  while(cin >> input) {
    if(input=="table") {
      cin >> tableID >> partySize >> serverName_partyName;

      Table* thisTable=new Table(tableID, partySize, serverName_partyName);
      available.append(thisTable);
    }
    else if(input=="party") {
      cin >> partySize >> serverName_partyName >> timeNeeded;

      Party* thisParty=new Party(serverName_partyName, partySize, timeNeeded);
      waiting.append(thisParty);
    }
    else if(input=="end") {
      break;
    }
  }
}

//party serving function definition
//while there are people eating or waiting
//when done eating, removed from occupied, appended to available
//if table found for waiting party, placed on table and appended to occupied
//when primary while loop is done, prints the contents of the map
void Restaurant::serveParties() {
  while(occupied.empty()==false || waiting.empty()==false) {
    if(occupied.empty()==false) {
      Table* tmp=occupied.first();
      while(tmp!=nullptr) {
        tmp->decrementTimer();
        if(tmp->getTimer()<=0) {
          cout << *tmp->getParty()->getReservationName() << " finished at " << *tmp->getTableID() << endl;
          tmp->clearTable();
          available.append(tmp);
          occupied.remove();
        }
        tmp=occupied.next();
      }
    }
    if(waiting.empty()==false) {
      Party* tmp=waiting.first();
      while(tmp!=nullptr) {
        Table* tmpTable=available.first();
        while(tmpTable!=nullptr) {
          if(tmpTable->getNumSeats() >= tmp->getNumDiners()) {
            cout << *tmp->getReservationName() << " seated at " << *tmpTable->getTableID() << endl;
            tmpTable->seatParty(tmp);
            tmpTable->setTimer(tmp->getTimeRequired());
            servers[*tmpTable->getServerName()] = servers[*tmpTable->getServerName()]+tmp->getNumDiners();
            available.remove(); //psuedo-code does not include this
            occupied.append(tmpTable);
            waiting.remove();
            printLists();
            break;
          }
          cout << "moving to next table" << endl;
          tmpTable=available.next();
          printLists();
        }
        cout << "moving to next party" << endl;
        tmp=waiting.next();
        printLists();
      }
    }
  }
  for(map<string, int>::iterator it=servers.begin(); it!=servers.end(); it++) {
    cout << it->first << " served " << it->second << endl;
  }
}
