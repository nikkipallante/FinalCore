/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    //TODO: Implement tick
    
    int countExploded = 0;
    int j = 0;
    int indicesToRemove[MAX_PEOPLE_PER_FLOOR];
   // if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        for (int i = 0; i < numPeople; i++) {
            if (people[i].tick(currentTime) == true) {
                indicesToRemove[j] = i;
                j++;
                countExploded++;
            }
        }
        removePeople(indicesToRemove, countExploded);
    //}
    return countExploded;
}

void Floor::addPerson(Person newPerson, int request) {
    //TODO: Implement addPerson
    if(numPeople < MAX_PEOPLE_PER_FLOOR){
    	people[numPeople] = newPerson;
   	if ( request > 0 ) 
	{
      		setHasUpRequest(true);
   	}
   	 if ( request < 0) 
	 {
        	setHasDownRequest(true);
    	}
   	 numPeople++;
   	 resetRequests();
    }
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    Person tempPeople[MAX_PEOPLE_PER_FLOOR];
    int removeIndex = 0;
    int tempIndex = 0;
    sort(indicesToRemove, indicesToRemove + numPeopleToRemove);
    for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
        if (indicesToRemove[removeIndex] == i) {
            removeIndex++;
        }
        else if (indicesToRemove[removeIndex] != i) {
            tempPeople[tempIndex] = getPersonByIndex(i);
            tempIndex++;
        }
    }
    for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
        people[i] = tempPeople[i];
    }
    resetRequests();
    // Creat an array to store the people who will stay
}

void Floor::resetRequests() {
	setHasUpRequest(false);
	setHasDownRequest(true);
    for (int i = 0; i < MAX_PEOPLE_PER_FLOOR; i++) {
        if (people[i].getTargetFloor() - people[i].getCurrentFloor() > 0) {
            setHasUpRequest(true);
        }
        else if (people[i].getTargetFloor() - people[i].getCurrentFloor() < 0) {
            setHasDownRequest(true);
        }
    }
}


//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
