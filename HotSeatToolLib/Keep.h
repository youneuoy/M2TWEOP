#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 
#include "overwritingValues.h"
//codes of strings:
#define LOC_EFFECTS_MONEY 1

#define LOC_EFFECTS_LOYALITY 2

#define LOC_EFFECTS_LOYALITY_PERS 3

#define LOC_EFFECTS_AUTHORITY_LEADER 4

//localisation and info about effects
class Keep
{
public:
	struct changeInfo {
		int effect;
		UINT32 typeId;
	};
	struct typeI {
		UINT32 typeId;
		string info;
	};
	static vector<typeI*>typesI;
	
	static void readInfo();

	static string* getEffectLoc(UINT32 id);
};

