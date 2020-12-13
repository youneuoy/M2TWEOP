#include "startFortsModelsPatch.h"
startFortsModelsPatch::stratFortsDataS startFortsModelsPatch::dataS;

void startFortsModelsPatch::setFortModel(fortModelChangeS* modelCh, fortStruct* fort)
{
	for (fortStratModel* model : dataS.fortsModelsList)
	{
		if (model->centerPath != modelCh->centerPath
			|| model->wallsPath != modelCh->wallsPath
			) continue;

		if (model->stratFortModel == nullptr)continue;


		for (stratFortMod* modelChanged : dataS.changedFortModels)
		{
			if (modelChanged == fort->stratModel)return;
		}
		
		ofstream f1("logs\\stratFortsModelsChangeList.youneuoylog", ios::app);


		stratFortMod* newMods = new stratFortMod[33];
		memset(newMods, 0, sizeof(stratFortMod) * 33);

		f1 << "wallsModel RAM adress here:" << hex << &newMods->centerModel << endl;
		newMods->centerModel = model->stratFortModel->centerModel;

		newMods->centerModelPath = model->stratFortModel->centerModelPath;
		newMods->centerModelPathCrypt = model->stratFortModel->centerModelPathCrypt;

		newMods->wallsModel = model->stratFortModel->wallsModel;

		newMods->wallsModelPath = model->stratFortModel->wallsModelPath;
		newMods->wallsModelPathCrypt = model->stratFortModel->wallsModelPathCrypt;

		/*for (int i = 0; i <= 31; i++)
		{
			f1 << "wallsModel RAM adress here:" << hex << &newMods[i].centerModel << endl;
			newMods[i].centerModel = model->stratFortModel->centerModel;

			newMods[i].centerModelPath = model->stratFortModel->centerModelPath;
			newMods[i].centerModelPathCrypt = model->stratFortModel->centerModelPathCrypt;

			newMods[i].wallsModel = model->stratFortModel->wallsModel;

			newMods[i].wallsModelPath = model->stratFortModel->wallsModelPath;
			newMods[i].wallsModelPathCrypt = model->stratFortModel->wallsModelPathCrypt;

		}*/

		dataS.changedFortModels.push_back(newMods);
		fort->stratModel = newMods;
		f1.close();
	}
}

void __stdcall startFortsModelsPatch::checkAndChangeModels()
{
	if (dataS.checkNeed == false)return;

	UINT32 numFac = FastFuncts::getFactionsCount();

	factionStruct** listFac = FastFuncts::getFactionsList();


	for (UINT32 i = 0; i < numFac; i++)
	{
		UINT32 fortsNum = listFac[i]->fortsNum;

		for (int j = 0; j < fortsNum; j++)
		{
			for (fortModelChangeS* modCh : dataS.fortsModelsChangeList)
			{
				if (listFac[i]->forts[j]->xCoord != modCh->x
					|| listFac[i]->forts[j]->yCoord != modCh->y
					) continue;
				setFortModel(modCh, listFac[i]->forts[j]);
			}
		}
	}
}

void startFortsModelsPatch::readModelsFile()
{
	ofstream f1("logs\\stratFortsModelsChangeList.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\stratFortsModelsChangeList.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t != 501) { continue; }
		else
		{
			startFortsModelsPatch::fortModelChangeS* mdlCh = new startFortsModelsPatch::fortModelChangeS();

			getline(f2, f);
			mdlCh->x = stoi(f);

			getline(f2, f);
			mdlCh->y = stoi(f);

			getline(f2, f);
			readStringInQuotes(&mdlCh->centerPath, f, "Center_path");

			getline(f2, f);
			readStringInQuotes(&mdlCh->wallsPath, f, "Walls_path");

			startFortsModelsPatch::dataS.fortsModelsChangeList.push_back(mdlCh);
		}
	}
	f2.close();

	f1 << "Log, readed params:" << endl;

	for (startFortsModelsPatch::fortModelChangeS* mdl : startFortsModelsPatch::dataS.fortsModelsChangeList)
	{
		f1 << "Model change coords:" << endl;
		f1 << "x= " << mdl->x << ", y=" << mdl->y << endl;
		f1 << "path to changed model center cas file:" << endl;
		f1 << mdl->centerPath << endl;
		f1 << "path to changed model walls cas file:" << endl;
		f1 << mdl->wallsPath << endl;
	}
	f1 << "end" << endl;
	f1.close();
}

void __stdcall startFortsModelsPatch::readCasModels()
{
	dataS.changedFortModels.clear();
	dataS.fortsModelsList.clear();

	ofstream f1("logs\\stratFortsModelsChangeList.youneuoylog", ios::app);

	for (startFortsModelsPatch::fortModelChangeS* mdl : startFortsModelsPatch::dataS.fortsModelsChangeList)
	{
		fortStratModel* mod = new fortStratModel();

		f1 << "Model:" << endl;

		mod->index = dataS.fortsModelsList.size();
		mod->centerPath = mdl->centerPath;
		mod->wallsPath = mdl->wallsPath;

		mod->stratFortModel = new stratFortMod();

		f1 << "Index:" << mod->index << endl;
		f1 << "centerPath:" << mod->centerPath << endl;
		f1 << "wallsPath:" << mod->wallsPath << endl;
		f1 << "Pointer to RAM adress:" << hex << mod->stratFortModel << endl;


		mod->stratFortModel->centerModel = readModel(&mod->centerPath);

		
		char* centerModelPath = new char[mod->centerPath.length() + 1];

		memcpy(centerModelPath, mod->centerPath.c_str(), mod->centerPath.length() + 1);
		UINT32 pathPointer = (UINT32)&mod->stratFortModel->centerModelPath;
		UINT32 functionOffset = structs::gameCodeOffsets.setStringAndCryptOffset;
		_asm {
			push centerModelPath
			mov ecx, pathPointer
			mov eax, functionOffset
			call eax
		}


		f1 << "centerModel RAM adress here:" << hex << mod->stratFortModel->centerModel << endl;


		mod->stratFortModel->wallsModel = readModel(&mod->wallsPath);

		char* wallsModelPath = new char[mod->wallsPath.length() + 1];

		memcpy(wallsModelPath, mod->wallsPath.c_str(), mod->wallsPath.length() + 1);
		 pathPointer = (UINT32)&mod->stratFortModel->wallsModelPath;
		_asm {
			push wallsModelPath
			mov ecx, pathPointer
			mov eax, functionOffset
			call eax
		}


		f1 << "wallsModel RAM adress here:" << hex << mod->stratFortModel->wallsModel << endl;

		dataS.fortsModelsList.push_back(mod);
	}

	f1.close();
}

void startFortsModelsPatch::disableChecker()
{
	dataS.checkNeed = false;
}

void startFortsModelsPatch::enableChecker()
{
	dataS.checkNeed = true;
}

model_Rigid* startFortsModelsPatch::readModel(string* path)
{
	DWORD adr = structs::gameCodeOffsets.loadStratCasModelOffset;
	char* pSArg = _strdup(path->c_str());

	DWORD res = 0;
	_asm {
		push 0x1
		push 0x1
		push 0x1
		push 0x2
		push 0x97c
		push pSArg

		mov eax, [adr]
		call eax
		add esp, 0x18
		mov[res], eax
	}

	int* modsNum = reinterpret_cast<int*>(structs::gameDataOffsets.statStratModelsListOffset + 0x8dc);

	model_Rigid** modRig = reinterpret_cast<model_Rigid**>(structs::gameDataOffsets.statStratModelsListOffset);
	modRig[*modsNum] = nullptr;

	*modsNum = *modsNum - 1;

	return reinterpret_cast<model_Rigid*>(res);
}
