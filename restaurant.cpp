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
 * Takes input, depending on command
 * creates a table or party to go on the waiting or available lists
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
      //new table for 'table' case, appended to available list
      cin >> tableID >> partySize >> serverName_partyName;

      Table* thisTable=new Table(tableID, partySize, serverName_partyName);
      available.append(thisTable);
    }
    else if(input=="party") {
      //new party for 'party' case, appended to waiting list
      cin >> partySize >> serverName_partyName >> timeNeeded;

      Party* thisParty=new Party(serverName_partyName, partySize, timeNeeded);
      waiting.append(thisParty);
    }
    else if(input=="end") {
      //end of input case
      break;
    }
  }
  //initialize the servers to have no served
  Table* tmpTable=available.first();
  while(tmpTable!=nullptr) {
    //set this table's server to 0 served
    servers[*tmpTable->getServerName()]=0;
    tmpTable=available.next();
  }
}

/**
 * @breif Runs restaurant simulation
 * @param none
 * @return none
 *
 * Uses the lists to run the simulation 
 * of serving customers until all customers are gone
 */
void Restaurant::serveParties() {
  //only starts if there are any available tables
  if(available.empty()==false) {
    //loop for restaurant being open
    while(occupied.empty()==false || waiting.empty()==false) {
      if(occupied.empty()==false) {
        //clears parties done eating
        //if anyone is sitting at a table (if occupied)
        Table* tmp=occupied.first();
        while(tmp!=nullptr) {
          bool removed=false;
          tmp->decrementTimer();
          if(tmp->getTimer()<=0) {
            //found table to be cleared
            cout << *tmp->getParty()->getReservationName();
            cout << " finished at " << *tmp->getTableID() << endl;
            tmp->clearTable();
            available.append(tmp);
            tmp=occupied.remove();
            removed=true;
          }
          if(removed==false) {
            //if nothing was deleted, move to next occupied table
            tmp=occupied.next();
          }
        }
      }
      if(waiting.empty()==false) {
        //seats waiting parties
        //if anyone is waiting to be seated (if waiting)
        Party* tmp=waiting.first();
        while(tmp!=nullptr) {
          bool removed=false;
          Table* tmpTable=available.first();
          while(tmpTable!=nullptr) {
            if(tmpTable->getNumSeats() >= tmp->getNumDiners()) {
              //found an available table for the current party
              int tmpServer=servers[*tmpTable->getServerName()]+tmp->getNumDiners();
              cout << *tmp->getReservationName();
              cout << " seated at " << *tmpTable->getTableID() << endl;
              //seat party at table
              tmpTable->seatParty(tmp);
              tmpTable->setTimer(tmp->getTimeRequired());
              servers[*tmpTable->getServerName()] = tmpServer;
              //move table to occupied list
              occupied.append(tmpTable);
              available.remove();
              tmp=waiting.remove();
              removed=true;
              break;
            }
            tmpTable=available.next();
          }
          if(removed==false) {
            //if nothing was deleted, move to next waiting party
            tmp=waiting.next();
          }
        }
      }
    }
  }
  //iterates through all servers and displays # served
  for(map<string, int>::iterator it=servers.begin(); it!=servers.end(); it++) {
    cout << it->first << " served " << it->second << endl;
  }
}
