#include "patchesForGame.h"



void onChangeTurnNum()
{
	diplomacy::checkAndChangeDips();
	checkAndChangeUnitsTypeFunc();
	checkAndChangeLabels();
	bModelChanges::checkAndChangeModels();

	plugins::onChangeTurnNum();
}

void onBattleResults()
{
	//setBattleResults();
}

void onGiveTrait()
{
	char* traitString;
	general* character;
	_asm {
		mov traitString, esi
		mov character, edx
	}
	if (character == 0)	return;

	string traitS(traitString);
	checkLabForDelete(&traitS, character);
}

void afterEDUread()
{
	readWriteValues();
	applySmallPaches();

	readUnitsTypesFunc();

	diplomacy::readDipFile();
	Myeffects::readEffects();
	tipsEs::startChecks(1);

	readFortsFile();

	bModelChanges::readModelsFile();

	stratModelsPatch::runStratModelsChangeThread();
}

void afterLoadGameData()
{
	diplomacy::checkAndChangeDips();
}

void afterI_CompareCounter()
{
	UINT32* counter;
	CompareCounter* compareCounter;
	_asm {
		mov counter, edx
		mov compareCounter, esi
	}
	if (compareCounter == 0)return;
	diplomacy::checkAndChangeDipsCompareCounter(compareCounter, *counter);
}

int __stdcall spawnArmyCoords()
{
	UINT32 x;
	UINT32 y;
	_asm {
		mov x, edx
		mov y, esi
	}
	if (structs::cfg.spawnArmyCoords == 1)
	{
		if (FastFuncts::findPort(x, y) != nullptr)
		{
			if (FastFuncts::findCharacter(x, y) == nullptr)
			{
				return 1;
			}
		}
	}
	return 0;
}
