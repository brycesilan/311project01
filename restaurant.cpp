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
  string serverName;
  string partyName;
  int partySize;
  int timeNeeded;

  while(cin >> input) {
    if(input=="table") {
      cin >> tableID >> partySize >> serverName;
      cout << "table " << tableID << " is waited by " << serverName << " for " << partySize << " people" << endl;

      Table* thisTable=new Table(tableID, partySize, serverName);
      availableTables.append(thisTable);
    }
    else if(input=="party") {
      cin >> partySize >> partyName >> timeNeeded;
      cout << "the " << partyName << " party will be " << partySize << " people that need " << timeNeeded << " minutes" << endl;

      Party* thisParty=new Party(partyName, partySize, timeNeeded);
      waitingParties.append(thisParty);
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
  //TODO run simulation here, depending on bool, are there any on wait list and are any tables occupied
  while(availableTables.empty()==true && waitingParties.empty()==false) {
    occupiedTables.empty();
  }
}
