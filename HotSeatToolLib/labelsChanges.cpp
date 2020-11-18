#include "labelsChanges.h"


void readLabelsFile()
{
	ofstream f1("logs\\labels.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\labels.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t == 0) { continue; }
		else
		{
			if (t != 1000) break;
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
			structs::changeLabels.push_back(ulabCh);
		}
	}
	f2.close();

	sort(structs::changeLabels.begin(), structs::changeLabels.end(), [](const  structs::labelChangeS* a, const structs::labelChangeS* b) { return a->priority > b->priority; });

	f1 << "Log, readed(and sorted by priority) params:" << endl;

	for (structs::labelChangeS* labcS : structs::changeLabels)
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
			if (cnd->typeCondition==900)
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


	f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\labels_immutable.yoneuoycfg";

	f2.open(f);
	while (f2.good())
	{
		getline(f2, f);
		if (f.size()>0&&f[0] != ';')
		{
			structs::immutableLabels.push_back(f);
		}
	}
	f2.close();

	f1 << "labels_immutable:" << endl;
	for (string s : structs::immutableLabels)
	{
		f1 << s<< endl;
	}

	f1 << "end" << endl;
	f1.close();
}

int checkAndChangeCharLabel(general* gen)
{
	if (gen->genChar->label) {
		string label = readString((DWORD)gen->genChar->label);
		for (string s : structs::immutableLabels)
		{
			if (label == s)
			{
				return 0;
			}
		}
	}
	for (structs::labelChangeS* labcS : structs::changeLabels)
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
			FastFuncts::setGeneralLabel(gen, &labcS->newlabel);
			return 1;
		}
	}

	return 0;
}

void checkAndChangeLabels()
{
	ofstream f1("logs\\labels.youneuoylog", ios::app);
	f1 << "Log, check for labels change:" << endl;

	UINT32 numFac = FastFuncts::getFactionsCount();
	f1 << "numbers of factions:" << numFac << endl;
	factionStruct** listFac = FastFuncts::getFactionsList();
	string s;

	UINT32 changed = 0;
	for (UINT32 i = 0; i < numFac; i++)
	{
		UINT32 numOfChar = listFac[i]->numOfCharacters;
		for (UINT32 j = 0; j < numOfChar; j++)
		{
			general* charac = listFac[i]->characters[j];
			if (checkAndChangeCharLabel(charac))
			{
				changed++;
			}

		}
	}
	f1 << "Changed labels:" << changed << endl;
	f1 << "End" << endl;

	f1.close();
}

void checkLabForDelete(string* command, general* character)
{
	//1-delete, 2 - change
	UINT32 action = 0;
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\all.youneuoylog", ios::app);
		f1 << "Log, check label from script command:" << endl;
		f1 << "script command params:" << *command << endl;
		f1 << "Character:" << readString((DWORD)character->genChar->fullName) << endl;
	}
	if (command->find(structs::cfg.anchillaryDelLab) == string::npos) 
	{
		if (structs::cfg.fullLogging)
		{
			f1 << "End." << endl;
			f1.close();
		}
		return;
	}

	int pos = command->find_first_of(" ");
	string lab(*command);
	lab.erase(pos);

	if (structs::cfg.fullLogging)
	f1 << "Label:" << lab << endl;

	int res = FastFuncts::findCharacterParam(character->genChar, LABEL_COND_CODE, &lab);

	if (res == 1)
	{
		if (command->find(structs::cfg.anchillaryChangeLab) == string::npos)
		{
			action = 1;
		}
		else
		{
			action = 2;
		}
		if (action == 1)
		{
			character->genChar->label = 0;
			character->genChar->labelCrypt = 0;
			if (structs::cfg.fullLogging)
			f1 << "Label deleted" << endl;
		}
		else if (action == 2)
		{
			pos= command->find_last_of(":");
			*command = command->substr(pos+1);
			FastFuncts::setGeneralLabel(character, command);
		}
	}
	if (structs::cfg.fullLogging)
	f1.close();
}
