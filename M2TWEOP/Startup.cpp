#include "Startup.h"


Startup::config Startup::cfg;
Startup::cfgStructType Startup::modCfg;
Startup::gameInfoS Startup::gameInfo;
Startup::cfgStructLim Startup::cfgLimits;
Startup::gameCfg Startup::gameConfig;
void Startup::loadParams()
{
	string cfgName = "";

	string startType = "";

	string volume = "";

	string s;
	ifstream f1;
	f1.open("startup.youneuoycfg");

	string antialias = "";
	string borderless = "";
	string autoRes = "";
	string applyCfg = "";
	string justStartMod = "";
	while (f1.good())
	{
		getline(f1, s);

		Params::readStringInQuotes(&cfgName, s, "Config_file_name");

		Params::readStringInQuotes(&startType, s, "Start_type");

		Params::readStringInQuotes(&volume, s, "Music_Volume");

		Params::readStringInQuotes(&antialias, s, "Antialiasing");
		Params::readStringInQuotes(&borderless, s, "Borderless");
		Params::readStringInQuotes(&autoRes, s, "Auto_resolution");
		Params::readStringInQuotes(&applyCfg, s, "Apply_gameCFG");

		Params::readStringInQuotes(&justStartMod, s, "JustStartMod");

	}
	if (startType == "")
	{
		startType = "0";
	}
	if (cfgName == "")
	{
		cfgName = "enter_cfg_name";
	}
	if (volume == "")
	{
		volume = "0";
	}
	if (justStartMod == "")
	{
		justStartMod = "0";
	}

	Startup::cfg.startTypeB = stoi(startType);
	Startup::cfg.musicVolume = stoi(volume);
	strcpy(Startup::cfg.modCFGName, cfgName.c_str());
	Startup::cfg.justStartMod = stoi(justStartMod);

	if (antialias != "")
	{
		Startup::gameConfig.antialiasing = stoi(antialias);
	}

	if (borderless != "")
	{
		Startup::gameConfig.borderlWindow = stoi(borderless);
	}

	if (antialias != "")
	{
		Startup::gameConfig.destkopResolution = stoi(autoRes);
	}

	if (antialias != "")
	{
		Startup::gameConfig.applyGameConfig = stoi(applyCfg);
	}


	f1.close();

	f1.open("modConfig.youneuoycfg");

	string leg;
	string lang;
	while (f1.good())
	{
		getline(f1, s);
		//Params::findOWParam(Startup::modCfg.fullLogging, s, "FullLoggingEnabled");
		Params::findAnyParam(&Startup::modCfg.fullLoggingB, s, "FullLoggingEnabled");
		//Params::findOWParam(Startup::modCfg.unlockChangeFaction, s, "UnlockConsoleChangeFaction");
		Params::findAnyParam(&Startup::modCfg.unlockChangeFactionB, s, "UnlockConsoleChangeFaction");
		//Params::findOWParam(Startup::modCfg.bersPatch, s, "CorrectionOfBerserkers");
		Params::findAnyParam(&Startup::modCfg.bersPatchB, s, "CorrectionOfBerserkers");
		//Params::findOWParam(Startup::modCfg.histBattleFix, s, "HistoryBattlesSoldiersNumberFix");
		Params::findAnyParam(&Startup::modCfg.histBattleFixB, s, "HistoryBattlesSoldiersNumberFix");
		//Params::findOWParam(Startup::modCfg.DCI, s, "DCI");
		Params::findAnyParam(&Startup::modCfg.DCIB, s, "DCI");
		//Params::findOWParam(Startup::modCfg.spawnArmyCoords, s, "SpawnArmyCoordsPatch");
		Params::findAnyParam(&Startup::modCfg.spawnArmyCoordsB, s, "SpawnArmyCoordsPatch");
		//Params::findOWParam(Startup::modCfg.characterUIMenus, s, "CharacterUIMenus");
		Params::findAnyParam(&Startup::modCfg.characterUIMenusB, s, "CharacterUIMenus");

		Params::findAnyParam(&Startup::modCfg.unlockConsoleCommands, s, "UnlockConsoleCommands");

		Params::findOWParam(Startup::modCfg.maxBodSize, s, "MaxBodyguardSize");

		Params::readStringInQuotes(&leg, s, "LegioString");
		Params::readStringInQuotes(&lang, s, "Lang");
	}

	f1.close();


	f1.open("limits.youneuoycfg");
	char battleSizeX[5] = "1000";
	char battleSizeY[5] = "1000";
	while (f1.good())
	{
		getline(f1, s);
		Params::findOWParam(Startup::cfgLimits.Religion_Limit, s, "Religion_Limit");
		Params::findOWParam(Startup::cfgLimits.Ancillaries_Limit, s, "Ancillaries_Limit");
		Params::findOWParam(Startup::cfgLimits.Lock_Size_Of_Unit, s, "Lock_Size_Of_Unit");
		Params::findOWParam(Startup::cfgLimits.Size_Of_Unit, s, "Size_Of_Unit");
		Params::findOWParam(Startup::cfgLimits.Min_Soldiers_In_Edu, s, "Min_Soldiers_In_Edu");
		Params::findOWParam(Startup::cfgLimits.Max_Soldiers_In_Edu, s, "Max_Soldiers_In_Edu");
		Params::findOWParam(battleSizeX, s, "Battlefield_Map_Size_X");
		Params::findOWParam(battleSizeY, s, "Battlefield_Map_Size_Y");
		Params::findOWParam(Startup::cfgLimits.Siege_Ram_Cost, s, "Siege_Ram_Cost");
		Params::findOWParam(Startup::cfgLimits.Siege_Ladder_Cost, s, "Siege_Ladder_Cost");
		Params::findOWParam(Startup::cfgLimits.Siege_Tower_Cost, s, "Siege_Tower_Cost");
	}

	f1.close();
	Startup::cfgLimits.Battlefield_Map_Size_X = stoi(battleSizeX);
	Startup::cfgLimits.Battlefield_Map_Size_Y = stoi(battleSizeY);

	strcpy(Startup::modCfg.legioString, leg.c_str());
	strcpy(Startup::modCfg.langP, lang.c_str());

	/*Startup::modCfg.fullLoggingB = stoi(Startup::modCfg.fullLogging);
	Startup::modCfg.unlockChangeFactionB = stoi(Startup::modCfg.unlockChangeFaction);
	Startup::modCfg.bersPatchB = stoi(Startup::modCfg.bersPatch);
	Startup::modCfg.histBattleFixB = stoi(Startup::modCfg.histBattleFix);
	Startup::modCfg.DCIB = stoi(Startup::modCfg.DCI);
	Startup::modCfg.characterUIMenusB = stoi(Startup::modCfg.characterUIMenus);
	Startup::modCfg.spawnArmyCoordsB = stoi(Startup::modCfg.spawnArmyCoords);*/

}

void Startup::startP()
{
	loadParams();
	music::play(Startup::cfg.musicVolume);
	getGameInfo();
}

void Startup::writeStartup()
{
	ofstream f1;
	f1.open("startup.youneuoycfg");

	f1 << "startup.youneuoycfg file, generated by M2TWEOP!" << endl << endl;

	f1 << ";" << Startup::cfg.modCFGNameTip << endl;
	f1 << "Config_file_name = \"" << Startup::cfg.modCFGName << "\"" << endl << endl;

	f1 << ";" << Startup::cfg.startTypeTip << endl;
	f1 << "Start_type = \"" << Startup::cfg.startTypeB << "\"" << endl << endl;

	f1 << ";" << Startup::cfg.musicVolumeTip << endl;
	f1 << "Music_Volume = \"" << Startup::cfg.musicVolume << "\"" << endl << endl;

	f1 << ";" << Startup::gameConfig.antialiasingTip << endl;
	f1 << "Antialiasing = \"" << Startup::gameConfig.antialiasing << "\"" << endl << endl;

	f1 << ";" << Startup::gameConfig.borderlWindowTip << endl;
	f1 << "Borderless = \"" << Startup::gameConfig.borderlWindow << "\"" << endl << endl;

	f1 << ";" << Startup::gameConfig.destkopResolutionTip << endl;
	f1 << "Auto_resolution = \"" << Startup::gameConfig.destkopResolution << "\"" << endl << endl;

	f1 << ";" << Startup::gameConfig.applyGameConfigTip << endl;
	f1 << "Apply_gameCFG = \"" << Startup::gameConfig.applyGameConfig << "\"" << endl << endl;

	f1 << ";" << Startup::cfg.justStartModTip << endl;
	f1 << "JustStartMod = \"" << Startup::cfg.justStartMod << "\"" << endl << endl;

	f1.close();
}

void Startup::writeModCfg()
{
	ofstream f1;
	f1.open("modConfig.youneuoycfg");

	f1 << "Generated by M2TWEOP!" << endl << endl;

	f1 << ";comments only in start of strings." << endl << endl;


	f1 << Startup::modCfg.langPTip << endl;
	f1 << "Lang = \"" << Startup::modCfg.langP << "\"" << endl << endl;

	f1 << Startup::modCfg.fullLoggingTip << endl;
	f1 << "FullLoggingEnabled = " << Startup::modCfg.fullLoggingB << endl << endl;

	f1 << Startup::modCfg.unlockChangeFactionTip << endl;
	f1 << "UnlockConsoleChangeFaction = " << Startup::modCfg.unlockChangeFactionB << endl << endl;

	f1 << Startup::modCfg.bersPatchTip << endl;
	f1 << "CorrectionOfBerserkers = " << Startup::modCfg.bersPatchB << endl << endl;

	f1 << Startup::modCfg.histBattleFixTip << endl;
	f1 << "HistoryBattlesSoldiersNumberFix = " << Startup::modCfg.histBattleFixB << endl << endl;

	f1 << Startup::modCfg.DCITip << endl;
	f1 << "DCI = " << Startup::modCfg.DCIB << endl << endl;

	f1 << Startup::modCfg.characterUIMenusTip << endl;
	f1 << "CharacterUIMenus = " << Startup::modCfg.characterUIMenusB << endl << endl;

	f1 << Startup::modCfg.spawnArmyCoordsTip << endl;
	f1 << "SpawnArmyCoordsPatch = " << Startup::modCfg.spawnArmyCoordsB << endl << endl;

	f1 << Startup::modCfg.unlockConsoleCommandsTip << endl;
	f1 << "UnlockConsoleCommands = " << Startup::modCfg.unlockConsoleCommands << endl << endl;

	f1 << Startup::modCfg.maxBodSizeTip << endl;
	f1 << "MaxBodyguardSize = " << Startup::modCfg.maxBodSize << endl << endl;

	f1 << Startup::modCfg.legioStringTip << endl;
	f1 << "LegioString = \"" << Startup::modCfg.legioString << "\"" << endl << endl;

	f1.close();
}

void Startup::writeLimits()
{
	ofstream f1;
	f1.open("limits.youneuoycfg");

	f1 << ";Generated by M2TWEOP!" << endl << endl;

	f1 << ";comments only in start of strings." << endl << endl;

	f1 << Startup::cfgLimits.Religion_LimitTip << endl;
	f1 << "Religion_Limit = " << Startup::cfgLimits.Religion_Limit << endl << endl;

	f1 << Startup::cfgLimits.Ancillaries_LimitTip << endl;
	f1 << "Ancillaries_Limit = " << Startup::cfgLimits.Ancillaries_Limit << endl << endl;

	f1 << Startup::cfgLimits.Lock_Size_Of_UnitTip << endl;
	f1 << "Lock_Size_Of_Unit = " << Startup::cfgLimits.Lock_Size_Of_Unit << endl << endl;

	f1 << Startup::cfgLimits.Size_Of_UnitTip << endl;
	f1 << "Size_Of_Unit = " << Startup::cfgLimits.Size_Of_Unit << endl << endl;

	f1 << Startup::cfgLimits.Min_Soldiers_In_EduTip << endl;
	f1 << "Min_Soldiers_In_Edu = " << Startup::cfgLimits.Min_Soldiers_In_Edu << endl << endl;

	f1 << Startup::cfgLimits.Max_Soldiers_In_EduTip << endl;
	f1 << "Max_Soldiers_In_Edu = " << Startup::cfgLimits.Max_Soldiers_In_Edu << endl << endl;

	f1 << Startup::cfgLimits.Battlefield_Map_Size_XTip << endl;
	f1 << "Battlefield_Map_Size_X = " << Startup::cfgLimits.Battlefield_Map_Size_X << endl << endl;

	f1 << Startup::cfgLimits.Battlefield_Map_Size_YTip << endl;
	f1 << "Battlefield_Map_Size_Y = " << Startup::cfgLimits.Battlefield_Map_Size_Y << endl << endl;

	f1 << Startup::cfgLimits.Siege_Ram_CostTip << endl;
	f1 << "Siege_Ram_Cost = " << Startup::cfgLimits.Siege_Ram_Cost << endl << endl;

	f1 << Startup::cfgLimits.Siege_Ladder_CostTip << endl;
	f1 << "Siege_Ladder_Cost = " << Startup::cfgLimits.Siege_Ladder_Cost << endl << endl;

	f1 << Startup::cfgLimits.Siege_Tower_CostTip << endl;
	f1 << "Siege_Tower_Cost = " << Startup::cfgLimits.Siege_Tower_Cost << endl << endl;

	f1.close();
}

int Startup::getGameInfo()
{
	CHAR currentPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, currentPath, MAX_PATH);

	PathRemoveFileSpecA(currentPath);
	Startup::gameInfo.currentMod = new char[strlen(currentPath) + 1];
	strcpy(Startup::gameInfo.currentMod, currentPath);


	int ver = 0;
	string mtw = findMTW(currentPath, &ver);

	if (mtw != "")
	{
		Startup::gameInfo.filePatch = new char[mtw.length() + 1];

		strcpy(Startup::gameInfo.filePatch, mtw.c_str());

		ver = getVersion(mtw.c_str());
	}
	else
	{
		ver = 0;
	}
	if (ver == 1)
	{
		Startup::gameInfo.ver = "Disk version, kingdoms(1.5)";
		Startup::gameInfo.v = 1500;
	}
	else if (ver == 2)
	{
		Startup::gameInfo.ver = "Steam version, definitive edition(1.52)";
		Startup::gameInfo.v = 1520;
	}
	else if (ver == 0)
	{
		Startup::gameInfo.ver = "Unknown version, not good";
	}


	createModInfoFile();
	return 1;
}

int Startup::runMod()
{
	Startup::writeStartup();
	Startup::writeGameCfg(1);

	//exe file
	string s = Startup::gameInfo.filePatch;
	string ws;
	ws.assign(s.begin(), s.end());

	string wsCmd;

	wsCmd = "@";
	string tmp;
	s = Startup::gameInfo.currentMod;
	tmp.assign(s.begin(), s.end());
	string search = "mods\\";
	size_t pos = tmp.find(search);
	if (pos == string::npos) return 0;
	wsCmd = wsCmd + tmp.substr(pos) + "\\";

	s = Startup::cfg.modCFGName;
	tmp.assign(s.begin(), s.end());
	wsCmd = wsCmd + tmp;


	//starting directory
	string stdir = ws;

	PathRemoveFileSpecA(&stdir.front());
	stdir.resize(strlen(stdir.data()));
	stdir.shrink_to_fit();



	string d3dS = stdir;
	d3dS += "\\d3d9.dll";
	bool sucess=DeleteFile(d3dS.c_str());

	string wrapd3dS = Startup::gameInfo.currentMod;
	wrapd3dS += "\\d3d9dllWrapper.dll";
	if (CopyFile(wrapd3dS.c_str(), d3dS.c_str(), FALSE)==false)
	{
		MessageBoxA(NULL, "Cannot run M2TWEOP, d3d9.dll replasing error! Try to delete d3d9.dll in game folder. ", "ERROR", MB_OK);
		exit(0);
	}


	UINT32 res = (UINT)ShellExecuteA(
		NULL,
		NULL,
		&ws[0],
		&wsCmd[0],
		stdir.c_str(),
		SW_SHOW);

	return res;
}

int Startup::runVanilla()
{
	Startup::writeStartup();
	Startup::writeGameCfg(0);
	//exe file
	string s = Startup::gameInfo.filePatch;
	string ws;
	ws.assign(s.begin(), s.end());

	//starting directory
	string stdir = ws;

	PathRemoveFileSpecA(&stdir.front());
	stdir.resize(strlen(stdir.data()));
	stdir.shrink_to_fit();

	UINT32 res = (UINT)ShellExecuteA(
		NULL,
		NULL,
		&ws[0],
		NULL,
		stdir.c_str(),
		SW_SHOW);

	return res;
}

void Startup::writeGameCfg(int ifmod)
{
	if (Startup::gameConfig.applyGameConfig == false)return;
	string borderless = "borderless_window = ";
	borderless = borderless + to_string(Startup::gameConfig.borderlWindow);
	string windowed = "windowed = ";
	windowed = windowed + to_string(Startup::gameConfig.borderlWindow);

	string antialias = "antialiasing = ";
	int lvl = (int)pow(2, Startup::gameConfig.antialiasing);
	if (lvl == 1)lvl = 0;
	antialias = antialias + to_string(lvl);

	string battleRes = "battle_resolution = ";
	string campRes = "campaign_resolution = ";
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	battleRes = battleRes + to_string(x) + " " + to_string(y);
	campRes = campRes + to_string(x) + " " + to_string(y);

	string cfg;
	if (ifmod)
	{
		cfg = Startup::gameInfo.currentMod;
		cfg = cfg + "\\" + Startup::cfg.modCFGName;
	}
	else {
		string s = Startup::gameInfo.filePatch;
		string ws;
		ws.assign(s.begin(), s.end());

		cfg = ws;

		PathRemoveFileSpecA(&cfg.front());
		cfg.resize(strlen(cfg.data()));
		cfg.shrink_to_fit();

		cfg = cfg + "\\medieval2.preference.cfg";
	}
	string backName = cfg + "backup";
	remove(backName.c_str());
	if (rename(cfg.c_str(), backName.c_str()))
	{
		MessageBoxW(NULL, L"Error while backuping config file! Try to disable new display settings.", L"Something goes wrong!", NULL);
		return;
	}

	string s;
	ifstream f1(backName);
	ofstream f2(cfg);
	while (f1.good()) {
		getline(f1, s);

		if (s == "[video]")
		{
			f2 << s << endl;
			f2 << borderless << endl;
			f2 << windowed << endl;
			f2 << antialias << endl;
			if (Startup::gameConfig.destkopResolution == true)
			{
				f2 << battleRes << endl;
				f2 << campRes << endl;
			}
			continue;
		}
		if (s.find("borderless_window") != string::npos
			||
			s.find("windowed") != string::npos
			||
			s.find("antialiasing") != string::npos
			||
			(s.find("battle_resolution") != string::npos&& Startup::gameConfig.destkopResolution == true)
			||
			(s.find("campaign_resolution") != string::npos && Startup::gameConfig.destkopResolution == true)
			)
			continue;

		f2 << s << endl;

	}
	f1.close();
	f2.close();
}

string Startup::findMTW(string s, int* ver)
{
	vector<string> res;
	res = findFile(s, "kingdoms.exe");
	if (res.size() > 0)
	{
		*ver = 1;
		return s + "\\" + res[0];
	}
	res = findFile(s, "medieval2.exe");

	if (res.size() > 0)
	{
		*ver = 2;
		return  s + "\\" + res[0];
	}

	s = Params::getParrentDir(s);
	s = Params::getParrentDir(s);

	res = findFile(s, "kingdoms.exe");
	if (res.size() > 0)
	{
		*ver = 1;
		return  s + "\\" + res[0];
	}
	res = findFile(s, "medieval2.exe");
	if (res.size() > 0)
	{
		*ver = 2;
		return  s + "\\" + res[0];
	}

	return "Nothing finded";
}

vector<string> Startup::findFile(string folder, string fileName)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				if (fd.cFileName == fileName)
					names.push_back(fd.cFileName);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void Startup::createModInfoFile()
{
	string s = Startup::gameInfo.filePatch;

	PathRemoveFileSpecA(&s[0]);
	s.resize(strlen(s.data()));
	s.shrink_to_fit();

	string f = s;
	f = f + "\\runningMod.youneuoycfg";
	ofstream f1(f);

	string t = to_string(Startup::gameInfo.v);
	f1 << t << endl;

	f1 << Startup::gameInfo.currentMod << endl;

	f1.close();
}


int Startup::getVersion(LPCSTR file)
{
	ifstream f1(file, ios::binary);

	DWORD checkOffset = 0x00a04f4c - 0x00400000;
	DWORD read;
	int ver = 0;

	f1.seekg(checkOffset);
	f1.read(reinterpret_cast<char*>(&read), 4);

	f1.close();


	DWORD steam = 0x7ce239e8;
	DWORD disk = 0xb60f0350;
	if (read == steam)
		ver = 2;
	else if (read == disk)
		ver = 1;

	return ver;
}


