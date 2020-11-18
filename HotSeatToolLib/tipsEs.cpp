#include "tipsEs.h"
bool tipsEs::drawTip = false;
bool tipsEs::hCheck = false;
int tipsEs::strNum = 0;
vector<string> tipsEs::tipS;
void tipsEs::readTips()
{
	string f = structs::cfg.langP + "\\" + "tips.youneuoyloc";

	string s;
	ifstream f2(f);
	UINT32 n = 0;
	while (f2.good())
	{
		getline(f2, s);
		if (s[0] == ';')continue;

		readStringInQuotes(&f, s, "tooltip string");
		tipS.push_back(f);
	}

	f2.close();
}
void tipsEs::draw(LPDIRECT3DDEVICE9 pDevice)
{
	if (!drawTip)return;
	POINT p;
	getCPos(&p);


	ImGui::SetNextWindowPos(ImVec2(p.x + 10, p.y + 10));
	ImGui::SetNextWindowBgAlpha(0.f);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize| ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::Begin("Tips window:", &drawTip, window_flags); 
	Myeffects::drawEffectList(0, tipS[strNum - 1].c_str());
	ImGui::End();

}

void tipsEs::checkDraws(void)
{
	hCheck = true;
	while (1) 
	{
		Sleep(100);
		if (structs::cfg.characterUIMenus == 1)
		{
			if (
				checkFamTree()
				&&
				!familyEdit::persCh
				)
			{
				strNum = 1;
				drawTip = true;
				continue;
			}
		}
		drawTip = false;
		strNum = 0;
	}
}

void tipsEs::startChecks(UINT32 some)
{
	readTips();
	if (some == 1)
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)checkDraws, NULL, 0, nullptr));
	}
}

int tipsEs::checkFamTree()
{

	UINT32 tree;
	Read(structs::gameDataOffsets.stratUiOffset, &tree);

	if (!tree)return 0;
	Read(tree + 0xec, &tree);

	if (!tree)return 0;
	Read(tree + 0x44c, &tree);

	if (!tree)return 0;
	generalCharacterictics* prs = reinterpret_cast<generalCharacterictics*>(tree);

	if (!(prs->age & 1))return 0;

	return 1;
}
