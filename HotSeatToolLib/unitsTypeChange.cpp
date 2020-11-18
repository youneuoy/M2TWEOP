#include "unitsTypeChange.h"
void readUnitsTypeFile()
{
	ofstream f1("logs\\guard.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\guard.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t == 0) { continue; }
		else
		{
			structs::unitChangeS* utypeP = new structs::unitChangeS();
			utypeP->typeCondition = t;
			getline(f2, utypeP->condition);
			getline(f2, utypeP->oldUnit.typeS);
			getline(f2, utypeP->newUnit.typeS);
			getline(f2, f);
			utypeP->priority = stoi(f);
			structs::changeUnits.push_back(utypeP);
		}
	}
	f2.close();

	sort(structs::changeUnits.begin(), structs::changeUnits.end(), [](const  structs::unitChangeS* a, const structs::unitChangeS* b) { return a->priority > b->priority; });

	f1 << "Log, readed(and sorted by priority) params:" << endl;

	for (structs::unitChangeS* unit : structs::changeUnits)
	{
		f1 << unit->typeCondition << endl;
		f1 << unit->condition << endl;
		f1 << unit->oldUnit.typeS << endl;
		f1 << unit->newUnit.typeS << endl;
		f1 << unit->priority << endl << endl;
	}
	f1 << "end" << endl;
	f1.close();
}

void readUnitsTypesFunc()
{
	readUnitsTypeFile();
	DWORD number;
	ofstream f1("logs\\guard.youneuoylog", ios::app);

	Read((DWORD)(structs::gameDataOffsets.unitTypesStart + 0x3e4 * 0x1f4), &number);
	f1 << "Log, searching for types id:" << endl;
	f1 << "number of types:"<< number << endl;

	EduEntry* typeUnit = reinterpret_cast<EduEntry*>(structs::gameDataOffsets.unitTypesStart);
	string s;
	UINT32 kol = 0;
	for (UINT32 i = 0; i < number; i++)
	{
		s = readString((DWORD)typeUnit[i].Type);

		for (structs::unitChangeS* unit : structs::changeUnits)
		{
			if (unit->newUnit.typeS == s)
			{
				kol++;
				unit->newUnit.typeID = typeUnit[i].Index;
			}
			if (unit->oldUnit.typeS == s)
			{
				kol++;
				unit->oldUnit.typeID = typeUnit[i].Index;
			}

		}
	}
	f1 << "Finded id`s:"<<kol << endl;
	f1 << "End" << endl;
	f1.close();
}

int checkAndChangeUnitType(unit* un)
{
	for (structs::unitChangeS* unitC : structs::changeUnits)
	{
		if (un->eduEntry->Index != unitC->oldUnit.typeID) continue;
		if (unitC->typeCondition == 999)//read comments to structure
		{
			if (FastFuncts::getPassedTurnsNum() >= atoi(unitC->condition.c_str()))
			{
				ofstream f1("logs\\guard.youneuoylog", ios::app);
				f1 << "Log:" << endl;
				f1 <<"turns passed: "<< FastFuncts::getPassedTurnsNum() <<" >= "<< unitC->condition << endl;
				f1 << "end" << endl;
				f1.close();
				FastFuncts::setUnitType(un, unitC->newUnit.typeID);
				return 1;
			}
		}
		else if (FastFuncts::findCharacterParam(un->general->genChar, unitC->typeCondition, &unitC->condition))
		{
			FastFuncts::setUnitType(un, unitC->newUnit.typeID);
			return 1;
		}
	}
	return 0;
}

void checkAndChangeUnitsTypeFunc()
{
	ofstream f1("logs\\guard.youneuoylog", ios::app);
	f1 << "Log, check for guard change:" << endl;

	UINT32 numFac = FastFuncts::getFactionsCount();
	f1 << "numbers of factions:" << numFac<<endl;
	factionStruct** listFac = FastFuncts::getFactionsList();
	string s;

	UINT32 changed = 0;
	for (UINT32 i = 0; i < numFac; i++)
	{
		UINT32 kolArmies = listFac[i]->stackNum;
		for (UINT32 j = 0; j < kolArmies; j++)
		{
			stackStruct* army = listFac[i]->stacks[j];
			UINT32 numUnits = army->numOfUnits;
			for (UINT32 k = 0; k < numUnits; k++)
			{
				if (army->units[k]->general != 0)
				{
					if (checkAndChangeUnitType(army->units[k]))
					{
						changed++;
					}
				}
			}
		}
	}
	f1 << "Changed units:" << changed << endl;
	f1 << "End" << endl;

	f1.close();
}