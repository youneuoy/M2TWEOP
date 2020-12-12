#pragma once

#ifdef HOTSEATTOOLLIB_EXPORTS
#define EOP_EXPORT extern "C" __declspec(dllexport)
#else
#define EOP_EXPORT extern "C" __declspec(dllimport)
#endif
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "MemWork.h"
#include"configFiles.h"
#include "realGameTypes.h"
#include"TechFuncts.h"

using namespace std;
//Here are the functions for quickly getting and setting various parameters.
namespace FastFuncts
{
	//count of factions in game
	EOP_EXPORT UINT32 getFactionsCount();
	//array of pointers to factions
	EOP_EXPORT factionStruct** getFactionsList();
	//number of passed turns
	EOP_EXPORT UINT32 getPassedTurnsNum();
	//number of year
	EOP_EXPORT UINT32 getYear();
	//season(0-summer,1-winter)
	EOP_EXPORT UINT32 getSeason();
	//find structure of faction by name
	EOP_EXPORT factionStruct* findFac(string* name);



	EOP_EXPORT int getFactionIndexByDipNum(int dipNum);
	EOP_EXPORT int getEDUIndex(const char* type);

	EOP_EXPORT unit* createUnitN(const char* type, int facNum,int exp, int arm,int weap);

	EOP_EXPORT unit* createUnitIdx(int index, int facNum, int exp, int arm, int weap);

	EOP_EXPORT int addUnitToArmy(unit* un,stackStruct* army);

	//get current active faction
	EOP_EXPORT factionStruct* getCurrTurnFac();

	//check diplomatic status
	EOP_EXPORT UINT32 checkFacsDipStance(factionStruct* first, string* next, string* state);
	EOP_EXPORT UINT32 checkFacsDipStanceFast(factionStruct* first, factionStruct* next,int state);

	//find faction by dipnum
	string findFacByModNum(int modnum);

	//change type of unit
	EOP_EXPORT void setUnitType(unit* un,UINT32 newTypeID);

	//types: 1-trait 2-ancillary 3-name
	UINT32 findCharacterParam(generalCharacterictics* gen, UINT32 type, string* param);

	UINT32 findCharacterExpandedParam(general* gen, structs::conditionExpanded* cond, string* descr);

	UINT32 findFactionExpandedParam(factionStruct* fac, structs::conditionExpandedD* cond, string* descr);

	UINT32 findNotconcrectParam(UINT32 type, string* cond);

	//array of pointers to stacks in battle
	vector<structs::arm*> getBattleStacksList();
	EOP_EXPORT vector<structs::arm*>* getBattleStacksListP();



	EOP_EXPORT void killUnit(unit* un);

	//kill unit
	EOP_EXPORT void killUnit(unit* un);

	//add anchillary to character
	EOP_EXPORT int addAnchillary(generalCharacterictics* character,anchillary* anch);
	//remove anchillary from character
	EOP_EXPORT void removeAnchillary(generalCharacterictics* character,anchillary* anch);

	EOP_EXPORT anchillary* findAnchillary(char* anchName);

	//set unit soldiersNum and EXP
	EOP_EXPORT int setUnitSoldiers(unit* un,UINT32 num, UINT32 exp, string type);

	EOP_EXPORT int setUnitSoldiersAdvanced(unit* un,int num, int exp);

	//set label of character
	EOP_EXPORT void setGeneralLabel(general* gen, string* label);
	//set battle model of character
	EOP_EXPORT void setGeneralBModel(general* gen, string* model);

	//edit diplomation
	EOP_EXPORT void setDipStance(factionStruct* first, string* next, string* state);

	//disable vassal state
	void disableVassal(factionDiplomacy* first, factionDiplomacy* next);
	//enable vassal
	void enableVassal(factionDiplomacy* first, factionDiplomacy* next);

	int getNewAge(int ageChar, int newAge);

	//make heir
	EOP_EXPORT void setHeir(generalCharacterictics* gen);

	settlementStruct* checkSett(int x, int y, factionStruct* fac);

	//close windows
	void closeFamilyTree();
	void closeOwnSettlement();
	void closeOwnCharacter();


	//get string with all traits
	//example:traits OrcRace 1 , Brave 2 , Disciplinarian 1 , GoodAmbusher 2 , GoodCommander 2 , LogisticalSkill 2
	string getTraits(generalCharacterictics* gen);

	//find port on coords
	portBuildingStruct* findPort(int x, int y);
	//find fort on coords
	fortStruct* findFort(int x, int y);

	//find character on coords
	general* findCharacter(int x, int y);

	//make crypt of string, not used, it done with games function what allocate memory, if use this you get crash after dealloc of memory
	UINT32 getLabelCrypt(const char* label);

	//unlock all console commands
	void unlockConsoleCommands();

	//write console commands info file
	void writeConsoleCommandsFile();



	stackStruct* getArmyOnCoords(int x, int y, int skippedNumber = 0);
}
