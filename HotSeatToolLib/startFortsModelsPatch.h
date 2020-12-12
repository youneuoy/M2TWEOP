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
class startFortsModelsPatch
{
public:
	struct fortModelChangeS {
		int x=0;
		int y=0;
		string centerPath;
		string wallsPath;
	};

	struct fortStratModel
	{
		UINT32 index = 0;

		string centerPath;
		string wallsPath;
		stratFortMod* stratFortModel = nullptr;
	};


	static struct stratFortsDataS
	{
		bool checkNeed = false;

		vector<stratFortMod*> changedFortModels;
		vector<fortModelChangeS*> fortsModelsChangeList;

		vector<fortStratModel*> fortsModelsList;
	}dataS;

	static void setFortModel(fortModelChangeS* modelCh, fortStruct* fort);

	static void checkAndChangeModels();

	//read models list
	static void readModelsFile();
	//read models files
	static void WINAPI readCasModels();

	static void disableChecker();
	static void enableChecker();


	static model_Rigid* readModel(string* path);

};