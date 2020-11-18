#include "modManager.h"
modManager::mds modManager::mods;
void modManager::findMods(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	vector<string> folders= fsystem::getAllSubFolders(mods.modFolder);

	int num = 0;
	for (string s : folders)
	{

		string modFolder = mods.modFolder + "\\" + s;
		if (!mod::ifMod(modFolder))continue;

		mod* md = new mod();
		md->initMod(modFolder, g_pd3dDevice);
		mods.list.push_back(md);
	}
}

void modManager::run(LPDIRECT3DDEVICE9 g_pd3dDevice, char* path)
{
	char* tmp = new char[strlen(path)];
	strcpy(tmp, path);
	PathRemoveFileSpec(path);
	mods.modFolder = path;
	mods.modFolder = mods.modFolder + "\\mods";
	findMods(g_pd3dDevice);

	int curr = -1;
	for (mod* md : mods.list)
	{
		curr++;
		if (md->name == mods.lastMod)
		{
			modManager::mods.selected = curr;
			return;
		}
	}
}

int modManager::Draw(LPDIRECT3DDEVICE9 g_pd3dDevice, bool* isdraw)
{
	int refreshMod = 0;

	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;


	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.0f), ImGuiCond_Always, ImVec2(0.5f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("modmanager window", NULL, window_flags);
	ImGui::Text("Your mods:\n\n");

	for (int i = 0; i < mods.list.size(); i++)
	{

		ImGui::BeginChild(mods.list[i]->name.c_str(), ImVec2(0, 128), false);
		ImGui::TextWrapped(mods.list[i]->name.c_str());
		ImGui::Image(mods.list[i]->image.texture, ImVec2(64, 64));
		ImGui::SameLine();
		//ImGui::TextWrapped(mods.list[i]->descr.c_str());

		if (ImGui::Button("Open project info link or file"))
		{
			UINT32 res = (UINT32)ShellExecuteA(NULL, "open", mods.list[i]->link.c_str(), NULL, NULL, SW_SHOWNORMAL);
			if (res <= 32)
			{
				string s = to_string(res);
				MessageBoxA(NULL, "Something goes wrong!", s.c_str(), NULL);
			}
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(mods.list[i]->link.c_str());

		if (ImGui::Button("Select this mod"))
		{
			mods.selected = i;
			refreshMod = 1;
			*isdraw = false;
		}
		ImGui::EndChild();
	}


	if (ImGui::Button("Close"))
	{
		*isdraw = false;
	}


	ImGui::End();


	return refreshMod;
}

int modManager::updateBackgroundTexture(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	if (mods.list[mods.selected]->EOP)
	{
		string p = mods.list[mods.selected]->path+"\\youneuoy_Data\\M2TWEOP.dds";
		if (static_cast<bool>(std::ifstream(p)))
		{
			mods.background->Release();
			fsystem::loadTexture(&p, &mods.background, g_pd3dDevice);
			return 1;
		}
	}
	return 0;
}

void modManager::writeLastMod(char* path)
{
	string s = path;
	s = s+"\\preferences.youneuoycfg";
	ofstream f1(s);

	f1<<";Generated by M2TWEOP!"<< endl;
	f1 << "lastMod = \"" << mods.list[mods.selected]->name << "\"" << endl;

	f1.close();

}

void modManager::loadLastMod(char* path)
{
	string s = path;
	s= s + "\\preferences.youneuoycfg";


	ifstream f1(s);
	while (f1.good())
	{
		getline(f1, s);

		Params::readStringInQuotes(&mods.lastMod, s, "lastMod");
	}

	f1.close();


}

