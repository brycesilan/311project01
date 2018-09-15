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
  if(waiting.empty()==false) {
    Party* tmp=waiting.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getReservationName() << " **waiting**" << endl;
      tmp=waiting.next();
    }
  }
}

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

void Restaurant::serveParties() {
  while(occupied.empty()==false || waiting.empty()==false) {
    if(occupied.empty()==false) {
      Table* tmp=occupied.first();
      while(tmp!=nullptr) {
        tmp->decrementTimer();
        if(tmp->getTimer()<=0) {
          cout << *tmp->getParty()->getReservationName() << " finished at " << *tmp->getTableID() << endl;
          occupied.remove();
          tmp->clearTable();
          available.append(tmp);
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
            occupied.append(tmpTable);
            waiting.remove();
            available.remove(); //psuedo-code does not include this in thing
          } //I also added stuff to remove()
          tmpTable=available.next();
        }
        tmp=waiting.next();
      }
    }
  }
  for(map<string, int>::iterator it=servers.begin(); it!=servers.end(); it++) {
    cout << it->first << " served " << it->second << endl;
  }
}
