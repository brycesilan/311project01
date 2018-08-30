//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"
#include "doublylinkedlist.h"
#include "party.h"
#include "table.h"

using namespace std;

int main() {
  DoublyLinkedList<Table> availableList;
  DoublyLinkedList<Party> waitingList;
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

      /*
      Table thisTable;
      availableList.append(thisTable);
      */
    }
    else if(input=="party") {
      cin >> partySize >> partyName >> timeNeeded;
      cout << "the " << partyName << " party will be " << partySize << " people that need " << timeNeeded << " minutes" << endl;

      //waitingList.append(Party(partyName, partySize, timeNeeded));
    }
    else if(input=="end") {
      break;
    }
    else {
      cerr << "Error: Invalid input" << endl;
    }
  }

  return 0;
}
