#include "Myeffects.h"

vector<Myeffects::effect*> Myeffects::effectList;

void Myeffects::readEffects()
{
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\fixed_params\\effects.youneuoypar";

	ifstream f2(f);

	//for read events data
	string t1, t2, t3;
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findEffectPar(f);
		if (t != 1000) { continue; }
		else
		{
			if (t != 1000) break;
			Myeffects::effect* ef = new Myeffects::effect();

			while (1)
			{
				getline(f2, t1);
				if (findEffectPar(t1) != 2000) {
					MessageBoxA(NULL, "invalid effects.youneuoypar file!", "Error!", NULL);
					exit(0);
				}
				getline(f2, f);
				t = findEffectPar(f);
				if (t == 1) break;
				Myeffects::eff* oneEf = new Myeffects::eff();
				oneEf->type = t;

				if (t == 2||t==3||t==4||t==5)
				{
					getline(f2, f);
					oneEf->param = stoi(f);
					ef->effects.push_back(oneEf);
					continue;
				}
				
				else if (t == 1)
				{
					delete oneEf;
					continue;
				}
			}
			Myeffects::effectList.push_back(ef);
		}
	}
	f2.close();

	Keep::readInfo();


	for (Myeffects::effect* e : effectList)
	{
		for (Myeffects::eff* ef : e->effects)
		{
			makeEffString(ef);
		}
	}

	Localisation::readLoc();
	BigMenus::readMessageFiles();
}

int Myeffects::findEffectPar(string par)
{
	if (par == "nothing")
	{
		return 1;
	}
	else if (par == "money")
		return 2;
	else if (par == "loyality")
		return 3;
	else if (par == "loyality_char")
		return 4;
	else if (par == "authority_leader")
		return 5;

	else if (par == "heir_accepted")
		return 1000;
	else if(par == "effect")
		return 2000;
	return 0;
}

Myeffects::effect* Myeffects::getEffect(UINT32 id)
{
	if (effectList.size() < id) {
		MessageBoxA(NULL, "try to get invalid effect from id!", "Error!", NULL);
		ofstream f1("logs\\error.youneuoyerr");
		f1 << "error in :getEffect(UINT32 id), argument out of range, try to get:" << endl;
		f1 << id << endl;
		f1 << "elements:" << endl;
		for (Myeffects::effect* e : effectList)
		{
			f1 <<e->id << endl;
			for (Myeffects::eff* ef : e->effects)
			{
				f1 << ef->type << endl;
				f1 << ef->param << endl;
				f1 << ef->paramS << endl;
			}
		}
		f1.close();
		exit(0);
	}
	return effectList[id - 1];
}

void Myeffects::drawEffectList(UINT32 num, const char* tooltip)
{

	ImGui::BeginTooltip();
	ImGui::Text(tooltip);
	if (num != 0)
	{
		effect* ef = getEffect(num);
		for (Myeffects::eff* e : ef->effects)
		{
			ImGui::Text(e->paramS.c_str());
		}
	}
	ImGui::EndTooltip();
}

void Myeffects::makeEffString(eff* ef)
{
	if (ef->type == EFFECT_MONEY)
	{
		ef->paramS = to_string(ef->param);
		ef->paramS += " ";
		ef->paramS +=*Keep::getEffectLoc(LOC_EFFECTS_MONEY);
	}
	else if (ef->type == EFFECT_LOYALITY)
	{
		ef->paramS = to_string(ef->param);
		ef->paramS += " ";
		ef->paramS += *Keep::getEffectLoc(LOC_EFFECTS_LOYALITY);
	}
	else if (ef->type == EFFECT_LOYALITY_PERS)
	{
		ef->paramS = to_string(ef->param);
		ef->paramS += " ";
		ef->paramS += *Keep::getEffectLoc(LOC_EFFECTS_LOYALITY_PERS);
	}
	else if (ef->type == EFFECT_AUTHORITY_LEADER)
	{
		ef->paramS = to_string(ef->param);
		ef->paramS += " ";
		ef->paramS += *Keep::getEffectLoc(LOC_EFFECTS_AUTHORITY_LEADER);
	}
}

void Myeffects::setCharacterEffects(generalCharacterictics* gen, UINT32 num)
{
		effect* ef = getEffect(num);
		for (Myeffects::eff* e : ef->effects)
		{
			if (e->type == EFFECT_MONEY)
			{
				gen->faction->money += e->param;
			}
			else if (e->type == EFFECT_LOYALITY)
			{
				for (int i = 0; i < gen->faction->numOfCharacters; i++)
				{
					general* g = gen->faction->characters[i];
					if (g->bodyguards)
					{
						if (g->genChar->loyality + e->param <= 0)
						{
							g->genChar->loyality = 0;
						}
						else
						g->genChar->loyality+= e->param;
					}

				}
			}
			else if (e->type == EFFECT_LOYALITY_PERS)
			{
				if (gen->loyality + e->param <= 0)
				{
					gen->loyality = 0;
				}
				else
				gen->loyality+= e->param;
			}
			else if (e->type == EFFECT_AUTHORITY_LEADER)
			{
				if (gen->faction->leader->leaderAutority + e->param <= 0)
				{
					gen->faction->leader->leaderAutority = 0;
				}
				else
				gen->faction->leader->leaderAutority+= e->param;
			}

		}
}
