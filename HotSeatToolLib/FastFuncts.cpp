#include "FastFuncts.h"

UINT32 FastFuncts::getFactionsCount()
{
	UINT32 count = 0;

	Read(structs::gameDataOffsets.factionOffsetsStart+0x324,&count);

	return count;
}

factionStruct** FastFuncts::getFactionsList()
{
	factionStruct** list;
	list=reinterpret_cast<factionStruct**>(structs::gameDataOffsets.factionOffsetsStart + 0x22c);
	return list;
}

UINT32 FastFuncts::getPassedTurnsNum()
{
	UINT32 count = 0;
	Read(structs::gameDataOffsets.factionOffsetsStart + 0x378, &count);
	return count;
}

UINT32 FastFuncts::getYear()
{
	UINT32 year = 0;
	float t = 0;

	Read(structs::gameDataOffsets.factionOffsetsStart + 0x70c, &t);
	year = (UINT32)t;
	return year;
}

UINT32 FastFuncts::getSeason()
{
	UINT32 season = 0;

	Read(structs::gameDataOffsets.factionOffsetsStart + 0x710, &season);

	return season;
}

factionStruct* FastFuncts::findFac(string* name)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();
	string s;

	UINT32 changed = 0;
	for (UINT32 i = 0; i < numFac; i++)
	{
		factionStruct* fact = listFac[i];
		string faction = readString((DWORD)fact->factName->name);

		if (faction == *name) return fact;
	}
	return listFac[0];
}

int FastFuncts::getFactionIndexByDipNum(int dipNum)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();
	for (UINT32 i = 0; i < numFac; i++)
	{
		if (listFac[i]->dipNum == dipNum)
		{
			return i;
		}
	}
	return -1;
}

EOP_EXPORT int FastFuncts::getEDUIndex(const char* type)
{
	eduEntryes* EDB=reinterpret_cast<eduEntryes*>(structs::gameDataOffsets.unitTypesStart-4);
	
	int unitsNum = EDB->numberOfTupes;
	for (int i = 0; i < unitsNum; i++)
	{
		if (strcmp(EDB->unitTupes[i].Type, type) == 0)
		{
			return i;
		}
	}
	return -1;
}

EOP_EXPORT unit* FastFuncts::createUnitN(const char* type, int facNum, int exp, int arm, int weap)
{
	int unitIndex = getEDUIndex(type);


	return createUnitIdx(unitIndex, facNum, exp, arm, weap);
}

EOP_EXPORT unit* FastFuncts::createUnitIdx(int index, int facNum, int exp, int arm, int weap)
{
	if (index == -1)return nullptr;

	unit* res;
	DWORD EDB = structs::gameDataOffsets.unitTypesStart - 4;

	DWORD adr = structs::gameCodeOffsets.createUnitOffset;
	_asm {
		mov ecx, EDB;

		push weap
		push arm
		push -1
		push exp
		push facNum
		push index
		push 0

		mov eax, [adr]
		call eax
		mov res,eax
	}

	return res;
}

EOP_EXPORT int FastFuncts::addUnitToArmy(unit* un, stackStruct* army)
{
	if (army->numOfUnits == 20)return 0;

	DWORD adr = structs::gameCodeOffsets.addUnitToArmyOffset;
	_asm {
		push 0
		push un
		mov ecx, army
		mov eax, adr
		call eax
	}
	return 1;
}

factionStruct* FastFuncts::getCurrTurnFac()
{
	factionStruct** listFac = FastFuncts::getFactionsList();
	UINT32 curr;
	Read(structs::gameDataOffsets.factionOffsetsStart + 0x348, &curr);
	return listFac[curr];
}

UINT32 FastFuncts::checkFacsDipStance(factionStruct* first, string* next, string* state)
{
	UINT32 diparray;
	Read(structs::gameDataOffsets.bDataOffset, &diparray);
	diparray = diparray + 0x1750;
	factionDiplomacy* fd = reinterpret_cast<factionDiplomacy*>(diparray);

	factionStruct* goal = findFac(next);
	UINT32 f = first->dipNum;
	UINT32 t = goal->dipNum;


	if (*state == "war")
	{
		if (
			fd[f + 31 * t].state == DIP_WAR
			&&
			fd[t + 31 * f].state == DIP_WAR
			) return 1;

	}
	else if (*state == "neutral")
	{
		if (
			fd[f + 31 * t].state == DIP_NEUTRAL
			&&
			fd[t + 31 * f].state == DIP_NEUTRAL
			) return 1;
	}
	else if (*state == "allied")
	{
		if (
			fd[f + 31 * t].state == DIP_ALLIED
			&&
			fd[t + 31 * f].state == DIP_ALLIED
			) return 1;
	}
	else if (*state == "suzerain")
	{
		if (
			fd[f + 31 * t].protectorate == 15
			&&
			fd[f + 31 * t].state == DIP_ALLIED
			) return 1;
	}
	else if (*state == "trade")
	{
		if (
			fd[f + 31 * t].trade == 1
			&&
			fd[t + 31 * f].trade == 1
			)
			return 1;
	}

	return 0;
}

EOP_EXPORT UINT32 FastFuncts::checkFacsDipStanceFast(factionStruct* first, factionStruct* next, int state)
{
	UINT32 diparray;
	Read(structs::gameDataOffsets.bDataOffset, &diparray);
	diparray = diparray + 0x1750;
	factionDiplomacy* fd = reinterpret_cast<factionDiplomacy*>(diparray);

	UINT32 f = first->dipNum;
	UINT32 t = next->dipNum;

	if (fd[t + 31 * f].state == state)
	{
		return 1;
	}



	return 0;
}

string FastFuncts::findFacByModNum(int modnum)
{
	string s;
	if (modnum > 31) { s = "wrong :-)"; return s; }

	DWORD ofst=0;
	Read(structs::gameDataOffsets.modelsInfoOffset, &ofst);

	ofst = ofst + modnum * 0xe0;

	Read(ofst+0x4, &ofst);

	s = readString(ofst);
	return s;
}

void FastFuncts::setUnitType(unit* un, UINT32 newTypeID)
{
	ofstream f1("logs\\guard.youneuoylog", ios::app);
	f1 << "Log:" << endl;
	string name = readString((DWORD)un->general->genChar->fullName);
	f1 << "changing the guard of  "<<name<<" to(index): " << newTypeID << endl;

	un->eduEntry = reinterpret_cast<EduEntry*>(structs::gameDataOffsets.unitTypesStart+sizeof(EduEntry)* newTypeID);
	f1 << "end" << endl;
	f1.close();
}

UINT32 FastFuncts::findCharacterParam(generalCharacterictics* gen, UINT32 type, string* param)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\all.youneuoylog", ios::app);
		f1 << "Log searching for character param(type):" << type << " value: " << *param << "character: " << readString((DWORD)gen->fullName) << endl;
	}

	if (type == 3 )//name
	{
		string name = readString((DWORD)gen->fullName);
		if (*param == name)
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "finded name:  " << name << endl;
				f1 << "end" << endl;
				f1.close();
			}
			return 1;
		}
	}
	else if (type == 2)//anchillary
	{
		UINT32 anchNum = gen->anchNum;
		for (UINT32 i = 0; i < anchNum; i++)
		{
			string anch = readString((DWORD)gen->anchillaries[i]->dataAnch->anchName);
			if (*param == anch)
			{
				if (structs::cfg.fullLogging)
				{
					f1 << "finded ancillary:  " << anch << endl;
					f1 << "end" << endl;
					f1.close();
				}
				return 1;
			}
		}
	}
	else if (type == 1)//trait
	{
		DWORD traits= (DWORD)gen->traits;
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
			if (structs::cfg.fullLogging)
			f1 << "character trait:  " << tttR << ",  level:" << lvlTtr << endl;
			if (*param == tttR && lvlTtr > 0)
			{
				if (structs::cfg.fullLogging) {
					f1 << "finded trait:  " << tttR << endl;
					f1 << "end" << endl;
					f1.close();
				}
				return 1;
			}
			Read(traits + 0x08, &traits);
		}

	}
	//label
	else if (type == 4)
	{
		if (gen->label == 0)
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "end" << endl;
				f1.close();
			}
			return 0;
		}
		string label = readString((DWORD)gen->label);
		if (*param == label)
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "finded label:  " << label << endl;
				f1 << "end" << endl;
				f1.close();
			}
			return 1;
		}
	}
	else if (type == 5001)
	{
		if (*param == "leader")
		{
			if (gen->status & 5)
			{
				if (structs::cfg.fullLogging)
				{
					f1 << "finded leader"  << endl;
					f1 << "end" << endl;
					f1.close();
				}
				return 1;
			}
		}
		else if (*param == "heir")
		{
			if (gen->status & 2)
			{
				if (structs::cfg.fullLogging)
				{
					f1 << "finded heir" << endl;
					f1 << "end" << endl;
					f1.close();
				}
				return 1;
			}
		}
	}

	else if (type == 5002)
	{
		string fac = readString((DWORD)gen->faction->factName->name);
		if (fac == *param)
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "finded faction:" <<fac<< endl;
				f1 << "end" << endl;
				f1.close();
			}
			return 1;
		}
	}

	else if (findNotconcrectParam(type, param) == 1)
	{
		if (structs::cfg.fullLogging)
		{
			f1 << "finded turn condition: "<< "  turn num:" << getPassedTurnsNum() << "finded " << *param << endl;
			f1 << "End." << endl;
			f1.close();
		}
		return 1;
	}

	if (structs::cfg.fullLogging)
	{
		f1 << "end" << endl;
		f1.close();
	}
	return 0;
}

UINT32 FastFuncts::findCharacterExpandedParam(general* gen, structs::conditionExpanded* cond, string* descr)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\all.youneuoylog", ios::app);
		f1 << "Log searching for param(type):" << cond->typeCondition << "  description: " << *descr << "  character: " << readString((DWORD)gen->genChar->fullName) << endl;
	}
	if (cond->typeCondition == 900)
	{
		if (structs::cfg.fullLogging)
		{
			f1 << "try to find character in: " << cond->condition1 << "," << cond->condition2 << "," << cond->condition3 << "," << cond->condition4 << endl;
			f1 << "character in: " << gen->xCoord << "," << gen->yCoord << endl;
		}

		if (TechFuncts::inside(gen->xCoord,gen->yCoord,cond->condition1,cond->condition2,cond->condition3,cond->condition4)==1)
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "character: " << readString((DWORD)gen->genChar->fullName) << "  in coords:" << cond->condition1 << "," << cond->condition2 << "," << cond->condition3 << "," << cond->condition4 << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}
	
	else
	{
		if (structs::cfg.fullLogging)
		{
			f1 << "End." << endl;
			f1.close();
		}

		if (findCharacterParam(gen->genChar, cond->typeCondition, &cond->condition) == 1)
		{
			return 1;
		}
	}
	if (structs::cfg.fullLogging)
	{
		f1 << "End.";
		f1.close();
	}
	return 0;
}

UINT32 FastFuncts::findFactionExpandedParam(factionStruct* fac, structs::conditionExpandedD* cond, string* descr)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\ALL_faction.youneuoylog", ios::app);
		f1 << endl<< "Log searching for faction param(type):" << cond->typeCondition << "  description: " << *descr << "  faction: " << readString((DWORD)fac->factName->name) << endl;
	}

	if (cond->typeCondition == 800)
	{
		if (checkFacsDipStance(fac,&cond->conditionS2,&cond->conditionS3))
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "faction: " << readString((DWORD)fac->factName->name) << "  has " << cond->conditionS3 << " with faction  " << cond->conditionS2 << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}

	else if (findNotconcrectParam(cond->typeCondition, &cond->conditionS1) == 1)
	{
		if (structs::cfg.fullLogging)
		{
			f1 << "faction: " << readString((DWORD)fac->factName->name) << "  turn num:" << getPassedTurnsNum() << "finded" << cond->conditionS1 << endl;
			f1 << "End." << endl;
			f1.close();
		}
		return 1;
	}

	if (structs::cfg.fullLogging)
	{
		f1 << "End.";
		f1.close();
	}
	return 0;
}

UINT32 FastFuncts::findNotconcrectParam(UINT32 type, string* cond)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	{
		f1.open("logs\\all.youneuoylog", ios::app);
		f1 << "Log searching for param(type):" << type <<"condition: "<< *cond << endl;
	}
	if (type == 999)
	{
		if (getPassedTurnsNum() >= atoi(cond->c_str()))
		{
			if (structs::cfg.fullLogging)
			{
				f1 << " turn num:" << getPassedTurnsNum() << ">=" <<*cond << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}
	else if (type == 998)
	{
		if (getPassedTurnsNum() > atoi(cond->c_str()))
		{
			if (structs::cfg.fullLogging)
			{
				f1  << "  turn num:" << getPassedTurnsNum() << ">" << *cond << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}
	else if (type == 997)
	{
		if (getPassedTurnsNum() < atoi(cond->c_str()))
		{
			if (structs::cfg.fullLogging)
			{
				f1<< "  turn num:" << getPassedTurnsNum() << "<" << *cond << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}
	else if (type == 996)
	{
		if (getPassedTurnsNum() == atoi(cond->c_str()))
		{
			if (structs::cfg.fullLogging)
			{
				f1 << "  turn num:" << getPassedTurnsNum() << "=" << *cond << endl;
				f1 << "End." << endl;
				f1.close();
			}
			return 1;
		}
	}
	if (structs::cfg.fullLogging)
	{
		f1 << "End.";
		f1.close();
	}
	return 0;
}

vector<structs::arm*> FastFuncts::getBattleStacksList()
{
	ofstream f1("logs\\stacksInBattle.youneuoylog", ios::app);
	vector<structs::arm*> battleArmies;
	stackStruct* army=0;
	f1 << "read battle stacks" << endl;
	UINT32 sides;
	Read(structs::gameDataOffsets.battleStacksOffsetStart+0xca78, &sides);
	DWORD oneSideSize = 0x192c;
	DWORD oneStackSize = 0x60;
	DWORD stackOffset;

	unsigned char def = 0;
	UINT32 dest = 0;
	UINT32 sieg = 0;
	for (UINT32 i = 0; i < sides; i++)
	{

		stackOffset = structs::gameDataOffsets.battleStacksOffsetStart + 0xf8 + (i * oneSideSize);

		Read(stackOffset-0x5c, &def,1);

		Read(stackOffset-0x50, &dest);
		if(dest!=0)
		Read(dest+4, &dest);

		Read(stackOffset - 0x4c, &sieg);
		if (sieg != 0)
		Read(sieg + 4, &sieg);

		do {
			Read(stackOffset, &army);
			if (army == 0)
			{
				break;
			}
			structs::arm* ar = new structs::arm();
			ar->side = i;
			ar->ifDef = def;
			ar->army = army;
			if (dest == 1 || sieg == 1)
				ar->condDest = 1;
			if (dest == 4 || sieg == 4)
				ar->condSetl = 1;
			Read(stackOffset+0x30, &ar->deploy);

			battleArmies.push_back(ar);
			stackOffset = stackOffset + oneStackSize;
		} while (1);

	}
	f1.close();

	return battleArmies;
}

vector<structs::arm*>* FastFuncts::getBattleStacksListP()
{
	vector<structs::arm*>* ret=new vector<structs::arm*>();
	*ret= getBattleStacksList();
	return ret;
}

void FastFuncts::killUnit(unit* un)
{
	DWORD adr = 0;
	DWORD arg = 0;
	if (un->general)
	{
		adr = structs::gameCodeOffsets.killCharStratMapOffset;
		arg = reinterpret_cast<DWORD>(un->general);
	}
	else 
	{
		adr = structs::gameCodeOffsets.killUnitOffset;
		arg = reinterpret_cast<DWORD>(un);
	}
	_asm {
		push 0x1
		mov ecx,[arg]
		mov eax,[adr]
		call eax
	}

}

EOP_EXPORT int FastFuncts::addAnchillary(generalCharacterictics* character, anchillary* anch)
{

	if (character == nullptr || anch == nullptr)return 0;

	DWORD adr = 0;
	int ret = 0;
	if (structs::cfg.gamever == 2)//steam
	{
		adr = 0x005a5d50;
	}
	else
	{
		adr = 0x005a5870;
	}
	_asm
	{
		mov ecx, character
		push anch
		mov eax, adr
		call eax
		mov ret,eax
	}


	return ret;
}

EOP_EXPORT void FastFuncts::removeAnchillary(generalCharacterictics* character, anchillary* anch)
{
	if (character == nullptr || anch == nullptr)return;

	DWORD adr = 0;
	int ret = 0;
	if (structs::cfg.gamever == 2)//steam
	{
		adr = 0x005a5e70;
	}
	else
	{
		adr = 0x005a5990;
	}
	_asm
	{
		mov ecx, character
		push anch
		mov eax, adr
		call eax
		mov ret, eax
	}

	return;
}

EOP_EXPORT anchillary* FastFuncts::findAnchillary(char* anchName)
{
	if (anchName == nullptr)return 0;

	DWORD adr = 0;
	anchillary* ret = nullptr;
	if (structs::cfg.gamever == 2)//steam
	{
		adr = 0x008b1d30;
	}
	else
	{
		adr = 0x008b1340;
	}

	_asm
	{
		push anchName
		mov eax, adr
		call eax
		add esp, 4
		mov ret, eax
	}


	return ret;
}

int FastFuncts::setUnitSoldiers(unit* un, UINT32 num, UINT32 exp, string type)
{
	ofstream f1("logs\\battleResults.youneuoylog", ios::app);
	f1 << "Log, set unit:"<< endl << endl;
	f1 << "data for set: " << endl;
	f1 << "type: " << type<< endl;
	f1 << "number: " << num << endl;
	f1 << "expierence: " << exp << endl;

	f1 << "unit now:" << endl;
	string name = readString((DWORD)un->eduEntry->Type);
	f1 << "type: " << name << endl;
	f1 << "number: " << un->number << endl;
	f1 << "expierence: " << un->expScreen << endl;

	if (name!=type)
	{
		f1 << "wrong unit" << endl;
		f1 << "end" << endl;
		f1.close();
		return 0;
	}

	if (num == 0)
	{
		FastFuncts::killUnit(un);
		f1 << "killed"<<endl;
		f1 << "end" << endl;
		f1.close();
		return 1;
	}
	un->number = num;
	un->expScreen = exp;

	for (int i = 0; i < un->number; i++)
	{
		un->soldiersArr[i].exp = exp*0x10+1;
	}
	
	f1 << "unit after set:" << endl;
	name = readString((DWORD)un->eduEntry->Type);
	f1 << "type: " << name << endl;
	f1 << "number: " << un->number << endl;
	f1 << "expierence: " << un->expScreen << endl;
	f1 << "end" << endl;
	f1.close();
	return 1;
}

EOP_EXPORT int FastFuncts::setUnitSoldiersAdvanced(unit* un, int num, int exp)
{
	if (num<=1)
	{
		return 0;
	}
	un->number = num;
	un->expScreen = exp;

	for (int i = 0; i < un->number; i++)
	{
		un->soldiersArr[i].exp = exp * 0x10 + 1;
	}

	return 1;
}

void FastFuncts::setGeneralLabel(general* gen, string* label)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
	f1.open("logs\\all.youneuoylog", ios::app);
	if (structs::cfg.fullLogging)
	f1 << "Log, try to set character label, character: " << readString((DWORD)gen->genChar->fullName) << " label: " << *label << endl;
	//gen->genChar->label = new char[label->length() + 1];


	char* lab = new char[label->length() + 1];
	//gen->genChar->labelCrypt = getLabelCrypt(label->c_str());
	memcpy(lab, label->c_str(), label->length() + 1);
	UINT32 persLab = (UINT32)&gen->genChar->label;
	UINT32 functionOffset = structs::gameCodeOffsets.setStringAndCryptOffset;
	_asm {
		push lab
		mov ecx, persLab
		mov eax, functionOffset
		call eax
	}

	if (structs::cfg.fullLogging)
	f1 << "label now: " << gen->genChar->label << endl<<" End."<< endl;
	if (structs::cfg.fullLogging)
	f1.close();
}

void FastFuncts::setGeneralBModel(general* gen, string* model)
{
	ofstream f1;
	if (structs::cfg.fullLogging)
		f1.open("logs\\all.youneuoylog", ios::app);
	if (structs::cfg.fullLogging)
		f1 << "Log, try to set character battle model, character: " << readString((DWORD)gen->genChar->fullName) << " model: " << *model << endl;
	//gen->genChar->label = new char[label->length() + 1];


	char* modl = new char[model->length() + 1];
	//gen->genChar->labelCrypt = getLabelCrypt(label->c_str());
	memcpy(modl, model->c_str(), model->length() + 1);
	UINT32 persMod = (UINT32)&gen->genChar->modelName;
	UINT32 functionOffset = structs::gameCodeOffsets.setStringAndCryptOffset;
	_asm {
		push modl
		mov ecx, persMod
		mov eax, functionOffset
		call eax
	}

	if (structs::cfg.fullLogging)
		f1 << "Battle model now: " << gen->genChar->modelName << endl << " End." << endl;
	if (structs::cfg.fullLogging)
		f1.close();
}

void FastFuncts::setDipStance(factionStruct* first, string* next, string* state)
{
	ofstream f1;
	if (structs::cfg.fullLogging) 
	{
		f1.open("logs\\ALL_faction.youneuoylog", ios::app);
		f1 << endl << "Changing the diplomatic relations of the factions of" << readString((DWORD)first->factName->name) << "  and " << *next << "  to: " << *state << endl;
	}
	UINT32 diparray;
	Read(structs::gameDataOffsets.bDataOffset, &diparray);
	diparray = diparray + 0x1750;
	factionDiplomacy* fd = reinterpret_cast<factionDiplomacy*>(diparray);

	factionStruct* goal = findFac(next);
	UINT32 f = first->dipNum;
	UINT32 t = goal->dipNum;
	//enable war, disable trade
	if (*state=="war")
	{
		disableVassal(&fd[f + 31 * t], &fd[t + 31 * f]);
		fd[f + 31 * t].state=DIP_WAR;
		fd[f + 31 * t].trade = 0;
		fd[t + 31 * f].trade = 0;
		fd[t + 31 * f].state=DIP_WAR;
	}
	else if (*state == "neutral")
	{
		disableVassal(&fd[f + 31 * t], &fd[t + 31 * f]);
		fd[f + 31 * t].state = DIP_NEUTRAL;
		fd[t + 31 * f].state = DIP_NEUTRAL;
	}
	else if (*state == "allied")
	{
		disableVassal(&fd[f + 31 * t], &fd[t + 31 * f]);
		fd[f + 31 * t].state = DIP_ALLIED;
		fd[t + 31 * f].state = DIP_ALLIED;
	}
	else if (*state == "suzerain")
	{
		enableVassal(&fd[f + 31 * t], &fd[t + 31 * f]);
	}
	else if (*state == "trade")
	{
		fd[f + 31 * t].trade = 1;
		fd[t + 31 * f].trade = 1;
	}
	if (structs::cfg.fullLogging)
	{
		f1 << "End";
		f1.close();
	}
}

void FastFuncts::disableVassal(factionDiplomacy* first, factionDiplomacy* next)
{
	first->state = DIP_NEUTRAL;
	next->state = DIP_NEUTRAL;
	if (first->protectorate == 15)
		first->protectorate = 6;
	if (next->protectorate == 15)
		next->protectorate = 6;
}

void FastFuncts::enableVassal(factionDiplomacy* first, factionDiplomacy* next)
{
	next->state = DIP_NEUTRAL;
	if (first->protectorate != 15)
		first->protectorate = 15;
	first->state = DIP_ALLIED;
	next->state = DIP_ALLIED;
	first->trade = 1;
	next->trade = 1;
}

int FastFuncts::getNewAge(int ageChar, int newAge)
{
	int ret = 0;
	ret = ageChar ^ (newAge * 8 ^ ageChar) & 0x3f8;

	return ret;
}

void FastFuncts::setHeir(generalCharacterictics* gen)
{
	/*factionStruct* fac = gen->faction;
	_asm {
		push gen
		mov ecx, fac
		mov eax, [fac]
		mov eax, [eax]
		mov eax, [eax+0x20]
		call eax
	}*/
	factionStruct* fac = gen->faction;
	fac->heir = gen;
}

settlementStruct* FastFuncts::checkSett(int x, int y, factionStruct* fac)
{
	int num = fac->settlementsNum;
	for (int i = 0; i < num; i++)
	{
		if (fac->settlements[i]->xCoord == x && fac->settlements[i]->yCoord == y)
			return fac->settlements[i];
	}
	return nullptr;
}

void FastFuncts::closeFamilyTree()
{
	UINT32 tree;
	UINT32 adr;
	Read(structs::gameDataOffsets.stratUiOffset, &tree);

	if (!tree)return;
	Read(tree + 0xec, &tree);
	if (!tree)return;
	Read(tree + 0x68, &tree);
	if (!tree)return;
	Read(tree, &adr);
	if (!adr)return;
	Read(adr + 0xe0, &adr);
	if (!adr)return;
	_asm {
		mov ecx, [tree]
		mov eax, [adr]
		call eax
	}
}

void FastFuncts::closeOwnSettlement()
{
	UINT32 tree;
	UINT32 adr;
	Read(structs::gameDataOffsets.stratUiOffset, &tree);

	if (!tree)return;
	Read(tree + 0xb8, &tree);
	if (!tree)return;
	Read(tree + 0x68, &tree);
	if (!tree)return;
	Read(tree, &adr);
	if (!adr)return;
	Read(adr + 0xe0, &adr);
	if (!adr)return;
	_asm {
		mov ecx, [tree]
		mov eax, [adr]
		call eax
	}
}

void FastFuncts::closeOwnCharacter()
{
	UINT32 tree;
	UINT32 adr;
	Read(structs::gameDataOffsets.stratUiOffset, &tree);

	if (!tree)return;
	Read(tree + 0xc4, &tree);
	if (!tree)return;
	Read(tree + 0x68, &tree);
	if (!tree)return;
	Read(tree, &adr);
	if (!adr)return;
	Read(adr + 0xe0, &adr);
	if (!adr)return;
	_asm {
		mov ecx, [tree]
		mov eax, [adr]
		call eax
	}
}

string FastFuncts::getTraits(generalCharacterictics* gen)
{
	string tr;
	DWORD traits = (DWORD)gen->traits;
	tr= "traits ";
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

		tr += " ";
		tr += tttR;
		tr += " ";
		tr += to_string(lvlTtr);
		tr += " ";
		tr += ",";


		Read(traits + 0x08, &traits);
	}
	return tr;
}

portBuildingStruct* FastFuncts::findPort(int x, int y)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();

	for (UINT32 i = 0; i < numFac; i++)
	{
		for (int j = 0; j < listFac[i]->portBuildingsNum; j++)
		{
			if (listFac[i]->portBuildings[j]->x == x
				&&
				listFac[i]->portBuildings[j]->y == y
				)
			{
				return listFac[i]->portBuildings[j];
			}
		}

	}

	return nullptr;
}

fortStruct* FastFuncts::findFort(int x, int y)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();

	for (UINT32 i = 0; i < numFac; i++)
	{
		for (int j = 0; j < listFac[i]->fortsNum; j++)
		{
			if (listFac[i]->forts[j]->xCoord == x
				&&
				listFac[i]->forts[j]->yCoord == y
				)
			{
				return listFac[i]->forts[j];
			}
		}

	}

	return nullptr;
}

general* FastFuncts::findCharacter(int x, int y)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();

	for (UINT32 i = 0; i < numFac; i++)
	{
		for (int j = 0; j < listFac[i]->numOfCharacters; j++)
		{
			if (listFac[i]->characters[j]->ifMarkedToKill==0
				&&
				listFac[i]->characters[j]->xCoord == x
				&&
				listFac[i]->characters[j]->yCoord == y			
				)
			{
				return listFac[i]->characters[j];
			}
		}

	}
	return nullptr;
}

UINT32 FastFuncts::getLabelCrypt(const char* label)
{
	char cVar1;
	UINT32 uVar2;
	UINT32 uVar3;

	uVar2 = 0;
	UINT32 result = 0;
	cVar1 = *label;
	while (cVar1 != '\0') {
		uVar3 = label[uVar2];
		if ((uVar2 & 1) == 0)
		{
			uVar3 = uVar3 << 0x10;
		}
		result = result + uVar3;
		uVar2 = uVar2 + 1;
		cVar1 = label[uVar2];
	}
	return result;
}

void FastFuncts::unlockConsoleCommands()
{
	uchar nops[2] = { 0x90,0x90 };
	DWORD cmd = structs::gameCodeOffsets.consoleCommandsOffset;

	//check checking code and change all jmps to nops
	for (int i = 0; i < 53; i++, cmd++)
	{
		uchar jz = 0x74;
		uchar ch;
		Read(cmd,&ch,1);
		if (ch == jz)
		{
			Write(nops, cmd, 2);
		}
	}


}

void FastFuncts::writeConsoleCommandsFile()
{
	if (structs::cfg.fullLogging)
	{
		ofstream f1;
		f1.open("logs\\console_commands.youneuoylog", ios::app);
		f1 << "Console commands list:"<< endl;
		console_command* cmd = reinterpret_cast<console_command*>(structs::gameDataOffsets.consoleCommandsOffset);
		int number = 63;
		int i = 0;
		for (; i < number; i++)
		{
			f1 << "Number: " << i << endl;
			f1 << cmd[i].name << endl;
			f1 << cmd[i].description << endl;
		}
		cmd = reinterpret_cast<console_command*>((int)cmd + 4);

		number = 121;
		for (; i < number; i++)
		{
			f1 << "Number: " << i+62 << endl;
			f1 << cmd[i].name << endl;
			f1 << cmd[i].description << endl;
		}

		f1.close();
	}
}

stackStruct* FastFuncts::getArmyOnCoords(int x, int y, int skippedNumber)
{
	UINT32 numFac = FastFuncts::getFactionsCount();
	factionStruct** listFac = FastFuncts::getFactionsList();

	int number = 0;
	for (UINT32 i = 0; i < numFac; i++)
	{
		for (int j = 0; j < listFac[i]->stackNum; j++)
		{
			if (listFac[i]->stacks[j]->gen == nullptr)continue;


			if (listFac[i]->stacks[j]->gen->xCoord == x
				&&
				listFac[i]->stacks[j]->gen->yCoord == y
				)
			{
				if (number >= skippedNumber)
				{
					return listFac[i]->stacks[j];
				}
				number++;
			}
		}

	}

	return nullptr;
}
