#pragma once
#include"configFiles.h"
#include"FastFuncts.h"
/*
In this file small code patches only! Like nopping one instruction, etc.
*/

//apply all another patches  from this file
void applySmallPaches();

//console command "control faction" in singleplayer game
void applyControlFaction();

//unlock all console commands
//also writes list of commands, if full logging enabled
void applyConsoleComands();