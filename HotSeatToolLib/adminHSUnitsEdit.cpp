#include "adminHSUnitsEdit.h"
adminHSUnitsEdit::adminHSUnitsEditData adminHSUnitsEdit::unitEditData;
string adminHSUnitsEdit::createStackName(stackStruct* stack)
{
	if (stack == nullptr)return "Attention! Here we have nullptr!";

	string ret = "Army ";
	if (stack->gen)
	{
		ret += "of ";
		if (stack->gen->genChar)
		{
			if (stack->gen->genChar->fullName)
			{
				ret += stack->gen->genChar->fullName;
			}
			else if (stack->gen->genChar->shortName)
			{
				ret += stack->gen->genChar->shortName;
			}
			else
			{
				ret += "name is missing";
			}
		}
		else
		{
			ret += "genChar is missing";
		}
	}
	else
	{
		ret += "gen is missing";
	}

	ret += ". Generals:";
	int genNum = 0;
	for (int i = 0; i < stack->numOfUnits; i++)
	{
		if (stack->units[i]->general)
		{
			genNum++;
		}
	}
	ret += to_string(genNum);
	ret += ", units:";
	ret += to_string(stack->numOfUnits);

	return ret;
}
void adminHSUnitsEdit::draw(LPDIRECT3DDEVICE9 pDevice)
{
	if (unitEditData.isDraw == false)return;


	int adr = 0;
	char adr2 = 0;
	char adr3 = 0;
	int adrT = 0;
	if (structs::cfg.gamever == 2)//steam
	{
		adr = *(int*)0x02c6d828;

		adr2= *(char*)0x01639f38;

		adrT = 0x02c2bf1c;
		Read((DWORD)adrT,&adrT,4);
		Read((DWORD)adrT +0x6f9,&adr3,1);
	}
	else if (structs::cfg.gamever == 1)
	{
		adr = *(int*)0x02cb6960;

		adr2 = *(char*)0x016818e8;

		adrT = 0x02c74fd4;
		Read((DWORD)adrT, &adrT, 4);
		Read((DWORD)adrT + 0x6f9, &adr3, 1);
	}
	if (adr != 0 && adr2 != 0)
	{
		if (adr3 == 0)
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
			ImGui::Begin("Logonpls window", &unitEditData.isDraw, window_flags);

			ImGui::Text("Use 'logon <password>' to enable with an administratorpassword. Otherwise, you will not be able to edit Ai armies");
			ImGui::End();
		}
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("adminHSUnitsEdit window", &unitEditData.isDraw, window_flags);

	if (ImGui::InputInt2("Army Coords", reinterpret_cast<int*>(&unitEditData.armyCoords)))
	{
		unitEditData.armiesAtCoords.clear();

		int numSkip = 0;
		stackStruct* retArm = nullptr;
		do
		{
			retArm = FastFuncts::getArmyOnCoords(unitEditData.armyCoords.x, unitEditData.armyCoords.y, numSkip);
			if (retArm != nullptr&& retArm->faction!=nullptr&&(retArm->faction->isPlayerControlled))
			{
				adminHSUnitsEdit::armStruct* armT = new adminHSUnitsEdit::armStruct();
				armT->stack = retArm;
				armT->stackName = createStackName(armT->stack);

				unitEditData.armiesAtCoords.push_back(armT);
			}
			numSkip++;
		} while (retArm != nullptr);
	}


	for (int i = 0; i < unitEditData.armiesAtCoords.size(); i++)
	{
		if (unitEditData.armiesAtCoords[i]->stack == nullptr)continue;
		if (ImGui::CollapsingHeader(unitEditData.armiesAtCoords[i]->stackName.c_str()) == true)
		{
			stackStruct* stackT = unitEditData.armiesAtCoords[i]->stack;
			for (int j = 0; j < stackT->numOfUnits; j++)
			{
				if (stackT->units[j] == nullptr
					|| stackT->units[j]->eduEntry == nullptr
					|| stackT->units[j]->eduEntry->Type == nullptr
					) continue;

				unitData unitDT;
				unitDT.num = stackT->units[j]->number;
				unitDT.exp = stackT->units[j]->expScreen;

				ImGui::PushID(stackT->units[j]);
				if (ImGui::InputInt2("Number/exp", reinterpret_cast<int*>(&unitDT)))
				{
					unitEdited(stackT->units[j], &unitDT);
				}
				ImGui::SameLine();
				if (ImGui::CollapsingHeader(stackT->units[j]->eduEntry->Type) == true)
				{
					if (ImGui::Button("Kill"))
					{
						FastFuncts::killUnit(stackT->units[j]);
						unitEditData.armiesAtCoords[i]->stackName = createStackName(stackT);
					}
				}
				ImGui::PopID();
			}
			if (stackT->numOfUnits < 20)
			{
				ImGui::NewLine();
				ImGui::InputText("Types filter",unitEditData.unCreateFilter,200);
				ImGui::InputInt3("Exp/arm/weap", reinterpret_cast<int*>(&unitEditData.newUnitD));

				if (ImGui::CollapsingHeader("Create new unit"))
				{
					eduEntryes* EDB = reinterpret_cast<eduEntryes*>(structs::gameDataOffsets.unitTypesStart - 4);

					int unitsNum = EDB->numberOfTupes;
					for (int k = 0; k < unitsNum; k++)
					{
						if (strlen(unitEditData.unCreateFilter) == 0
							||
							strstr(EDB->unitTupes[k].Type, unitEditData.unCreateFilter)
							)
						{
							if (ImGui::Button(EDB->unitTupes[k].Type))
							{
								//int facNum = FastFuncts::getFactionIndexByDipNum(stackT->faction->dipNum);
								unit* newUn = FastFuncts::createUnitN(EDB->unitTupes[k].Type, stackT->faction->dipNum, unitEditData.newUnitD.exp, unitEditData.newUnitD.arm, unitEditData.newUnitD.weapon);
								FastFuncts::addUnitToArmy(newUn, stackT);
								unitEditData.armiesAtCoords[i]->stackName = createStackName(stackT);
							}
						}
					}
				}
			}

		}
	}

	ImGui::End();
}

void adminHSUnitsEdit::switchDraw()
{
	unitEditData.armiesAtCoords.clear();
	unitEditData.isDraw = !unitEditData.isDraw;
}

void adminHSUnitsEdit::unitEdited(unit* un, unitData* unData)
{
	if (unData->num < 0
		|| unData->num>300
		)
	{
		unData->num = un->numberMax;
	}
	if (unData->exp < 0
		|| unData->exp>9
		)
	{
		unData->exp = 0;
	}

	FastFuncts::setUnitSoldiersAdvanced(un, unData->num, unData->exp);
}
