/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move()
{
    if(commandString == "s" || commandString == "S")
    {
        elevatorId = -1;
        targetFloor = -1;
        numPeopleToPickup = 0;
        totalSatisfaction = 0;
        isPass = false;
        isPickup = false;
        isSave = true;
        isQuit = false;
    }
    else if(commandString == "q" || commandString == "Q")
    {
        elevatorId = -1;
        targetFloor = -1;
        numPeopleToPickup = 0;
        totalSatisfaction = 0;
        isPass = false;
        isPickup = false;
        isSave = false;
        isQuit = true;
    }
    else if(commandString == "")
    {
        elevatorId = -1;
        targetFloor = -1;
        numPeopleToPickup = 0;
        totalSatisfaction = 0;
        isPass = true;
        isPickup = false;
        isSave = false;
        isQuit = false;
    }
    else if(commandString[2] == 'p')
    {
        elevatorId = commandString[1] - '0';
        targetFloor = -1;
        numPeopleToPickup = 0;
        totalSatisfaction = 0;
        isPass = false;
        isPickup = true;
        isSave = false;
        isQuit = false;
    }
    else if(commandString[2] == 'f')
    {
        elevatorId = commandString[1] - '0';
        targetFloor = commandString[3] - '0';
        numPeopleToPickup = 0;
        totalSatisfaction = 0;
        isPass = false;
        isPickup = false;
        isSave = false;
        isQuit = false;
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const
{
    bool moveIsValid = false;
    if(isPass || isSave || isQuit)
    {
        moveIsValid = true;
    }
    else if(elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !elevators[elevatorId].isServicing())
    {
        if(isPickup)
        {
            moveIsValid = true;
        }
        else if(targetFloor >= 0 && targetFloor < NUM_FLOORS && targetFloor != elevators[elevatorId].getCurrentFloor())
        {
            moveIsValid = true;
        }
    }
    return moveIsValid;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor)
{
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    targetFloor = 0;
    int distance = 0;
    
    for(int i = 0; i < pickupList.length(); i++)
    {
        char num = pickupList.at(i);
        int personIndex = num - '0';
        peopleToPickup[i] = personIndex;
        numPeopleToPickup++;
        
        int angerLevel = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        totalSatisfaction += (MAX_ANGER - angerLevel);
        
        int targetFloorTemp = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        if(abs(targetFloorTemp - currentFloor) > distance)
        {
            distance = abs(targetFloorTemp = currentFloor);
            targetFloor = targetFloorTemp;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
