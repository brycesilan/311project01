//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"

using namespace std;

int main() {
  Restaurant myDiner;

  myDiner.getInput();

  myDiner.printLists();

  myDiner.serveParties();

  return 0;
}

void Restaurant::printLists() {
  if(available.empty()==false) {
    Table* tmp=available.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getTableID() << " ** is an available table**" << endl;
      tmp=available.next();
    }
  }
  if(waiting.empty()==false) {
    Party* tmp=waiting.first();
    while(tmp!=nullptr) {
      cout << "--------- " << *tmp->getReservationName() << " **is waiting**" << endl;
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
        if(tmp->getTimer()==0) {
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
            servers[*tmpTable->getServerName()] = servers[*tmpTable->getServerName()]+tmp->getNumDiners();
            occupied.append(tmpTable);
            waiting.remove();
            available.remove();
            break;
          }
          cout << "***** going to next available, currently is: " << *tmpTable->getServerName() << endl;
          tmpTable=available.next();
          cout << "***** went to next, tmpTable is " << *tmpTable->getServerName() << endl;
        }
        cout << "***** going to next waiting, currently is :" << *tmp->getReservationName() << endl;
        tmp=waiting.next();
        //cout << "***** went to next, tmp is " << *tmp->getReservationName() << endl;
      }
    }
  }
  for(map<string, int>::iterator it=servers.begin(); it!=servers.end(); it++) {
    cout << it->first << " served " << it->second << endl;
  }
}
