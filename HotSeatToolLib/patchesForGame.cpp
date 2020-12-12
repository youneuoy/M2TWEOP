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
	char* traitString=nullptr;
	general* character = nullptr;
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

	startFortsModelsPatch::readModelsFile();
}

void afterLoadGameData()
{
	diplomacy::checkAndChangeDips();
}

void afterI_CompareCounter()
{
	UINT32* counter = nullptr;
	CompareCounter* compareCounter = nullptr;
	_asm {
		mov counter, edx
		mov compareCounter, esi
	}
	if (compareCounter == 0)return;
	diplomacy::checkAndChangeDipsCompareCounter(compareCounter, *counter);
}



int __stdcall spawnCharacterCoords()
{
	UINT32 x = 0;
	UINT32 y = 0;
	_asm {
		mov x, edx
		mov y, esi
	}
	if (structs::cfg.spawnArmyCoords == 1)
	{
		portBuildingStruct* port = FastFuncts::findPort(x, y);
		if (port != nullptr)
		{
			general* gen = FastFuncts::findCharacter(x, y);
			if (gen == nullptr || gen->ifMarkedToKill)
			{
				return 1;
			}
		}
	}

	return 0;
}
struct
{
	bool ifArmyAtPort = false;
	int x = 0;
	int y = 0;


	portBuildingStruct* port = nullptr;
}spawnPort;
int __stdcall spawnArmyCoords()
{
	UINT32 x = 0;
	UINT32 y = 0;
	_asm 
	{
		mov x, edx
		mov y, esi
	}
	if (structs::cfg.spawnArmyCoords == 1)
	{
		portBuildingStruct* port = FastFuncts::findPort(x, y);
		if (port != nullptr)
		{
			general* gen = FastFuncts::findCharacter(x, y);
			if (gen==nullptr|| gen->ifMarkedToKill)
			{
				spawnPort.ifArmyAtPort = true;

				spawnPort.x = x;
				spawnPort.y = y;

				spawnPort.port = port;

				return 1;
			}
		}
	}


	spawnPort.ifArmyAtPort = false;
	return 0;
}

void __stdcall spawnEndArmyCoords()
{
	if (!spawnPort.ifArmyAtPort)return;
	spawnPort.ifArmyAtPort = false;

	if (spawnPort.port == nullptr) return;

	general* gen = FastFuncts::findCharacter(spawnPort.x, spawnPort.y);
	if (gen == nullptr)return;

	if (spawnPort.port->x != gen->xCoord|| spawnPort.port->y != gen->yCoord)return;

	if (FastFuncts::checkFacsDipStanceFast(spawnPort.port->fac, gen->genChar->faction, DIP_WAR) == 0)return;


	factionStruct* fac = gen->genChar->faction;

	DWORD adr=0;
	if (structs::cfg.gamever == 2)//steam
	{
		adr = 0x005a0050;
	}
	else
	{
		adr = 0x0059fb70;
	}
	_asm
	{
		mov ecx, gen
		mov eax, adr
		call eax
	}
}
