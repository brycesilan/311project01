//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"
//TODO might need to include other h files

using namespace std;

int main() {
  string input="0";
  string tableID;
  string serverName;
  string partyName;
  int partySize;
  int timeNeeded;

  while(cin >> input) {

    if(input=="table") {
      cin >> tableID >> partySize >> serverName;
      cout << "table " << tableID << " is waited by " << serverName << " for " << partySize << " people" << endl;
      //TODO create table
    }
    else if(input=="party") {
      cin >> partySize >> partyName >> timeNeeded;
      cout << "the " << partyName << " party will be " << partySize << " people that need " << timeNeeded << " minutes" << endl;
      //TODO create party
    }
    else if(input=="end") {
      break;
    }
    else {
      cerr << "Error: Invalid input" << endl;
      return 1;
    }
  }

  return 0;
}
