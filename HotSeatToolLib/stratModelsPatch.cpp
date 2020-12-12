#include "stratModelsPatch.h"


stratModelsPatch::stratModCfg stratModelsPatch::stModCfg;
bool stratModelsPatch::modelsReaded=false;

vector<stratModelsPatch::modelChangeS*> stratModelsPatch::modelsChangeList;

vector<stratResMod*> stratModelsPatch::changedModels;

void WINAPI stratModelsPatch::readModel()
{
	/*char* patch;
	_asm {
		mov patch, edi;
	}
	if (!patch)return;

	DWORD modsNum=0;
	Read(structs::gameDataOffsets.statStratModelsListOffset+0x8dc, &modsNum);

	if (!modsNum)
	{
		structs::modelsStrat.clear();
	}

	string s = readString((DWORD)patch);

	structs::modelStratStat* mod = new structs::modelStratStat();

	mod->index = structs::modelsStrat.size();
	mod->patch = s;

	structs::modelsStrat.push_back(mod);
	runWaitModelPointer(structs::modelsStrat[mod->index]);*/
}

void __stdcall stratModelsPatch::readModelsChFile()
{
	ofstream f1("logs\\stratModelsChangeList.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\stratModelsChangeList.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t != 501) { continue; }
		else
		{
			stratModelsPatch::modelChangeS* mdl = new stratModelsPatch::modelChangeS();

			getline(f2, f);
			mdl->x = stoi(f);

			getline(f2, f);
			mdl->y = stoi(f);

			getline(f2, f);
			readStringInQuotes(&mdl->path, f, "Model_path");

			stratModelsPatch::modelsChangeList.push_back(mdl);
		}
	}
	f2.close();

	f1 << "Log, readed params:" << endl;

	for (stratModelsPatch::modelChangeS* mdl : stratModelsPatch::modelsChangeList)
	{
		f1 << "Model change coords:" << endl;
		f1 << "x= " << mdl->x << ", y=" << mdl->y << endl;
		f1 << "path to changed model cas file:" << endl;
		f1 << mdl->path << endl;
	}
	f1 << "end" << endl;
	f1.close();
}

void stratModelsPatch::writeModelsFile()
{
	ofstream f1("logs\\stratModelsList.youneuoylog");

	f1 << "Models:" << endl;
	for (structs::modelStratStat* mod : structs::modelsStrat)
	{
		f1 << "Index:" << mod->index << endl;
		f1 << "Patch:" << mod->patch << endl;
		f1 << "RAM adress:" << mod->modelP->model << endl;
	}
	f1.close();
}

void stratModelsPatch::runStratModelsChangeThread()
{
	readCfgFile();
	readModelsChFile();
	DWORD waitTime = stratModelsPatch::stModCfg.numberModelsChangeThreadStart;
	thread thrSMod(modelsChangeThread, waitTime);

	thrSMod.detach();
	//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)modelsChangeThread, (LPVOID)waitTime, 0, nullptr);
}

void WINAPI stratModelsPatch::disableChecker()
{
	modelsReaded = false;
	stratModelsPatch::stModCfg.checkNeed = false;
	//customModelsStrat::changeLoadCode();
	startFortsModelsPatch::disableChecker();
}

void __stdcall stratModelsPatch::enableChecker()
{
	startFortsModelsPatch::enableChecker();
	//customModelsStrat::copyListToGame();
	stratModelsPatch::stModCfg.checkNeed = true;
}

void stratModelsPatch::runWaitModelPointer(structs::modelStratStat* mod)
{
	thread thrSMod(waitModelPointer, mod);

	thrSMod.detach();
}

void stratModelsPatch::modelsChangeThread(DWORD sleepTime)
{
	int* loadState = reinterpret_cast<int*>(structs::gameDataOffsets.checkThreadOffsetModels);
	while (1)
	{
		startMet:
		Sleep(sleepTime);
		if (*loadState == 0)
		{
			continue;
		}
		if (stratModelsPatch::stModCfg.checkNeed == false)
		{
			continue;
		}
		DWORD modsNum = 0;
		Read(structs::gameDataOffsets.statStratModelsListOffset + 0x8dc, &modsNum);
		if (stratModelsPatch::stModCfg.numberModelsChangeThreadStart > modsNum)
		{
			continue;
		}

		if (FastFuncts::getFactionsCount() == 0)continue;


		UINT32 numFac = FastFuncts::getFactionsCount();

		factionStruct** listFac = FastFuncts::getFactionsList();

		/*//test
		for (UINT32 i = 0; i < numFac; i++)
		{
			UINT32 numOfSettl = listFac[i]->settlementsNum;
			if (numOfSettl == 0)continue;

			for (UINT32 j = 0; j < numOfSettl; j++)
			{
				int notChange;
					for (stratResMod* md : stratModelsPatch::changedModels)
					{
						if (listFac[i]->settlements[j]->model->castle == md->model)
						{
							notChange = 1;
							break;
						}
					}
					if (notChange == 1)
					{
						continue;
					}
					listFac[i]->settlements[j]->model->town = structs::modelsStrat[0]->modelP->model;
					listFac[i]->settlements[j]->model->castle = structs::modelsStrat[0]->modelP->model;
			}
		}*/
		//!
		//! 
		 startFortsModelsPatch::checkAndChangeModels();
		for (UINT32 i = 0; i < numFac; i++)
		{
			UINT32 numOfSettl = listFac[i]->settlementsNum;
			if (numOfSettl == 0)continue;

			for (UINT32 j = 0; j < numOfSettl; j++)
			{

				UINT32 numOfRes = listFac[i]->settlements[j]->resourcesNum;
				if (numOfRes == 0)continue;

				for (UINT32 k = 0; k < numOfRes; k++)
				{
					for (stratModelsPatch::modelChangeS* mdl : stratModelsPatch::modelsChangeList)
					{
						if (listFac[i]->settlements[j]->resources[k]->xCoord == mdl->x
							&&
							listFac[i]->settlements[j]->resources[k]->yCoord == mdl->y
							)
						{
							int num = TechFuncts::findModel(&structs::modelsStrat, &mdl->path);
							if (num == -1)
							{
								break;
							}

							if (!structs::modelsStrat[num]->modelP)break;
							//Sleep(sleepTime);
							Read(structs::gameDataOffsets.statStratModelsListOffset + 0x8dc, &modsNum);
							if (stratModelsPatch::stModCfg.numberModelsChangeThreadStart > modsNum)
							{
								goto startMet;
							}
							int notChange = 0;
							for (stratResMod* md : stratModelsPatch::changedModels)
							{
								if (listFac[i]->settlements[j]->resources[k]->stratMod == md)
								{
									notChange = 1;
									break;
								}
							}
							if(notChange == 1) 
							{
								break;
							}
							stratResMod* newMod = new stratResMod();
							newMod->resource_cost = 0;
							newMod->hasMine = 0;
							newMod->resource_num= listFac[i]->settlements[j]->resources[k]->stratMod->resource_num;
							newMod->model = structs::modelsStrat[num]->modelP->model;

							stratModelsPatch::changedModels.push_back(newMod);
							listFac[i]->settlements[j]->resources[k]->stratMod = newMod;

						}
					}
				}
			}
		}
	}
}

void WINAPI stratModelsPatch::waitModelPointer(structs::modelStratStat* mod)
{

	ofstream f1("logs\\stratModelsList.youneuoylog", ios::app);


	Sleep(stratModelsPatch::stModCfg.waitModelPointerTime);

	model_Rigid** models = reinterpret_cast<model_Rigid**>(structs::gameDataOffsets.statStratModelsListOffset);

	mod->modelP = new stratResMod();
	mod->modelP->model = models[mod->index];
	f1 << "Model:" << endl;
	f1 << "Index:" << mod->index << endl;
	f1 << "Patch:" << mod->patch << endl;
	f1 << "RAM adress here:" << hex << mod->modelP->model << endl;
	f1 << "Pointer to RAM adress:" << hex << mod->modelP << endl;
	f1 << "Done!" << endl;

	f1.close();
}

void stratModelsPatch::readCfgFile()
{
	string s = structs::cfg.modPatch + "\\youneuoy_Data\\config\\tech.youneuoycfg";
	ifstream f2(s);
	while (f2.good())
	{
		getline(f2, s);
		findOWParam(&stratModelsPatch::stModCfg.numberModelsChangeThreadStart, s, "numberModelsChangeThreadStart");
		findOWParam(&stratModelsPatch::stModCfg.waitModelsChangeThreadStart, s, "waitModelsChangeThreadStart");
		findOWParam(&stratModelsPatch::stModCfg.waitModelPointerTime, s, "waitModelPointerTime");
	}
	f2.close();
}

void __stdcall stratModelsPatch::unicalStratModsRead()
{
	if (modelsReaded == true) return;

	startFortsModelsPatch::readCasModels();
	structs::modelsStrat.clear();
	stratModelsPatch::changedModels.clear();
	modelsReaded = true;

	DWORD adr = structs::gameCodeOffsets.loadStratCasModelOffset;

	for (stratModelsPatch::modelChangeS* mdl : stratModelsPatch::modelsChangeList)
	{
		structs::modelStratStat* mod = new structs::modelStratStat();
		ofstream f1("logs\\custom_stratModels.youneuoylog", ios::app);
		f1 << "Model:"<< endl;

		mod->index = structs::modelsStrat.size();
		mod->patch = mdl->path;

		mod->modelP = new stratResMod();

		f1 << "Index:" << mod->index << endl;
		f1 << "Patch:" << mod->patch << endl;
		f1 << "Pointer to RAM adress:" << hex << mod->modelP << endl;

		char* pSArg = _strdup(mod->patch.c_str());

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
		mod->modelP->model =reinterpret_cast<model_Rigid*>(res);

		int* modsNum = reinterpret_cast<int*>(structs::gameDataOffsets.statStratModelsListOffset + 0x8dc);

		model_Rigid** modRig=reinterpret_cast<model_Rigid**>(structs::gameDataOffsets.statStratModelsListOffset);
		modRig[*modsNum] = nullptr;

		*modsNum = *modsNum - 1;

		f1 << "RAM adress here:" << hex << mod->modelP->model << endl;

		f1.close();
		structs::modelsStrat.push_back(mod);
	}
}
