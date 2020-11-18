#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 
#include "BigMenus.h"
#include "Keep.h"
#define EFFECT_NOTHING 1
#define EFFECT_MONEY 2
#define EFFECT_LOYALITY 3
#define EFFECT_LOYALITY_PERS 4
#define EFFECT_AUTHORITY_LEADER 5


#define EFFECT_heir_accepted 1
class Myeffects
{
public:
	struct eff {
		int param;
		UINT32 type;
		string paramS;
	};

	struct effect {
		UINT32 id;
		vector<eff*>effects;
	};

	static vector<effect*>effectList;

	static void readEffects();

	static int findEffectPar(string par);

	static effect* getEffect(UINT32 id);

	static void drawEffectList(UINT32 num, const char* tooltip);

	static void makeEffString(eff* ef);

	static void setCharacterEffects(generalCharacterictics* gen, UINT32 num);
};

