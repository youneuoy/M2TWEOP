#define _WIN32_WINNT 0x0501
#include <windows.h>

#include "pch.h"



#include <Commdlg.h>

#include <fstream>
#include <string>
#include <vector>
//asm
#if _DEBUG
#pragma comment(lib,"AsmJit_debug.lib")
#else
#pragma comment(lib,"AsmJit.lib")
#endif

#include <AsmJit.h>

#include "MemWork.h"
#include "Injects.h"
#include"unitsTypeChange.h"
#include"configFiles.h"
#include "patchesForGame.h"
#include "labelsChanges.h"
#include "overwritingValues.h"
#include"keyboardFunctions.h"
#include"eduLimit.h"
#include"fortsDel.h"
#include "stratModelsPatch.h"
using namespace std;
using namespace AsmJit;
//disasm
#pragma comment(lib,"BeaEngine_s.lib")
#include "plugins.h"


//Do not do as here
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int ageCheckTrait(structs::ageStep* arg, DWORD pers)
{
	if (pers == 0)return 0;
	ofstream f1("logs\\ages.youneuoylog", ios::app);
	f1 << "Log, check trait:" << endl;
	f1 <<"search for trait:  " << arg->param << endl;

	DWORD traits;
	Read(pers + 0x1E4,&traits);
	while (traits != 0)
	{
		DWORD trNaz;
		Read(traits, &trNaz);
		DWORD lvlTtr = trNaz;
		Read(lvlTtr + 0x4, &lvlTtr);
		Read(lvlTtr, &lvlTtr);

		Read(trNaz, &trNaz);

		Read(trNaz + 0x4, &trNaz);
		string tttR = readString(trNaz);
		f1 << "character trait:  " << tttR <<",  level:"<< lvlTtr << endl;
		if (arg->param==tttR&& lvlTtr>0)
		{
			DWORD y = 0xc8;
			Write(&y, pers + 0x26c, 1);


			f1 << "Finded, age reset. End" << endl;
			f1.close();
			return 1;
		}
		Read(traits + 0x08, &traits);
	}
	f1 << "Not finded. End" << endl;
	f1.close();
	return 0;
}
int ageCheckAncillary(structs::ageStep* arg, DWORD pers)
{
	ofstream f1("logs\\ages.youneuoylog", ios::app);
	f1 << "Log, check ancillary:" << endl;
	f1 << "search for ancillary:  " << arg->param << endl;

	DWORD anchNum; 
	Read(pers + 0x1F4, &anchNum);
	DWORD mAnch;
	Read(pers + 0x1EC, &mAnch);
	int iter = anchNum;
	while (iter != 0)
	{
		DWORD anc;
		Read(mAnch + 0x0, &anc);
		Read(anc + 0x0, &anc);
		Read(anc + 0x0C, &anc);
		string anchNaz = readString(anc);
		f1 << "character ancillary:  " << anchNaz << endl;
		if (arg->param == anchNaz)
		{
			DWORD y = 0xc8;
			Write(&y, pers + 0x26c, 1);


			f1 << "Finded, age reset. End" << endl;
			f1.close();
			return 1;
		}

		mAnch += 0x4;
		iter--;
	}

	f1 << "Not finded. End" << endl;
	f1.close();
	return 0;
}
int ageCheckName(structs::ageStep* arg, DWORD pers)
{
	ofstream f1("logs\\ages.youneuoylog", ios::app);
	f1 << "Log, check name:" << endl;

	//C8 - 25 лет
	DWORD name;
	Read(pers + 0x24, &name);
	string persName = readString(name);
	f1 << "character name:  "<< persName<<endl<<"search for name:  " <<arg->param<< endl;

	if (arg->param == persName)
	{
		DWORD y = 0xc8;
		Write(&y, pers + 0x26c,1);


		f1 << "Finded, age reset. End" << endl;
		f1.close();
		return 1;
	}
	f1 << "Not finded. End" << endl;
	f1.close();
	return 0;
}
void ageFunc()
{
	DWORD pers = 0;
	_asm {
		mov pers, ecx
	}

	UINT32 anchNum;
	if (pers == 0)return;
	Read(pers + 0x1F4, &anchNum);

	for (structs::ageStep* fac : structs::dataAgeStruct.immortals)
	{
		if (fac->type == 3)
		{
			if (ageCheckName(fac, pers))
			{
				return;
			}
		}
		else if (fac->type == 1)
		{
			if (ageCheckTrait(fac, pers))
			{
				return;
			}
		}
		else if (fac->type == 2)
		{
			if (ageCheckAncillary(fac, pers))
			{
				return;
			}
		}
	}
}
void setAgeVisual(DWORD pers, string s, int standart=0)
{
	ofstream f1("logs\\ages.youneuoylog", ios::app);
	f1 << "Log, set age visual:" << endl;
	string res = readString(structs::dataAgeStruct.standartAgeStringOffset);
	if (res != structs::dataAgeStruct.standartAgeString)
	{
		f1 << "not standart age string, reset" << endl;
		char* buf = new char[res.size()+1];

		memset(buf, 0, res.size() + 1);
		Write(buf, structs::dataAgeStruct.standartAgeStringOffset, res.size());

		delete[] buf;
		buf = nullptr;
	}
	if (standart == 1)
	{
		f1 << "writing standart age string:  " << structs::dataAgeStruct.standartAgeString << endl;
		Write(&structs::dataAgeStruct.standartAgeString[0], structs::dataAgeStruct.standartAgeStringOffset, structs::dataAgeStruct.standartAgeString.length());
		f1 << "done "<< endl;

	}
	else if (standart == 0)
	{
		f1 << "reset string" << endl;

		char* buf = new char[res.size() + 1];

		memset(buf, 0, res.size() + 1);
		Write(buf, structs::dataAgeStruct.standartAgeStringOffset, res.size());

		delete[] buf;
		buf = nullptr;

		int pos = 0;
		pos = s.find_first_of("0123456789", pos);
		if (pos != string::npos)
		{
			f1 << "finded new number for age!" << endl;
			UINT32 age = 0;
			pos = s.find_first_of("0123456789", pos + 1);
			int endpos = s.find_first_not_of("0123456789.", pos + 1);
			string fileAge = s.substr(pos, endpos - pos);
			age = stoi(fileAge);


			float year = 0;
			Read(0x2BB7794, &year);
			if (year == 0)
			{
				Read(0x2BF0528, &year);
				if (year == 0)
					Read(0x2C6E4FC, &year);
			}
			float persBirthYear = 0;
			Read(pers + 0x204, &persBirthYear);
			age += year - persBirthYear;
			f1 << "new visual age:  " << s << endl;


			s.erase(pos, endpos - pos);
			s.insert(pos, to_string(age));
		}
		f1 << "writing new age string, :  " << s<<endl;

		Write(&s[0], structs::dataAgeStruct.standartAgeStringOffset, s.size());
		f1 << "done " << endl;
	}
	f1.close();
}
void ageVisualFunc()
{
	DWORD pers = 0;
	_asm {
		mov pers, edi
	}

	ofstream f1("logs\\ages.youneuoylog", ios::app);
	f1 << "Log, Opening Character Information:" << endl;
	f1.close();
	for (structs::ageStep* fac : structs::dataAgeStruct.immortals)
	{
		if (fac->type == 3)
		{
			if (ageCheckName(fac, pers))
			{
				setAgeVisual(pers, fac->forScreen);
				return;
			}
		}
		else if (fac->type == 1)
		{
			if (ageCheckTrait(fac, pers))
			{
				setAgeVisual(pers, fac->forScreen);
				return;
			}
		}
		else if (fac->type == 2)
		{
			if (ageCheckAncillary(fac, pers))
			{
				setAgeVisual(pers, fac->forScreen);
				return;
			}
		}
	}
	setAgeVisual(pers," ",1);
}
void readAgeFile()
{
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\age.yoneuoycfg";
	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		if (f == "") continue;
		structs::ageStep* age = new structs::ageStep();
		findAParam(age, f);
		findAParam(age, f);
		findAParam(age, f);
		if (age->type == 0) { f2.close(); return; }
		else
		{
			getline(f2, age->param);
			getline(f2, age->forScreen);
		}
		structs::dataAgeStruct.immortals.push_back(age);
	}
	f2.close();
}


void readFiles()
{
	readAgeFile();
	readLabelsFile();

	ofstream f1("logs\\ages.youneuoylog");
	f1 << "Log, readed params:" << endl;
	for (structs::ageStep* fac : structs::dataAgeStruct.immortals)
	{
		f1 << fac->type << endl;
		f1 << fac->param << endl;
		f1 << fac->forScreen << endl;
	}
	f1 << "end" << endl;
	f1.close();
}
void findCFGParam(int* arg, string s, string param)
{
	if (s.find(param) != string::npos)
	{
		int pos = s.find_first_of("0123456789");
		int endpos = s.find_first_not_of("0123456789", pos + 1);
		string result = s.substr(pos, endpos - pos);
		*arg = stoi(result);
	}
}

//read main config files and set some offsets
void readMF()
{
	CreateDirectory(L"logs", NULL);
	string gamever;
	ifstream f1("runningMod.youneuoycfg");

	getline(f1, gamever);
	structs::cfg.gamever = stoi(gamever);

	if (structs::cfg.gamever == 1500)
	{
		structs::cfg.gamever = 1;
		structs::dataAgeStruct.standartAgeStringOffset = 0x01342b68;
	}
	else if (structs::cfg.gamever == 1520)
	{
		structs::cfg.gamever = 2;
		structs::dataAgeStruct.standartAgeStringOffset = 0x012FDB48;
	}

	setOffsets();



	structs::dataAgeStruct.standartAgeString = readString(structs::dataAgeStruct.standartAgeStringOffset);
	getline(f1, structs::cfg.modPatch);
	f1.close();

}



//apply code injects
MemWork* mem;
void doPachs()
{
	ofstream f1("logs\\applyingPatches.youneuoylog");
	f1 << "Log:" << endl;
	mem = new MemWork();

	f1 << "Start applying age patch" << endl;
	f1 << "first step" << endl;
	Age* inj = new Age(mem, (LPVOID)ageFunc, structs::cfg.gamever);
	f1 << "step 2" << endl;
	inj->SetlAgeCode();
	f1 << "step 3" << endl;
	inj->Enable();
	f1 << "Done" << endl;

	f1 << "Start applying visual age patch" << endl;

	AgeVisual* agV  = new AgeVisual(mem, (LPVOID)ageVisualFunc, structs::cfg.gamever);
	agV->SetlAgeCode();
	agV->Enable();
	f1 << "Done" << endl;
	
	if (structs::cfg.bersPatch == 1) {
		f1 << "Start applying berserkers patch" << endl;

		berserkersP* brs = new berserkersP(mem, structs::cfg.gamever);
		brs->SetlBersCode();
		brs->Enable();
		f1 << "Done" << endl;
	}
	
	f1 << "Start applying unit types patch #1" << endl;

	toReadEDU* ed = new toReadEDU(mem, (LPVOID)afterEDUread, structs::cfg.gamever);
	ed->SetlEDUCode();
	ed->Enable();
	f1 << "Done" << endl;

	f1 << "Start applying OnChangePassedTurnsCount patch" << endl;

	toChangePassedTurnsCount* tcptc = new toChangePassedTurnsCount(mem, (LPVOID)onChangeTurnNum, structs::cfg.gamever);
	tcptc->SetlTurnsCountCode();
	tcptc->Enable();
	f1 << "Done" << endl;

	/*if (structs::cfg.gamever == 2)
	{
		f1 << "Start applying battle results patch" << endl;

		toBattleResults* brl = new toBattleResults(mem, (LPVOID)onBattleResults, structs::cfg.gamever);
		brl->SetlBattleResCode();
		//brl->SetOriginalBattleResCode();

		brl->Enable();
		f1 << "Done" << endl;
	}*/

	f1 << "Start applying label script patch" << endl;
	toCheckLabelResults* labResults = new toCheckLabelResults(mem, (LPVOID)onGiveTrait, structs::cfg.gamever);
	labResults->SetlCheckLabCode();
	labResults->Enable();

	f1 << "Done" << endl;

	f1 << "Start applying start campaign and battle start patch" << endl;
	toCreateMap* stCampaign = new toCreateMap(mem, (LPVOID)afterLoadGameData, structs::cfg.gamever);
	stCampaign->SetlCreateCode();
	stCampaign->Enable();

	f1 << "Done" << endl;

	f1 << "Start applying I_CompareCounter command patch" << endl;
	toI_CompareCounter* iccmp = new toI_CompareCounter(mem, (LPVOID)afterI_CompareCounter, structs::cfg.gamever);
	iccmp->SetltoI_CompareCounterCode();
	iccmp->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying fort patch" << endl;
	toFortsDelCheck* frt = new toFortsDelCheck(mem, (LPVOID)checkFort, structs::cfg.gamever);
	frt->SetlFortsDelCode();
	frt->Enable();

	f1 << "Done" << endl;

	f1 << "Start applying DiplomaticStanceFromFaction patch #1" << endl;
	toDSFromFacCh* dsff1 = new toDSFromFacCh(mem, (LPVOID)diplomacy::checkDipString, structs::cfg.gamever);
	dsff1->SetlDsFromFacCode();
	dsff1->Enable();

	f1 << "Done" << endl;

	f1 << "Start applying DiplomaticStanceFromFaction patch #2" << endl;
	toDiplomaticStanceCheck* dsff2 = new toDiplomaticStanceCheck(mem, (LPVOID)diplomacy::checkFacDip, structs::cfg.gamever);
	dsff2->SetlDsCheckCode();
	dsff2->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying spawn_army coords patch" << endl;
	toSpawnArmy* spwnArm = new toSpawnArmy(mem, (LPVOID)spawnArmyCoords, structs::cfg.gamever);
	spwnArm->SetlSpawnCode();
	spwnArm->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying battle_start patch" << endl;
	toBattleStratScreen* bstart = new toBattleStratScreen(mem, (LPVOID)bModelChanges::checkAndChangeModels, structs::cfg.gamever);
	bstart->SetlBSCode();
	bstart->Enable();

	f1 << "Done" << endl;



	f1 << "Start applying strat models onload patch" << endl;
	toStartReadCas* readCas = new toStartReadCas(mem, (LPVOID)stratModelsPatch::readModel, structs::cfg.gamever);
	readCas->SetlStReadCasCode();
	readCas->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying models load patch #1" << endl;
	toStartReadModels* readModelsStart = new toStartReadModels(mem, (LPVOID)stratModelsPatch::disableChecker, structs::cfg.gamever);
	readModelsStart->SetlStReadModelsCode();
	readModelsStart->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying models load patch #2" << endl;
	toEndReadModels* readModelsEnd = new toEndReadModels(mem, (LPVOID)stratModelsPatch::enableChecker, structs::cfg.gamever);
	readModelsEnd->SetlEndReadModelsCode();
	readModelsEnd->Enable();

	f1 << "Done" << endl;


	f1 << "Start applying unical strat models patch" << endl;
	toResourcesReadModels* readResModels = new toResourcesReadModels(mem, (LPVOID)stratModelsPatch::unicalStratModsRead, structs::cfg.gamever);
	readResModels->SetlResModelsCode();
	readResModels->Enable();

	f1 << "Done" << endl;

	f1 << "Start applying onEvents patch" << endl;
	toEvents* evnts = new toEvents(mem, (LPVOID)plugins::onEvent, structs::cfg.gamever);
	evnts->SetlEventsCode();
	evnts->Enable();

	f1 << "Done" << endl;

	thread thrSMod(limitsFile,mem);

	thrSMod.detach();

	f1 << "End." << endl;

	f1.close();



}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//startEduWork();
		readMF();
		doPachs();
		readFiles();
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyboardHook, 0, 0, 0));
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitS, NULL, 0, 0));
		plugins::init();
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
