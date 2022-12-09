/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState)
{
    //find floor with largest number of people
    int floorMostPeople = 0;
    for(int i = 0; i < NUM_FLOORS; i++)
    {
        if(buildingState.floors[i].numPeople > buildingState.floors[floorMostPeople].numPeople)
        {
            floorMostPeople = i;
        }
    }
    int elevatorToUse = 0;
    for(int i = 0; i < NUM_ELEVATORS; i++)
    {
        if(!buildingState.elevators[i].isServicing)
        {
            elevatorToUse = i;
            break;
        }
    }
    return "e" + to_string(elevatorToUse) + "f" + to_string(floorMostPeople);
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup)
{
    return "";
}
