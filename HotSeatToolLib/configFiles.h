#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "MemWork.h"
#include "realGameTypes.h"

using namespace std;



//diplomacy codes:
//NEUTRAL state of faction
#define DIP_NEUTRAL 200
//war state of faction
#define DIP_WAR 600
//allied state of faction
#define DIP_ALLIED 0

#define DIPFILE_DIPSTATE 800
//codes of conditions:
//1-trait 2-ancillary 3-name 4-label 999-passed_Turns 900-4_coords

#define TRAIT_COND_CODE 0x1
#define ANCILLARY_COND_CODE 0x2
#define NAME_COND_CODE 0x3
#define LABEL_COND_CODE 0x4

#define PASSED_TURNS_COND_CODE 0x999
#define COORDS_COND_CODE 0x900

class structs
{
public:
	struct arm {
		//numbers of units
		UINT32 num;

		//army pointer
		stackStruct* army;


		//condition destroy_or_rout_enemy 
		UINT32 condDest;
		//condition capture settlement
		UINT32 condSetl;
		//defender or not
		UINT32 ifDef;
		//side in battle(0-3)
		UINT32 side;

		//deployment data offset
		DWORD deploy;

		//units
		vector<unit*>units;
	};




	static struct  cfgStructType{
		//steam =2, kingdoms=1
		UINT32 gamever;
		string modPatch;
		string langP;
		//enable full logging(file all.youneuoylog)
		int fullLogging=0;
		//unlock console command change faction in singleplayer game
		int unlockChangeFaction = 0;
		//berserkers crach fix
		int bersPatch=1;

		//online history battles fix
		int histBattleFix = 0;

		int DCI = 0;

		//unlock console commands
		int unlockConsoleCommands = 0;

		//character ui functions
		int characterUIMenus = 1;
		//allow spawn_army changes
		int spawnArmyCoords = 0;

		//bodyguard replenish max count
		int maxBodSize = 31;

		string anchillaryDelLab = "try_change_this_label";
		string anchillaryChangeLab = "try_change_this_label_to";

		//overwritingValues:
		char* legioString;
	}cfg;

	static struct gameDataOffsetsType{
		//maybe basic game offset
		DWORD bDataOffset;

		//UI offsets
		DWORD stratUiOffset;

		//start of units edu entries
		DWORD unitTypesStart;
		//start of factions entries
		DWORD factionOffsetsStart;
		//offset of stacks in battle
		DWORD battleStacksOffsetStart;
		//offset of the legio string use
		DWORD legioStringOffset;

		//battle camera offsets
		DWORD cameraOffsetsStartB;

		//models info offsets
		DWORD modelsInfoOffset;

		//check offset for models thread, 0 on start of loading screen
		DWORD checkThreadOffsetModels;

		//list of loaded "static" strat models offset start(settlements, resources, etc)
		DWORD statStratModelsListOffset;

		//start of console commands array
		DWORD consoleCommandsOffset;
	}gameDataOffsets;


	static struct gameCodeOffsetsType {
		//function for set string and crypt for it
		DWORD setStringAndCryptOffset;
		//offset of jump instruction after checking game type after console command "change faction"
		DWORD consoleChangeFactionOffset;

		//kill unit
		DWORD killUnitOffset;
		//kill character on stratmap
		DWORD killCharStratMapOffset;

		//load "static" strat_model for settlement, resource, etc.
		DWORD loadStratCasModelOffset;


		//highlight code
		DWORD highlightCodeOffset;

		//start of console commands check code(for lock/unlock it)
		DWORD consoleCommandsOffset;

		//create unit
		DWORD createUnitOffset;
		//attach unit to stack
		DWORD addUnitToArmyOffset;
	}gameCodeOffsets;

	//dont used now
	static struct gameDataForUsageC {
		UINT32 herebedata;
	}gameDataUsage;

	//type of unit
	struct unitTypeCh {
		UINT32 typeID;
		string typeS;
	};
	//type of change unit to another
	struct unitChangeS {
		//1-trait 2-ancillary 3-name 999-passed_Turns
		UINT32 typeCondition;
		string condition;
		UINT32 priority;

		unitTypeCh newUnit;
		unitTypeCh oldUnit;
	};


	struct modelStratStat {
		UINT32 index;
		string name;
		string patch;

		stratResMod* modelP;
	};

	static vector<modelStratStat*> modelsStrat;

	static vector<unitChangeS*> changeUnits;

	struct conditionExpanded {
		UINT32 typeCondition;

		UINT32 condition1;
		UINT32 condition2;
		UINT32 condition3;
		UINT32 condition4;
		string condition;
		//2 - forbidden,1 - prerequisite, 0 - optional
		UINT32 isImportant;
	};

	struct labelChangeS {
		//id`s of the records - 1000-label:
		//id`s of the conditions
		//1-trait 2-ancillary 3-name 4-label 999-passed_Turns 900-4_coords
		vector<conditionExpanded*>conditions;

		UINT32 priority;
		UINT32 importans=0;

		string descLabel;
		string newlabel;
	};
	static vector<labelChangeS*> changeLabels;

	static vector<labelChangeS*> changeBModels;


	static vector<string> immutableLabels;


	struct ageStep {
		UINT32 type;
		string param;
		string forScreen;
	};

	static struct dataAgeStructType{
		vector<ageStep*> immortals;
		string standartAgeString;
		DWORD standartAgeStringOffset;
	}dataAgeStruct;

	struct conditionExpandedD {
		UINT32 typeCondition;

		string conditionS1;
		string conditionS2;
		string conditionS3;
		//2 - forbidden,1 - prerequisite, 0 - optional
		UINT32 isImportant;
	};

	struct I_CompareCounterS
	{
		//for I_CompareCounter
		UINT32 TypeOperation;
		string counterName;
		UINT32 number;
		I_CompareCounterS(string operation, string counter, string numberS) {
			if (operation == "==")
				TypeOperation = 4;
			else if (operation == ">")
				TypeOperation = 5;
			else if (operation == "<")
				TypeOperation = 6;
			else if (operation == "!=")
				TypeOperation = 7;
			else if (operation == ">=")
				TypeOperation = 8;
			else if (operation == "<=")
				TypeOperation = 9;
			else TypeOperation = 0;
			counterName = counter;
			number = stoi(numberS);
		}
	};

	struct dipCond {
		string descDip;
		string firstFac;
		string nextFac;
		string newState;
		UINT32 priority;
		UINT32 importans;
		vector<conditionExpandedD*>conditions;

		//for I_CompareCounter
		I_CompareCounterS* cmpcounter;
	};
	static vector<dipCond*> changeDips;


	struct fortCond {
		int x;
		int y;
	};

	static vector<fortCond*> lForts;
};



//Different offsets for the data depending on the version of the game
void setOffsets();

//type of param from config file
UINT32 findParam(string s);

//for age functions
void findAParam(structs::ageStep* arg, string s);

string readString(DWORD adr);

void Write(void* ptr, DWORD to, size_t size);

template <typename  data>
void Read(DWORD from, data* p, size_t size=4)
{
	memset(p, 0, size);
	memcpy(p, (LPVOID)from, size);
}