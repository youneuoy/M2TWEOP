#include "diplomacy.h"


void diplomacy::readDipFile()
{
	ofstream f1("logs\\diplomacy.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\diplomacy.yoneuoycfg";

	ifstream f2(f);

	//for read events data
	string t1, t2, t3;
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t == 0) { continue; }
		else
		{
			if (t != 2000) break;
			structs::dipCond* dcnd = new structs::dipCond();

			getline(f2, t1);
			t = findParam(t1);
			if (t == 100)
			{
				getline(f2, t1);
				getline(f2, t2);
				getline(f2, t3);
				structs::I_CompareCounterS* ccs = new structs::I_CompareCounterS(t1, t2, t3);
				dcnd->cmpcounter = ccs;
				getline(f2, dcnd->descDip);
			}
			else {
				structs::I_CompareCounterS* ccs = new structs::I_CompareCounterS("0", "0", "0");
				dcnd->cmpcounter = ccs;
				dcnd->descDip = t1;
			}
			//getline(f2, dcnd->descDip);
			getline(f2, dcnd->firstFac);
			getline(f2, dcnd->nextFac);
			getline(f2, dcnd->newState);
			getline(f2, f);
			dcnd->priority = stoi(f);
			getline(f2, f);
			dcnd->importans = stoi(f);

			while (1)
			{
				getline(f2, f);
				t = findParam(f);
				if (t == 0) break;
				structs::conditionExpandedD* cnd = new structs::conditionExpandedD();
				cnd->typeCondition = t;

				getline(f2, f);
				cnd->isImportant = stoi(f);

				if (t == 800)
				{
					//factions dip status
					//fac1
					getline(f2, cnd->conditionS1);
					//fac2
					getline(f2, cnd->conditionS2);
					//state
					getline(f2, cnd->conditionS3);
					dcnd->conditions.push_back(cnd);
					continue;
				}
				getline(f2, cnd->conditionS1);


				dcnd->conditions.push_back(cnd);
			}
			structs::changeDips.push_back(dcnd);
		}
	}
	f2.close();

	sort(structs::changeDips.begin(), structs::changeDips.end(), [](const  structs::dipCond* a, const structs::dipCond* b) { return a->priority > b->priority; });

	f1 << "Log, readed(and sorted by priority) params:" << endl;

	for (structs::dipCond* dipcondS : structs::changeDips)
	{
		f1 << "start: " << endl;
		if (dipcondS->cmpcounter->TypeOperation)
		{
			f1 << dipcondS->cmpcounter->TypeOperation << endl;
			f1 << dipcondS->cmpcounter->counterName << endl;
			f1 << dipcondS->cmpcounter->number << endl;
		}
		f1 << dipcondS->descDip << endl;
		f1 << dipcondS->firstFac << endl;
		f1 << dipcondS->nextFac << endl;
		f1 << dipcondS->newState << endl;

		f1 << dipcondS->priority << endl;
		f1 << dipcondS->importans << endl;
		for (structs::conditionExpandedD* cnd : dipcondS->conditions)
		{
			f1 << "Condition" << endl;
			f1 << cnd->typeCondition << endl;
			f1 << cnd->isImportant << endl;

			f1 << cnd->conditionS1 << endl;
			if (cnd->typeCondition == 800)
			{
				f1 << cnd->conditionS2 << endl;
				f1 << cnd->conditionS3 << endl;
			}
		}
	}
	f1 << "end" << endl;
	f1.close();
}

int diplomacy::checkAndChangeFacDip(CompareCounter* compareCounter, int counter)
{
	UINT32 changed = 0;
	for (structs::dipCond* dipS : structs::changeDips)
	{
		if (dipS->cmpcounter->TypeOperation != 0 && !compareCounter)  continue;
		if (compareCounter)
		{
			if (compareCounter->operation != dipS->cmpcounter->TypeOperation) continue;
			if(readString((DWORD)compareCounter->operandName)!= dipS->cmpcounter->counterName) continue;
			if (compareCounter->checkedValue != dipS->cmpcounter->number) continue;
			if(!compareCounterValue(dipS->cmpcounter->number, compareCounter->operation, counter)) continue;

		}
		UINT32 notChange = 0;
		UINT32 imp = 0;
		factionStruct* fact = FastFuncts::findFac(&dipS->firstFac);
		for (structs::conditionExpandedD* cnd : dipS->conditions)
		{
			int res = FastFuncts::findFactionExpandedParam(fact, cnd, &dipS->descDip);

			if (res == 0 && cnd->isImportant == 1) { notChange = 1; break; }
			if (res == 1 && cnd->isImportant == 2) { notChange = 1; break; }
			if (res == 1) imp++;
		}
		if (dipS->importans == imp && notChange == 0)
		{
			changed++;
			FastFuncts::setDipStance(fact, &dipS->nextFac, &dipS->newState);
		}
	}
	return changed;
}

void diplomacy::checkAndChangeDips()
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\diplomacy.youneuoylog", ios::app);
		f1 << "Log, check for diplomacy change:" << endl;
	}
	UINT32 numFac = FastFuncts::getFactionsCount();
	if (structs::cfg.fullLogging)
	{
		f1 << "numbers of factions:" << numFac << endl;
	}

	UINT32 changed = checkAndChangeFacDip();
	if (structs::cfg.fullLogging)
	{
		f1 << "Changed diplomacy statuses:" << changed << endl;

		f1 << "End" << endl;

		f1.close();
	}
}

void diplomacy::checkAndChangeDipsCompareCounter(CompareCounter* compareCounter, int counter)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\diplomacy.youneuoylog", ios::app);
		f1 << "Log, check for diplomacy change at I_CompareCounter:" << endl;
		f1 << "counter:"<< readString((DWORD)compareCounter->operandName)<<" counter value: "<< counter<<" operation: "<< compareCounter->operation<<" value from check:"<< compareCounter->checkedValue <<endl;

	}

	UINT32 changed = checkAndChangeFacDip(compareCounter, counter);

	if (structs::cfg.fullLogging)
	{
		f1 << "Changed diplomacy statuses:" << changed << endl;

		f1 << "End" << endl;

		f1.close();
	}
}

int diplomacy::compareCounterValue(int counterV, int operation, int checkV)
{
	//==
	if (operation == 4)
	{
		return counterV == checkV;
	}
	//>
	else if (operation == 5)
		return counterV > checkV;
	//<
	else if (operation == 6 )
		return counterV < checkV;
	//!=
	else if (operation == 7)
		return counterV != checkV;
	//>=
	else if (operation == 8)
		return counterV >= checkV;
	//<=
	else if (operation == 9)
		return counterV <= checkV;
	return 0;
}

int __stdcall diplomacy::checkDipString()
{
	char* s;
	_asm {
		mov s,edx
	}

	if (!s)return 0x259;

	string stance(s);
	if (stance == "suzerain")
		return 15;
	if (stance == "AtWar")
		return 600;

	return 0x259;
}

int __stdcall diplomacy::checkFacDip()
{
	DWORD fac;
	DWORD comm;
	DWORD retz;
	_asm {
		mov retz,ecx
		mov comm, edx
		mov fac,esi
	}
	UINT32 nextfac;

	Read(comm+0x10,&nextfac);
	Read(comm+0x14,&comm);

	//15-vassal
	if(comm!=15)	return retz;

	Read(fac+0x4, &fac);
	factionStruct* f = reinterpret_cast<factionStruct*>(fac);

	UINT32 diparray;
	Read(structs::gameDataOffsets.bDataOffset, &diparray);
	diparray = diparray + 0x1750;
	factionDiplomacy* fd = reinterpret_cast<factionDiplomacy*>(diparray);

	if (fd[f->dipNum + 31 * nextfac].protectorate==15)
	{
		return 15;
	}

	return retz;
}
