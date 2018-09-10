//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"
#include "doublylinkedlist.h"
#include "party.h"
#include "table.h"

using namespace std;

void doCommands(DoublyLinkedList<Table> &availableTables, DoublyLinkedList<Party> &waitingParties);
void runSim(DoublyLinkedList<Table> &availableTables, DoublyLinkedList<Table> &occupiedTables, DoublyLinkedList<Party> &waitingParties);

int main() {
  DoublyLinkedList<Table> availableList;
  DoublyLinkedList<Table> occupiedList;
  DoublyLinkedList<Party> waitingList;

  doCommands(availableList, waitingList);
  runSim(availableList, occupiedList, waitingList);

  return 0;
}

void doCommands(DoublyLinkedList<Table> &availableTables, DoublyLinkedList<Party> &waitingParties) {
  string input;
  string tableID;
  string serverName_partyName;
  int partySize;
  int timeNeeded;

  cout << "table: 'table tableID partySize serverName'" << endl;
  cout << "party: 'party partySize partyName timeNeeded'" << endl;

  while(cin >> input) {
    if(input=="table") {
      cin >> tableID >> partySize >> serverName_partyName;

      Table* thisTable=new Table(tableID, partySize, serverName_partyName);
      availableTables.append(thisTable);

      cout << "added table" << endl;
    }
    else if(input=="party") {
      cin >> partySize >> serverName_partyName >> timeNeeded;

      Party* thisParty=new Party(serverName_partyName, partySize, timeNeeded);
      waitingParties.append(thisParty);

      cout << "added party" << endl;
    }
    else if(input=="end") {
      break;
    }
    else {
      cerr << "Error: Invalid input" << endl;
    }
  }
}

void runSim(DoublyLinkedList<Table> &availableTables, DoublyLinkedList<Table> &occupiedTables, DoublyLinkedList<Party> &waitingParties) {
  while(availableTables.empty()==false && waitingParties.empty()==true) {
    if(occupiedTables.empty()==false) {
      Table* tmp=occupiedTables.first();
      while(tmp!=nullptr) {
        tmp->decrementTimer();
        if(tmp->getTimer()==0) {
          cout << tmp->getParty()->getReservationName() << " finished at " << tmp->getTableID() << endl;
          occupiedTables.remove();
          tmp->clearTable();
          availableTables.append(tmp);
        }
        tmp=occupiedTables.next();
      }
    }
    if(waitingParties.empty()==false) {
      Party* tmp=waitingParties.first();
      while(tmp!=nullptr) {
        Table* tmpTable=availableTables.first();
        while(tmp!=nullptr) {
          if(tmpTable->getNumSeats()<=tmp->getNumDiners()) {
            cout << tmp->getReservationName() << " seated at " << tmpTable->getTableID() << endl;
            //set table->party, set table->timer
            //add # of diners to server total
            //move table to occupied list
            //remove party from waiting list
          }
          tmpTable=availableTables.next();
        }
        tmp=waitingParties.next();
      }
    }
  }
  //print number of diners served by each server
}
