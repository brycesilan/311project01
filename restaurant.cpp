/** 
 * @file restaurant.cpp
 *
 * @breif
 *    definitions of restaurant functions and main()
 *
 * @author Connor Richards
 */

#include <iostream>
#include "restaurant.h"

using namespace std;

/**
 * @breif creates restaurant object, gets input, and serves parties
 * @param none
 * @return 0
 *
 * Runs the simulation
 */
int main() {
  Restaurant myDiner;
  myDiner.getInput();
  myDiner.serveParties();

  return 0;
}

/**
 * @breif Takes input and creates tables or parties, appends them to lists
 * @param none
 * @return none
 *
 * Takes input, depending on command, creates a table or party to go on the waiting or available lists
 */
void Restaurant::getInput() {
  //input variables
  string input;
  string tableID;
  string serverName_partyName;
  int partySize;
  int timeNeeded;

  //input takes in put until input=='end'
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

/**
 * @breif Runs restaurant simulation
 * @param none
 * @return none
 *
 * Uses the lists to run the simulation of serving customers until all customers are gone
 */
void Restaurant::serveParties() {
  //loop of restaurant being open
  while(occupied.empty()==false || waiting.empty()==false) {
    //clears parties done eating
    if(occupied.empty()==false) {
      Table* tmp=occupied.first();
      while(tmp!=nullptr) {
        bool removed=false;
        tmp->decrementTimer();
        if(tmp->getTimer()<=0) {
          cout << *tmp->getParty()->getReservationName() << " finished at " << *tmp->getTableID() << endl;
          tmp->clearTable();
          available.append(tmp);
          tmp=occupied.remove();
          removed=true;
        }
        if(removed==false) {
          tmp=occupied.next();
        }
      }
    }
    //seats waiting parties
    if(waiting.empty()==false) {
      Party* tmp=waiting.first();
      while(tmp!=nullptr) {
        bool removed=false;
        Table* tmpTable=available.first();
        while(tmpTable!=nullptr) {
          if(tmpTable->getNumSeats() >= tmp->getNumDiners()) {
            cout << *tmp->getReservationName() << " seated at " << *tmpTable->getTableID() << endl;
            tmpTable->seatParty(tmp);
            tmpTable->setTimer(tmp->getTimeRequired());
            servers[*tmpTable->getServerName()] = servers[*tmpTable->getServerName()]+tmp->getNumDiners();
            //hopefully remove() works (watch out for head, also need to make it so it wont move twice, like "remove, next" skips a person
            //also maybe consolidate the removes and appends
            occupied.append(tmpTable);
            available.remove();
            tmp=waiting.remove();
            removed=true;
            break;
          }
          tmpTable=available.next();
        }
        if(removed==false) {
          tmp=waiting.next();
        }
      }
    }
  }
  //iterates through all servers and displays # served
  for(map<string, int>::iterator it=servers.begin(); it!=servers.end(); it++) {
    cout << it->first << " served " << it->second << endl;
  }
}
