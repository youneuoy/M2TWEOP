#include "battlesResults.h"

vector<structs::arm*> bResults::stacksInBattle;
bool bResults::isDrawNedeed = false;
bool bResults::isFuckGatesDrawNedeed = true;
int* bResults::battleState = nullptr;

void bResults::setBattleResults()
{

	if (stacksInBattle.size() == 0)
	{
		MessageBoxA(NULL, "No!", "Info!", NULL);
		return;
	}

	ofstream f2("logs\\battleResults.youneuoylog");
	f2 << "start set battle results" << endl;

	f2 <<"number of armies in battle: "<< bResults::stacksInBattle.size()<<endl;

	string s = structs::cfg.modPatch + "\\battleResults\\battle_results.txt";
	f2 << s<< endl;

	f2.close();
	ifstream f1(s);

	UINT32 armynum=0;
	string w;
	string tmp1;

	int numOtr;
	string nazOtr;
	int kolvo;
	int expi;
	while (f1.good()) {
		getline(f1, s);
		if (s == "army")
		{
			armynum++;
			do {
				getline(f1, s);
				if (s != "unit")
				{
					break;
				}
				//number in stack
				getline(f1, w, '=');
				if (w != "number in army") 
				{
					MessageBox(NULL, L"Wrong number in army", L"ERROR", MB_OK | MB_ICONASTERISK);
					MessageBoxA(NULL,w.c_str(), "ERROR", MB_OK | MB_ICONASTERISK);
				}
				getline(f1, tmp1);
				numOtr = stoi(tmp1);

				//type of unit
				getline(f1, w, '=');
				if (w != "type")
				{
					MessageBox(NULL, L"Wrong type", L"ERROR", MB_OK | MB_ICONASTERISK);
					MessageBoxA(NULL, w.c_str(), "ERROR", MB_OK | MB_ICONASTERISK);
				}
				getline(f1, nazOtr);

				//sioldiers count
				getline(f1, w, '=');
				if (w != "soldiers") 
				{
					MessageBox(NULL, L"Wrong soldiers", L"ERROR", MB_OK | MB_ICONASTERISK);
					MessageBoxA(NULL, w.c_str(), "ERROR", MB_OK | MB_ICONASTERISK);
				}
				getline(f1, tmp1);
				kolvo = stoi(tmp1);

				//soldiers expierence
				getline(f1, w, '=');
				if (w != "exp")
				{
					MessageBox(NULL, L"Wrong exp", L"ERROR", MB_OK | MB_ICONASTERISK);
					MessageBoxA(NULL, w.c_str(), "ERROR", MB_OK | MB_ICONASTERISK);
				}
				getline(f1, tmp1);
				expi = stoi(tmp1);


				if (FastFuncts::setUnitSoldiers(bResults::stacksInBattle[armynum-1]->units[numOtr], kolvo, expi, nazOtr)==0)
				{
					MessageBox(NULL, L"Wrong unit", L"ERROR", MB_OK | MB_ICONASTERISK);
					return;
				}

			} while (1);
		}
	}

	f1.close();
	bResults::stacksInBattle.clear();
	MessageBoxA(NULL, "Done!", "Info", MB_OK | MB_ICONASTERISK);
/*	for (int i=0;i< battleStacks.size();i++)
	{
		for (int j = 0; j < battleStacks[i]->numOfUnits; j++)
		{
			if (battleStacks[i]->units[j]->number != 0)
			{
				unit* tmp = battleStacks[i]->units[j];
				battleStacks[i]->units[j] = battleStacks[i]->units[0];
				battleStacks[i]->units[0] = tmp;
				break;
			}
		}

	}*/


}

void bResults::grabPointers()
{
	//delete pointers
	bResults::stacksInBattle.clear();

	bResults::stacksInBattle = FastFuncts::getBattleStacksList();

	for (structs::arm* ar : bResults::stacksInBattle)
	{
		for (int i = 0; i < ar->army->numOfUnits; i++)
		{
			ar->units.push_back(ar->army->units[i]);
		}
	}

	if (stacksInBattle.size() == 0)
	{
		MessageBoxA(NULL, "No!", "Info!", NULL);
		return;
	}
	MessageBoxA(NULL, "Now you can do another actions!", "Info!", NULL);
}

int bResults::findStringV(vector<string>* v, string fac)
{
	for (string s : *v)
	{
		if (s == fac)return 1;
	}
	return 0;
}

void bResults::CreateBattleResultsFile()
{
	string fName = structs::cfg.modPatch;
	fName = fName + "\\youneuoy_Data\\battles_results\\";
	string battleName;
	if (FastFuncts::getSeason() == 0)
	{
		battleName = "summer";
	}
	else {
		battleName = "winter";
	}
	battleName = battleName + " ";
	battleName = battleName + to_string(FastFuncts::getYear());

	fName = fName + battleName;
	CreateDirectoryA(fName.c_str(), NULL);
	fName = fName + "\\";

	fName = fName + "battle_results.txt";

	ofstream f1(fName);
	f1 << "This file contains the results of the battle. It is created using M2TW Engine Overhaul Project. Do not modify the file structure.";
	
	for (structs::arm* ar : bResults::stacksInBattle)
	{
		f1 << endl << "army" << endl;
		int i = 0;
		for (unit* un : ar->units)
		{
			f1 << "unit" << endl
				<< "number in army=" << i << endl
				<< "type=" << readString((DWORD)un->eduEntry->Type) << endl
				<< "soldiers="
				<< un->number << endl
				<< "exp="
				<< un->expScreen<< endl;

			i++;
		}
	}

	MessageBoxA(NULL, "battle_results.txt created!", "Info!", NULL);
	f1.close();
}

void bResults::CreateBattleFile()
{
	struct alliance {
		vector<string>factions;
		vector<structs::arm*>armies;
		UINT32 side;
	};

	vector<alliance*>alliances;

	for (structs::arm* ar : bResults::stacksInBattle)
	{
		if (alliances.size() <= ar->side)
		{
			alliance* a = new alliance();
			alliances.push_back(a);
		}
		alliances[ar->side]->armies.push_back(ar);
		string fac = readString((DWORD)ar->army->faction->factName->name);
		if (findStringV(&alliances[ar->side]->factions, fac)) continue;
		alliances[ar->side]->factions.push_back(fac);
		alliances[ar->side]->side = ar->side;

	}

	vector<string>facSeen;

	string fName = structs::cfg.modPatch;
	fName = fName + "\\youneuoy_Data\\battles\\";
	string battleName;
	if (FastFuncts::getSeason() == 0)
	{
		battleName= "summer";
	}
	else {
		battleName= "winter";
	}
	battleName = battleName + "__";
	battleName = battleName + to_string(FastFuncts::getYear());

	fName = fName + battleName;
	CreateDirectoryA(fName.c_str(), NULL);
	fName = fName + "\\";
	fName= fName+	"descr_battle.txt";

	ofstream f1(fName);

	f1 << "; Generated by M2TW Engine Overhaul Project" << endl << endl;
	f1 << "battle		" << battleName << "		" << "multiplayer" << endl;
	f1 << "playable" << endl;
	for (structs::arm* ar : bResults::stacksInBattle)
	{
		string fac = readString((DWORD)ar->army->faction->factName->name);
		if (findStringV(&facSeen, fac)) continue;
		f1 << "	" << fac << endl;
		facSeen.push_back(fac);
	}
	f1 << "end" << endl;
	f1 << "nonplayable" << endl;
	f1 << "end" << endl << endl << endl;

	if (FastFuncts::getSeason() == 0)
	{
		f1 << "start_date	" << FastFuncts::getYear() << " " << "summer" << endl;
		f1 << "end_date	" << FastFuncts::getYear() << " " << "summer"  << endl << endl << endl;
	}
	else
	{
		f1 << "start_date	" << FastFuncts::getYear() << " " << "winter" << endl;
		f1 << "end_date	" << FastFuncts::getYear() << " " << "winter" << endl << endl << endl;
	}

	f1 << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;
	f1 << "; >>>> start of factions section <<<<" << endl << endl;

	facSeen.clear();

	for (structs::arm* ar : bResults::stacksInBattle)
	{
		string fac = readString((DWORD)ar->army->faction->factName->name);
		if (!findStringV(&facSeen, fac)) 
		{
			f1 << "faction	" << fac << endl;
			facSeen.push_back(fac);
		} 

		settlementStruct* sett = FastFuncts::checkSett(ar->army->gen->xCoord, ar->army->gen->yCoord,ar->army->faction);
		if (sett!=nullptr)
		{
			f1 << "settlement";
			if (sett->isCastle == 1)
			{
				f1 << " castle";
			}
			f1<< endl 
				<< "{" << endl;
			f1 << "	level "<< TechFuncts::getSettlLevel(sett->level)<<endl;
			f1 << "	tile " << sett->xCoord << ", " << sett->yCoord << endl;
			f1 << "	year_founded 0" << endl;
			f1 << "	population 999" << endl;
			f1 << "	plan_set default_set" << endl;
			f1 << "	faction_creator "<<FastFuncts::findFacByModNum(sett->fac_creatorModNum)<<endl;

				for(int bnum=0;bnum< sett->buldingsNum;bnum++)
				{ 
					f1 << "	building" << endl
						<< "	{" << endl;
					f1 << "		type " << readString((DWORD)sett->buildings[bnum]->bData->type)
						<<" "<< readString((DWORD)(sett->buildings[bnum]->bData->drawInfo[sett->buildings[bnum]->level].name))<<endl;
					f1 << "	}" << endl;
				}
			f1 << "}" << endl;
		}

		if (ar->army->gen)
		{
			UINT32 age = ar->army->gen->genChar->age >> 3 & 0xf7;
			string nm = readString((DWORD)ar->army->gen->genChar->fullName);
			if (nm == "")
				nm = "default";
			f1 << "character	" << nm
				<< ", named character, male";
			if (ar->army->gen->genChar->status & 2)
			{
				f1 << ", heir";
			}
			else if (ar->army->gen->genChar->status & 5)
			{
				f1 << ", leader";
			}
			f1<<", age " << age 
				<< ", x " << ar->army->gen->xCoord << ", y " << ar->army->gen->yCoord;
			if(ar->army->gen->genChar->portrait_custom)
				f1 << ", portrait " << readString((DWORD)ar->army->gen->genChar->portrait_custom);
			if (ar->army->gen->genChar->modelName)
				f1 << ", battle_model " << readString((DWORD)ar->army->gen->genChar->modelName);
			if (ar->army->gen->ability)
				f1 << ", hero_ability " << readString((DWORD)ar->army->gen->ability);
			if (ar->army->gen->genChar->label)
				f1 << ", label " << readString((DWORD)ar->army->gen->genChar->label);
			f1 << endl;

			if (ar->army->gen->genChar->traits)
			{
				f1<<FastFuncts::getTraits(ar->army->gen->genChar)<<endl;
			}
			if (ar->army->gen->genChar->anchNum != 0)
			{
				f1<< "ancillaries";
				UINT32 anchNum = ar->army->gen->genChar->anchNum;
				for (UINT32 i = 0; i < anchNum; i++)
				{
					string anch = readString((DWORD)ar->army->gen->genChar->anchillaries[i]->dataAnch->anchName);
					f1 << " " << anch << ",";
				}
			}

		}
		else
		{
			f1 << "character	default, general, male" << endl;
		}
		f1 << endl << "army" << endl;
		for (unit* un : ar->units)
		{
			f1 << "unit		"
				<< readString((DWORD)un->eduEntry->Type)
				<< "				soldiers "
				<< un->number
				<< " exp "
				<< un->expScreen
				<< " armour "
				<< ((un->stats>>0xd&0x1f))
				<< " weapon_lvl "
				<< ((un->stats >> 0x8 & 0x1f)) << endl;
		}
		f1 << endl;
	}
	f1 << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;
	f1 << "; >>>> start of battle section <<<<" << endl << endl;

	UINT32 bX = 0;
	UINT32 bY = 0;
	float time = 0;

	Read(structs::gameDataOffsets.battleStacksOffsetStart+0x18, &bX);
	Read(structs::gameDataOffsets.battleStacksOffsetStart+0x1c, &bY);
	Read(structs::gameDataOffsets.factionOffsetsStart+0x728, &time);

	f1 << "battle	" << bX << ", " << bY << endl;
	f1 << "battle_time	" << time << "	" << "0.00"<< endl;
	f1 << "weather	" << "clear" << endl << endl;

	f1 << "home_faction	" << readString((DWORD)bResults::stacksInBattle[0]->army->faction->factName->name) << endl;

	for (alliance* a : alliances)
	{
		f1 << "alliance	can_deploy	can_view	";
		for (string s : a->factions)
		{
			f1 << s<<",	";
		}
		if (a->armies[0]->ifDef == 0)
		{
			f1 << "attacking";
		}
		else 
		{
			f1 << "defending";
		}
		f1 << endl;
	}
	f1 << endl;

	for (alliance* a : alliances)
	{
		int k = 0;
		for (structs::arm* ar : a->armies)
		{
			f1 << "army	" << readString((DWORD)ar->army->faction->factName->name)
				<< ", " << k << ", " << "no_withdraw, supporting_armies 0" <<", reform_point "<<ar->army->reform_point_x<<", "<<ar->army->reform_point_y<< endl << endl;
			k++;

			UINT32 coorNum = 0;

			Read(ar->deploy +0xc, &coorNum);
			DWORD coor = 0;

			Read(ar->deploy +0x4, &coor);
			for (UINT32 kk = 0; kk < coorNum; kk++, coor += 8)
			{
				float x = 0;
				float y = 0;
				Read(coor, &x);
				Read(coor+0x4, &y);
				f1 << "deployment_area_point	" << x << ", " << y << endl;

			}
			f1 << endl;

			int otrn = 0;
			for (unit* un : ar->units)
			{
				while (1)
				{
					DWORD xc;
					DWORD yc;
					float x = 0;
					float y = 0;
					Read((DWORD)un + 0x5f4, &xc);
					Read(xc, &xc);
					Read(xc + 0x20, &y);
					Read(xc + 0x18, &x);
					if (x == 0 || y == 0) continue;
					f1 << "unit			"
						<< otrn
						<< ", "
						<< x
						<< ", "
						<< y
						<< ", "
						<< 0
						<< ", formation_type square, formation_width "
						<< 50;
					if (un->siegeEnNum>0&& un->siegeEnNum<10)
					{
						if (un->siegeEngine)
						{
							if ((*un->siegeEngine)->type == 2)
							{
								f1 << ", attach_engine ram";
							}
							else if ((*un->siegeEngine)->type == 4)
							{
								f1 << ", attach_engine ladder";
							}
							else if ((*un->siegeEngine)->type == 1)
							{
								f1 << ", attach_engine tower";
							}
						}
					}
					f1<< endl;
					otrn++;
					break;
				}
			}
			f1 << endl;
		}
	}
	f1 << endl << endl << endl << endl;
	f1 << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;
	f1 << "; >>>> start of objectives scripting section <<<<" << endl << endl;

	f1 << "objectives" << endl << endl;
	for (alliance* a : alliances)
	{
		f1 << "alliance "<<a->side << endl;
		if (a->armies[0]->condDest == 1)
		{
			f1 << "condition destroy_or_rout_enemy" << endl;
		}
		if (a->armies[0]->condSetl == 1)
		{
			f1 << "condition capture_major_settlement" << endl;
		}
		f1 << endl;
	}

	MessageBoxA(NULL, "descr_battle.txt created!", "Info!", NULL);
	f1.close();
}

void bResults::switchDraw()
{
	battleState = reinterpret_cast<int*>(structs::gameDataOffsets.battleStacksOffsetStart + 0x4);
	if (*battleState == 0 && !isDrawNedeed)return;
	if (isFuckGatesDrawNedeed)
	{
		isFuckGatesDrawNedeed = false;
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)msgFuckGates, 0, 0, 0));
	}

	isDrawNedeed = !isDrawNedeed;
}

void bResults::draw(LPDIRECT3DDEVICE9 pDevice)
{
	if (!isDrawNedeed)return;


	ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 0, 0, 20));
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("Battle Results window", &isDrawNedeed, window_flags);
	
	
	if (*battleState>1)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(1, 50, 32, 255));
		if (ImGui::Button("Battle loaded? Click here!"))
		{
			thread thrSMod(grabPointers);

			thrSMod.detach();
			//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)grabPointers, 0, 0, 0));
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Click after loading battle!");

		ImGui::PopStyleColor();
		if (ImGui::Button("Generate battle_results.txt"))
		{
			switchDraw();
			thread thrSMod(CreateBattleResultsFile);

			thrSMod.detach();
			//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CreateBattleResultsFile, 0, 0, 0));
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Generate file with battle results");

		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(1, 50, 32, 255));
		if (ImGui::Button("Generate descr_battle.txt"))
		{
			switchDraw();
			thread thrSMod(CreateBattleFile);

			thrSMod.detach();
			//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CreateBattleFile, 0, 0, 0));
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Generate file with battle");
		ImGui::PopStyleColor();
	}


	else if(*battleState ==1|| *battleState == 0)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(1, 50, 32, 255));
		if (ImGui::Button("Want to set battle_results? Click here"))
		{
			thread thrSMod(grabPointers);

			thrSMod.detach();
			//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)grabPointers, 0, 0, 0));
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Click only on the window before battle!");

		ImGui::PopStyleColor();

		if (ImGui::Button("Set battle_results!"))
		{		
			switchDraw();
			setBattleResults();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Do it only on the results screen!");
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void bResults::msgFuckGates()
{
	MessageBoxA(NULL, "For this function to work correctly, turn off the shadows in the game settings, otherwise you will get random crashes!", "Important info!", NULL);
}
