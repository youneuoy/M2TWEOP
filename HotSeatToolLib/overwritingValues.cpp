#include"overwritingValues.h"
owW::config owW::cfg;

void readWriteValues()
{
	string ls;
	string s = structs::cfg.modPatch + "\\modConfig.youneuoycfg";
	ifstream f2(s);
	while (f2.good())
	{

		getline(f2, s);
		findOWParam(&structs::cfg.fullLogging, s, "FullLoggingEnabled");
		findOWParam(&structs::cfg.unlockChangeFaction, s, "UnlockConsoleChangeFaction");
		findOWParam(&structs::cfg.bersPatch, s, "CorrectionOfBerserkers");
		findOWParam(&structs::cfg.histBattleFix, s, "HistoryBattlesSoldiersNumberFix");
		findOWParam(&structs::cfg.DCI, s, "DCI");
		findOWParam(&structs::cfg.spawnArmyCoords, s, "SpawnArmyCoordsPatch");
		findOWParam(&structs::cfg.characterUIMenus, s, "CharacterUIMenus");
		findOWParam(&structs::cfg.unlockConsoleCommands, s, "UnlockConsoleCommands");

		findOWParam(&structs::cfg.maxBodSize, s, "MaxBodyguardSize");

		readStringInQuotes(&ls, s, "LegioString");
		readStringInQuotes(&structs::cfg.langP, s, "Lang");
	}
	f2.close();
	structs::cfg.langP= structs::cfg.modPatch+"\\youneuoy_Data\\localisation\\" + structs::cfg.langP;

	if(ls.empty())
		ls= "Legio ";
	structs::cfg.legioString = new char[ls.length() + 1];
	memcpy(structs::cfg.legioString, ls.c_str(), ls.length() + 1);
	writeValues();
}

void writeValues()
{
	Write((void*)&structs::cfg.legioString, structs::gameDataOffsets.legioStringOffset, 4);

	if (structs::cfg.histBattleFix)
	{
		unsigned char disSold[2] = { 0x90, 0x90 };
		DWORD nPtr;
		DWORD nbPtr;
		

		if (structs::cfg.gamever == 2)
		{

			nPtr = 0x008eebbd;
			nbPtr = 0x008EEBB5;

		}
		else
		{
			nPtr = 0x008ee13d;
			nbPtr = 0x008ee135;

		}

		Write(disSold, nPtr, 2);
		Write(disSold, nbPtr, 2);

	}

	if (structs::cfg.DCI)
	{
		MemWork* mem = new MemWork();
		DCICrashHard* dci = new DCICrashHard(mem, (LPVOID)nullptr, structs::cfg.gamever);
		dci->SetlDCICode();
		dci->Enable();
	}

	DWORD bodyguardSizeOffset1;
	DWORD bodyguardSizeOffset2;
	if (structs::cfg.gamever == 2)
	{
		bodyguardSizeOffset1 = 0x008ec815;
		bodyguardSizeOffset2 = 0x008ec81a;
	}
	else
	{
		bodyguardSizeOffset1 = 0x008ebd95;
		bodyguardSizeOffset2 = 0x008ebd9a;
	}

	Write(&structs::cfg.maxBodSize, 0x008ec815+2, 1);
	Write(&structs::cfg.maxBodSize, 0x008ec81a+1, 1);

}


void findOWParam(int* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0]!=';')
	{
		int pos = s.find_first_of("0123456789");
		int endpos = s.find_first_not_of("0123456789", pos + 1);
		string result = s.substr(pos, endpos - pos);
		*arg = stoi(result);
	}
}
void replaceAll(string& s, const string& search, const string& replace) {
	for (size_t pos = 0; ; pos += replace.length()) {

		pos = s.find(search, pos);
		if (pos == string::npos) break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

void readStringInQuotes(string* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0] != ';')
	{
		size_t pos = s.find_first_of("\"");
		size_t endpos = s.find_last_of("\"");
		if (pos == string::npos || endpos == string::npos || pos == endpos) return;
		pos++;
		*arg = s.substr(pos, endpos - pos);
	}
	string f = "\\n";
	string r = "\n";
	replaceAll(*arg,f,r);
}

template <typename param_type>
void findAnyParam(param_type* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0] != ';')
	{
		float t;
		int pos = s.find_first_of("0123456789");
		int endpos = s.find_first_not_of("0123456789", pos + 1);
		string result = s.substr(pos, endpos - pos);
		*arg = stoi(result);
	}
}
template <typename param_type>
void findFloatParam(param_type* arg, string s, string param) {
	if (s.find(param) != string::npos && s[0] != ';')
	{
		float t;
		int pos = s.find_first_of("0123456789.");
		int endpos = s.find_first_not_of("0123456789.", pos + 1);
		string result = s.substr(pos, endpos - pos);
		*arg = stof(result);
	}
}


void limitsFile(MemWork* mem)
{

	string s = structs::cfg.modPatch + "\\limits.youneuoycfg";
	ifstream f1(s);
	while (f1.good())
	{
		getline(f1, s);

		findOWParam(&owW::cfg.religionLimit, s, "Religion_Limit");

		findOWParam(&owW::cfg.ancillariesLimit, s, "Ancillaries_Limit");

		findOWParam(&owW::cfg.lockSizeOfUnit, s, "Lock_Size_Of_Unit");
		findOWParam(&owW::cfg.sizeOfUnit, s, "Size_Of_Unit");

		findAnyParam(&owW::cfg.minSoldiersEdu, s, "Min_Soldiers_In_Edu");
		findAnyParam(&owW::cfg.maxSoldiersEdu, s, "Max_Soldiers_In_Edu");

		findFloatParam(&owW::cfg.battlefieldMapSizeX, s, "Battlefield_Map_Size_X");
		findFloatParam(&owW::cfg.battlefieldMapSizeY, s, "Battlefield_Map_Size_Y");

		findFloatParam(&owW::cfg.siegeRamCost, s, "Siege_Ram_Cost");
		findFloatParam(&owW::cfg.siegeLadderCost, s, "Siege_Ladder_Cost");
		findFloatParam(&owW::cfg.siegeTowerCost, s, "Siege_Tower_Cost");
	}
	f1.close();




	sizeOfBattleField* sizeField = new sizeOfBattleField(mem, structs::cfg.gamever, owW::cfg.battlefieldMapSizeX, owW::cfg.battlefieldMapSizeY);

	sizeField->SetlSizeCode();
	sizeField->Enable();  

	if (structs::cfg.gamever == 1)
	{
		doDisk();
	}
	else if (structs::cfg.gamever == 2)
	{
		doSteam();
	}



	vector<DWORD> adresses;

	if (structs::cfg.gamever == 1)//kingdoms
	{
		adresses =
		{
			0x1655BB0,
			0x1655BB4,
			0x1655BB8
		};
	}
	else if (structs::cfg.gamever == 2)//steam
	{
		adresses =
		{
			0x160DCC8,
			0x160DCCC,
			0x160DCD0
		};
	}
	Write(&owW::cfg.siegeRamCost, adresses[0], 4);
	Write(&owW::cfg.siegeLadderCost, adresses[1],4);
	Write(&owW::cfg.siegeTowerCost, adresses[2],4);
}

void doDisk()
{
	DWORD sizeOffset = 0x016818FC;
	DWORD religionOffset = 0x00411C0E;
	DWORD ancillariesOffset = 0x005A57CD;

	UINT32 one = 0;
	UINT32 two = 0;
	UINT32 three = 0;

	if (owW::cfg.lockSizeOfUnit)
	{
		Write(&owW::cfg.sizeOfUnit, sizeOffset,4);
		//WriteProcessMemory(hMTW2, (LPVOID)sizeOffset, &cfg.sizeOfUnit, 4, 0);
		writeRet(0x00C71C00);
		writeRet(0x00C71B80);
	}

	Write(&owW::cfg.religionLimit, religionOffset, 1);


	Write(&owW::cfg.ancillariesLimit, ancillariesOffset, 1);


	doCount(0x008ef381);

}

void doSteam()
{
	DWORD sizeOffset = 0x01639F4C;
	DWORD religionOffset = 0x00411E0E;
	DWORD ancillariesOffset = 0x005A5CAD;
	DWORD tactmapSizeOffset = 0x012f0e70;
	DWORD tactmapSizeSiegeOffset = 0x012fe3ac;
	UINT32 one = 0;
	UINT32 two = 0;
	UINT32 three = 0;
	float four = 0;
	float five = 0;
	if (owW::cfg.lockSizeOfUnit)
	{
		Write(&owW::cfg.sizeOfUnit, sizeOffset, 4);
		writeRet(0x00C6C000);
		writeRet(0x00C6C080);
	}

	Write(&owW::cfg.religionLimit, religionOffset, 1);


	Write(&owW::cfg.ancillariesLimit, ancillariesOffset, 1);

	doCount(0x008efe01);
}

void doCount(DWORD code)
{
	code += 0x82C;
	UINT32 one = 0;
	UINT32 two = 0;

	one = owW::cfg.minSoldiersEdu;
	two = owW::cfg.maxSoldiersEdu;
	Write(&one, code,2);

	code += 6;
	Write(&two, code, 2);

}

void writeRet(DWORD code)
{
	UINT32 ret = 0xC3;
	Write(&ret,code,1);
}
