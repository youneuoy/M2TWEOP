#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 
#include <thread>
#include "overwritingValues.h"
#include "keyboardFunctions.h"

#include "startFortsModelsPatch.h"
using namespace std;
class stratModelsPatch
{
public:
	static void WINAPI readModel();

	static void WINAPI readModelsChFile();

	static void writeModelsFile();

	static void runStratModelsChangeThread();

	static void WINAPI disableChecker();

	static void WINAPI enableChecker();

	static void runWaitModelPointer(structs::modelStratStat* mod);




	static bool modelsReaded;

	static void WINAPI unicalStratModsRead();
private:


	static void modelsChangeThread(DWORD sleepTime);

	static void WINAPI waitModelPointer(structs::modelStratStat* mod);

	static void readCfgFile();




	struct modelChangeS {
		int x;
		int y;
		string path;
	};

	static vector<stratResMod*> changedModels;

	static vector<modelChangeS*> modelsChangeList;


	static struct  stratModCfg {
		bool checkNeed = false;

		int waitModelPointerTime = 500;
		int waitModelsChangeThreadStart = 500;
		int numberModelsChangeThreadStart = 0;
	}stModCfg;


};

