#include "bModelChanges.h"

void bModelChanges::readModelsFile()
{
	ofstream f1("logs\\battleModels.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\battleModels.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t == 0) { continue; }
		else
		{
			if (t != 5000) break;
			structs::labelChangeS* ulabCh = new structs::labelChangeS();

			getline(f2, ulabCh->descLabel);
			getline(f2, ulabCh->newlabel);
			getline(f2, f);
			ulabCh->priority = stoi(f);
			getline(f2, f);
			ulabCh->importans = stoi(f);

			while (1)
			{
				getline(f2, f);
				t = findParam(f);
				if (t == 0) break;
				structs::conditionExpanded* cnd = new structs::conditionExpanded();
				cnd->typeCondition = t;

				getline(f2, f);
				cnd->isImportant = stoi(f);

				if (t == 900)
				{
					//4 coords
					getline(f2, f);
					cnd->condition1 = stoi(f);
					getline(f2, f);
					cnd->condition2 = stoi(f);
					getline(f2, f);
					cnd->condition3 = stoi(f);
					getline(f2, f);
					cnd->condition4 = stoi(f);


					ulabCh->conditions.push_back(cnd);
					continue;
				}
				getline(f2, cnd->condition);


				ulabCh->conditions.push_back(cnd);
			}
			structs::changeBModels.push_back(ulabCh);
		}
	}
	f2.close();

	sort(structs::changeBModels.begin(), structs::changeBModels.end(), [](const  structs::labelChangeS* a, const structs::labelChangeS* b) { return a->priority > b->priority; });

	f1 << "Log, readed(and sorted by priority) params:" << endl;

	for (structs::labelChangeS* labcS : structs::changeBModels)
	{
		f1 << "start: " << endl;
		f1 << labcS->descLabel << endl;
		f1 << labcS->newlabel << endl;
		f1 << labcS->priority << endl;
		f1 << labcS->importans << endl;
		for (structs::conditionExpanded* cnd : labcS->conditions)
		{
			f1 << "Condition" << endl;
			f1 << cnd->typeCondition << endl;
			f1 << cnd->isImportant << endl;
			if (cnd->typeCondition == 900)
			{
				f1 << cnd->condition1 << endl;
				f1 << cnd->condition2 << endl;
				f1 << cnd->condition3 << endl;
				f1 << cnd->condition4 << endl;
			}
			f1 << cnd->condition << endl;
		}
	}
	f1 << "end" << endl;
}

void bModelChanges::checkAndChangeModels()
{
	ofstream f1("logs\\battleModels.youneuoylog", ios::app);
	f1 << "Log, check for battle models change:" << endl;

	UINT32 numFac = FastFuncts::getFactionsCount();
	f1 << "numbers of factions:" << numFac << endl;
	factionStruct** listFac = FastFuncts::getFactionsList();

	UINT32 changed = 0;
	for (UINT32 i = 0; i < numFac; i++)
	{
		UINT32 numOfChar = listFac[i]->numOfCharacters;
		for (UINT32 j = 0; j < numOfChar; j++)
		{
			general* charac = listFac[i]->characters[j];
			if (checkAndChangeCharModel(charac))
			{
				changed++;
			}

		}
	}

	f1 << "Changed models:" << changed << endl;
	f1 << "End" << endl;

	f1.close();
}

int bModelChanges::checkAndChangeCharModel(general* gen)
{
	for (structs::labelChangeS* labcS : structs::changeBModels)
	{
		UINT32 notChange = 0;
		UINT32 imp = 0;
		for (structs::conditionExpanded* cond : labcS->conditions)
		{
			int res = FastFuncts::findCharacterExpandedParam(gen, cond, &labcS->descLabel);
			//int res = FastFuncts::findCharacterParam(gen->genChar, cond->typeCondition, &cond->condition);
			if (res == 0 && cond->isImportant == 1) { notChange = 1; break; }
			if (res == 1 && cond->isImportant == 2) { notChange = 1; break; }
			if (res == 1) imp++;
		}
		if (labcS->importans == imp && notChange == 0)
		{
			FastFuncts::setGeneralBModel(gen, &labcS->newlabel);
			return 1;
		}
	}

	return 0;
}
