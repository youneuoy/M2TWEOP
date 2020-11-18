#include "unitsTypeChange.h"
#include "battlesResults.h"
#include "smallPatches.h"
#include "labelsChanges.h"
#include "diplomacy.h"
#include "Myeffects.h"
#include"fortsDel.h"
#include "bModelChanges.h"
#include "stratModelsPatch.h"

#include "plugins.h"
//Functions from this file are executed at certain events in the game.


//before start of a first faction turn.
void onChangeTurnNum();

//in calculation of results of the battle
void onBattleResults(); 

//on console command give_trait, after searching for character
void onGiveTrait();

//after reading EDU
void afterEDUread();

//after loading campaign or battle data
void afterLoadGameData();

//after comparison in I_CompareCounter command
void afterI_CompareCounter();

//spawn_army coords
int WINAPI spawnArmyCoords();