//restaurant.cpp
//Richards, Connor
//crichards14

#include <iostream>
#include "restaurant.h"
//TODO might need to include other h files

using namespace std;

int main() {
  string input="0";

  while(cin >> input) {
    if(input=="table") {
    }
    else if(input=="party") {
    }
    else if(input=="end") {
      break;
    }
    else {
      cerr << "Error: Invalid input" << endl;
      return 0;
    }
  }

  return 0;
}
