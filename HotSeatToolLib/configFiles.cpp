#include "configFiles.h"

structs::cfgStructType structs::cfg;
structs::gameDataForUsageC structs::gameDataUsage;
structs::gameDataOffsetsType structs::gameDataOffsets;
structs::gameCodeOffsetsType structs::gameCodeOffsets;
structs::dataAgeStructType structs::dataAgeStruct;
vector<structs::dipCond*> structs::changeDips;
vector<structs::unitChangeS*> structs::changeUnits;
vector<structs::labelChangeS*> structs::changeLabels;
vector<structs::labelChangeS*> structs::changeBModels;
vector<structs::fortCond*> structs::lForts;
vector<structs::modelStratStat*> structs::modelsStrat;
vector<string> structs::immutableLabels;

//s
void Write(void* ptr, DWORD to, size_t size)
{

	HANDLE h = GetCurrentProcess();
	DWORD oldMemProtect = 0;
	VirtualProtectEx(h, (LPVOID)to, size, PAGE_EXECUTE_READWRITE, &oldMemProtect);
	WriteProcessMemory(h, (LPVOID)to, ptr, size, NULL);
	VirtualProtectEx(h, (LPVOID)to, size, oldMemProtect, &oldMemProtect);

	CloseHandle(h);
}

string readString (DWORD adr)
{
	if (adr == 0)
		return "";
	DWORD len = 0;
	char c;
	do {
		Read(adr + len, &c, 1);
		len++;
	} while (c != '\0');
	len--;
	string s;
	s.resize(len);
	Read(adr, &s[0], len);
	return s;
}

void setOffsets()
{
	if (structs::cfg.gamever == 1)
	{
		structs::gameDataOffsets.bDataOffset = 0x2c64988;
		structs::gameDataOffsets.cameraOffsetsStartB = 0x0198848c;
		structs::gameDataOffsets.stratUiOffset = 0x02cb62fc;
		structs::gameDataOffsets.modelsInfoOffset = 0x01667288;
		structs::gameDataOffsets.battleStacksOffsetStart = 0x1BACCFC;
		structs::gameDataOffsets.statStratModelsListOffset = 0x01b5e708;
		structs::gameDataOffsets.consoleCommandsOffset = 0x0168ba88;

		structs::gameDataOffsets.checkThreadOffsetModels = 0x01986c48;

		structs::gameDataOffsets.unitTypesStart = 0x0190bd0c;
		structs::gameDataOffsets.factionOffsetsStart = 0x02c00140;
		structs::gameDataOffsets.legioStringOffset = 0x008ea8ff+1;
		structs::gameCodeOffsets.setStringAndCryptOffset = 0x00d4cfd0;
		structs::gameCodeOffsets.consoleChangeFactionOffset = 0x00d329aa;


		structs::gameCodeOffsets.killUnitOffset = 0x007417e0;
		structs::gameCodeOffsets.killCharStratMapOffset = 0x00592900;

		structs::gameCodeOffsets.loadStratCasModelOffset = 0x00a04380;

		structs::gameCodeOffsets.highlightCodeOffset = 0x009e0ec4;

		structs::gameCodeOffsets.consoleCommandsOffset = 0x00d2d763;

		structs::gameCodeOffsets.createUnitOffset = 0x008edf60;
		structs::gameCodeOffsets.addUnitToArmyOffset = 0x00719380;
	}
	else if (structs::cfg.gamever == 2)
	{
		structs::gameDataOffsets.bDataOffset = 0x2C1B8D0;
		structs::gameDataOffsets.cameraOffsetsStartB = 0x0193f34c;
		structs::gameDataOffsets.stratUiOffset = 0x2C6D1B0;
		structs::gameDataOffsets.modelsInfoOffset = 0x0161f3b0;
		structs::gameDataOffsets.statStratModelsListOffset = 0x01b155d8;
		structs::gameDataOffsets.consoleCommandsOffset = 0x01644228;


		structs::gameDataOffsets.checkThreadOffsetModels = 0x193DAF8;

		structs::gameDataOffsets.unitTypesStart = 0x18C2BAC;
		structs::gameDataOffsets.factionOffsetsStart = 0x02bb7088;
		structs::gameDataOffsets.battleStacksOffsetStart = 0x01B63C44;

		structs::gameDataOffsets.legioStringOffset = 0x008eb37f+1;
		structs::gameCodeOffsets.setStringAndCryptOffset = 0x00d47330;
		structs::gameCodeOffsets.consoleChangeFactionOffset = 0x00d2cd2a;


		structs::gameCodeOffsets.killUnitOffset = 0x00741F70;
		structs::gameCodeOffsets.killCharStratMapOffset = 0x00592e00;


		structs::gameCodeOffsets.loadStratCasModelOffset = 0x00a04f00;

		structs::gameCodeOffsets.highlightCodeOffset = 0x009e1a64;

		structs::gameCodeOffsets.consoleCommandsOffset = 0x00d27ae3;

		structs::gameCodeOffsets.createUnitOffset = 0x008ee9e0;
		structs::gameCodeOffsets.addUnitToArmyOffset = 0x00719ab0;
	}
}

UINT32 findParam(string s)
{
	if (s == "trait")
	{
		return 1;
	}
	else if (s == "ancillary")
	{
		return 2;
	}
	else if (s == "name")
	{
		return 3;
	}
	else if (s == "label")
	{
		return 4;
	}
	else if (s == "4_coords")
	{
		return 900;
	}
	else if (s == "passed_Turns")
	{
		return 999;
	}
	else if (s == "passed_Turns>")
	{
		return 998;
	}
	else if (s == "passed_Turns<")
	{
		return 997;
	}
	else if (s == "passed_Turns=")
	{
		return 996;
	}
	else if (s == "label:")
	{
		return 1000;
	}
	else if (s == "diplomacy:")
	{
		return 2000;
	}
	else if (s == "diplomatic_status")
	{
		return 800;
	}
	else if (s=="I_CompareCounter")
	{
		return 100;
	}
	else if (s == "fortCoords")
	{
		return 500;
	}
	else if (s == "Battle_model_change:")
	{
		return 5000;
	}
	else if(s=="status")
	{
		return 5001;
	}
	else if (s == "faction")
	{
		return 5002;
	}
	else if (s == "ModelChange:")
	{
		return 501;
	}
return 0;
}

void findAParam(structs::ageStep* arg, string s)
{
	if (s == "trait")
	{
		arg->type = 1;
		return;
	}
	else if (s == "ancillary")
	{
		arg->type = 2;
		return;
	}
	else if (s == "name")
	{
		arg->type = 3;
		return;
	}
	else
	{
		arg->type = 0;
	}
}


