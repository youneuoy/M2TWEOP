#include "Drawer.h"

bool Drawer::drawMain = true;
bool Drawer::drawFAQ = false;
bool Drawer::drawCredits = false;
void Drawer::mainMenu(LPDIRECT3DDEVICE9 pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;


		ImGui::SetNextWindowPos(ImVec2(0, 0));

		//startup.youneuoycfg
		ImGui::Begin("startup.youneuoycfg window", &drawMain, window_flags);

		ImGui::Text("Your startup.youneuoycfg:");

		ImGui::InputText("config file name", Startup::cfg.modCFGName, sizeof(Startup::cfg.modCFGName));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfg.modCFGNameTip.c_str());

		if (ImGui::SliderInt("music volume", &Startup::cfg.musicVolume, 0, 100))
		{
			music::setVolume(Startup::cfg.musicVolume);
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfg.musicVolumeTip.c_str());

		if (ImGui::Checkbox("display configs", &Startup::cfg.startTypeB))
		{
			if (Startup::cfg.startTypeB==false)
			{
				drawMain = false;
			}
			else
			{
				drawMain = true;
			}
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfg.startTypeTip.c_str());

		/*ImGui::InputText("display configs", Startup::cfg.startType, sizeof(Startup::cfg.startType));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfg.startTypeTip.c_str());*/
		ImGui::Separator();

		ImGui::Text("Your game config:");

		//antialiasing

		const char* names[] = { "disabled", "x2", "x4", "x8" };

		if (ImGui::Button("antialiasing"))
			ImGui::OpenPopup("antialias_popup");
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::gameConfig.antialiasingTip.c_str());
		ImGui::SameLine();
		ImGui::TextUnformatted(names[Startup::gameConfig.antialiasing]);
		if (ImGui::BeginPopup("antialias_popup"))
		{
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
					Startup::gameConfig.antialiasing = i;
			ImGui::EndPopup();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::gameConfig.antialiasingTip.c_str());

		ImGui::Checkbox("borderless window", &Startup::gameConfig.borderlWindow);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::gameConfig.borderlWindowTip.c_str());

		ImGui::Checkbox("use desktop resolution", &Startup::gameConfig.destkopResolution);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::gameConfig.destkopResolutionTip.c_str());

		ImGui::Checkbox("use this settings", &Startup::gameConfig.applyGameConfig);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::gameConfig.applyGameConfigTip.c_str());

		if (ImGui::Checkbox("dont show menu at start", &Startup::cfg.justStartMod))
		{
			MessageBoxA(NULL, "You can disable this in config file later", "Attention", NULL);
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfg.justStartModTip.c_str());

		ImGui::End();

		if (drawMain)
		{
		//modConfig.youneuoycfg
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 1.0f, io.DisplaySize.y * 0.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
		ImGui::Begin("modConfig.youneuoycfg window", &drawMain, window_flags);

		ImGui::Text("Your modConfig.youneuoycfg:");
		ImGui::InputText("language", Startup::modCfg.langP, sizeof(Startup::modCfg.langP));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.langPTip.c_str());

		ImGui::InputText("max bodyguard size", Startup::modCfg.maxBodSize, sizeof(Startup::modCfg.maxBodSize));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.maxBodSizeTip.c_str());

		ImGui::InputText("legio string", Startup::modCfg.legioString, sizeof(Startup::modCfg.legioString));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.legioStringTip.c_str());


		ImGui::Checkbox("full logging", &Startup::modCfg.fullLoggingB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.fullLoggingTip.c_str());

	/*	ImGui::InputText("full logging", Startup::modCfg.fullLogging, sizeof(Startup::modCfg.fullLogging));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.fullLoggingTip.c_str());*/

		ImGui::Checkbox("unlock change_faction", &Startup::modCfg.unlockChangeFactionB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.unlockChangeFactionTip.c_str());

		/*ImGui::InputText("unlock change_faction", Startup::modCfg.unlockChangeFaction, sizeof(Startup::modCfg.unlockChangeFaction));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.unlockChangeFactionTip.c_str());*/

		ImGui::Checkbox("berserks fix", &Startup::modCfg.bersPatchB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.bersPatchTip.c_str());

		/*ImGui::InputText("berserks fix", Startup::modCfg.bersPatch, sizeof(Startup::modCfg.bersPatch));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.bersPatchTip.c_str());*/

		ImGui::Checkbox("soldiers count fix", &Startup::modCfg.histBattleFixB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.histBattleFixTip.c_str());

		/*ImGui::InputText("soldiers count fix", Startup::modCfg.histBattleFix, sizeof(Startup::modCfg.histBattleFix));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.histBattleFixTip.c_str());*/

		ImGui::Checkbox("creatures fix", &Startup::modCfg.DCIB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.DCITip.c_str());

		/*ImGui::InputText("creatures fix", Startup::modCfg.DCI, sizeof(Startup::modCfg.DCI));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.DCITip.c_str());*/

		ImGui::Checkbox("new family tree elements", &Startup::modCfg.characterUIMenusB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.characterUIMenusTip.c_str());

		/*ImGui::InputText("new family tree elements", Startup::modCfg.characterUIMenus, sizeof(Startup::modCfg.characterUIMenus));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.characterUIMenusTip.c_str());*/

		ImGui::Checkbox("spawn_army fix", &Startup::modCfg.spawnArmyCoordsB);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.spawnArmyCoordsTip.c_str());

		ImGui::Checkbox("unlock console commands", &Startup::modCfg.unlockConsoleCommands);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.unlockConsoleCommandsTip.c_str());
		/*ImGui::InputText("spawn_army fix", Startup::modCfg.spawnArmyCoords, sizeof(Startup::modCfg.spawnArmyCoords));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::modCfg.spawnArmyCoordsTip.c_str());
			*/

		if (ImGui::Button("Apply changes"))
		{
			Startup::writeModCfg();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Apply changes and write new config file");

		ImGui::End();



		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.0f, io.DisplaySize.y * 1.0f), ImGuiCond_Always, ImVec2(0.0f, 1.0f));


		ImGui::Begin("limits.youneuoycfg window", &drawMain, window_flags);
		ImGui::Text("Your limits.youneuoycfg:");

		ImGui::InputText("religion Limit", Startup::cfgLimits.Religion_Limit, sizeof(Startup::cfgLimits.Religion_Limit));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Religion_LimitTip.c_str());

		ImGui::InputText("ancillaries Limit", Startup::cfgLimits.Ancillaries_Limit, sizeof(Startup::cfgLimits.Ancillaries_Limit));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Ancillaries_LimitTip.c_str());

		ImGui::InputText("lock unit size", Startup::cfgLimits.Lock_Size_Of_Unit, sizeof(Startup::cfgLimits.Lock_Size_Of_Unit));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Lock_Size_Of_UnitTip.c_str());


		ImGui::InputText("unit size", Startup::cfgLimits.Size_Of_Unit, sizeof(Startup::cfgLimits.Size_Of_Unit));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Size_Of_UnitTip.c_str());


		ImGui::InputText("min soldiers", Startup::cfgLimits.Min_Soldiers_In_Edu, sizeof(Startup::cfgLimits.Min_Soldiers_In_Edu));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Min_Soldiers_In_EduTip.c_str());

		ImGui::InputText("max soldiers", Startup::cfgLimits.Max_Soldiers_In_Edu, sizeof(Startup::cfgLimits.Max_Soldiers_In_Edu));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Max_Soldiers_In_EduTip.c_str());

		ImGui::SliderInt("battlefield size X", &Startup::cfgLimits.Battlefield_Map_Size_X, 500, 2000);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Battlefield_Map_Size_XTip.c_str());

		ImGui::SliderInt("battlefield size Y", &Startup::cfgLimits.Battlefield_Map_Size_Y, 500, 2000);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Battlefield_Map_Size_YTip.c_str());
		/*ImGui::InputText("battlefield size X", Startup::cfgLimits.Battlefield_Map_Size_X, sizeof(Startup::cfgLimits.Battlefield_Map_Size_X));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Battlefield_Map_Size_XTip.c_str());

		ImGui::InputText("battlefield size Y", Startup::cfgLimits.Battlefield_Map_Size_Y, sizeof(Startup::cfgLimits.Battlefield_Map_Size_Y));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Battlefield_Map_Size_YTip.c_str());*/

		ImGui::InputText("siege ram cost", Startup::cfgLimits.Siege_Ram_Cost, sizeof(Startup::cfgLimits.Siege_Ram_Cost));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Siege_Ram_CostTip.c_str());

		ImGui::InputText("siege ladder cost", Startup::cfgLimits.Siege_Ladder_Cost, sizeof(Startup::cfgLimits.Siege_Ladder_Cost));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Siege_Ladder_CostTip.c_str());

		ImGui::InputText("siege tower cost", Startup::cfgLimits.Siege_Tower_Cost, sizeof(Startup::cfgLimits.Siege_Tower_Cost));
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Startup::cfgLimits.Siege_Tower_CostTip.c_str());

		if (ImGui::Button("Apply changes"))
		{
			Startup::writeLimits();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Apply changes and write new config file");

		ImGui::End();

	}



	

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImGui::Begin("Main window", NULL, window_flags);
	if (ImGui::Button("Start mod"))
	{
		UINT32 res = Startup::runMod();
		if (res <= 32)
		{
			wstring s = to_wstring(res);
			MessageBoxW(NULL, L"Something goes wrong!", s.c_str(), NULL);
		}
		else {
			injector::start();
		}
		if (Startup::cfg.closeAfterStart == true)
			exit(0);
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Run mod");

	if (ImGui::Button("Start vanilla"))
	{
		UINT32 res = Startup::runVanilla();
		if (res <= 32)
		{
			wstring s = to_wstring(res);
			MessageBoxW(NULL, L"Something goes wrong!", s.c_str(), NULL);
		}
		else {
			injector::start();
		}
		if (Startup::cfg.closeAfterStart == true)
			exit(0);
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Run vanilla, works with steam version only!");

	ImGui::Checkbox("Close program after game start", &Startup::cfg.closeAfterStart);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Dont check if you want start multiple copies of game, etc.");

	if (ImGui::Button("Click me!"))
	{
		Drawer::drawFAQ = true;
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Very very important info here!");

	/*if (ImGui::Button("Credits"))
	{
		Drawer::drawCredits = true;
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("List of those involved in the development, as well as thanks");
		*/

	ImGui::End();

	//info(down menu)
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 1.0f), ImGuiCond_Always, ImVec2(0.5f, 1.0f));
	ImGui::Begin("Info window", NULL, window_flags);

	ImGui::Text(Startup::gameInfo.currentMod);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(Startup::gameInfo.currentModTip.c_str());


	ImGui::Text(Startup::gameInfo.filePatch);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(Startup::gameInfo.filePatchTip.c_str());

	ImGui::Text(Startup::gameInfo.ver.c_str());
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(Startup::gameInfo.verTip.c_str());

	ImGui::End();

	if (Drawer::drawFAQ)
		Drawer::FAQ(pDevice);

	/*if (Drawer::drawCredits)
		Drawer::credits(pDevice);
		*/
}

void Drawer::FAQ(LPDIRECT3DDEVICE9 pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;


	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImGui::Begin("FAQ window", NULL, window_flags);
	ImGui::Text("Have problems? Want know more? Read it:\n");


	ImGui::Text("Use borderless windowed(or just windowed)game mode only.\nFulscreen=crashes!\n\n");

	ImGui::Text("Change antialiasing level in config file only.\nChange antialiasing in game menu=crash!\n\n");

	ImGui::Text("If you generate battle file or get battle results then disable shadows in game settings.\nShadows+inbattle program menu=crashes!\n\n");


	ImGui::Text("Keyboard shortcuts:\n");

	ImGui::Text("Ctrl+Q - highlighting units in battle\n\n");
	ImGui::Text("Ctrl+Z - Battle map strategic overview (does not work with tw camera)\n\n");
	ImGui::Text("Ctrl+V - Create battle / get results / apply results. Useful for hotseats.\n\n");

	if (ImGui::Button("Visit subforum of project on twcenter.net"))
	{
		UINT32 res = (UINT32)ShellExecuteA(NULL, "open", "https://www.twcenter.net/forums/forumdisplay.php?2296-M2TW-Engine-Overhaul-Project", NULL, NULL, SW_SHOWNORMAL);
		if (res <= 32)
		{
			string s = to_string(res);
			MessageBoxA(NULL, "Something goes wrong!", s.c_str(), NULL);
		}
	}

	if (ImGui::Button("OK"))
	{
		Drawer::drawFAQ = false;
	}


	ImGui::End();
}

void Drawer::credits(LPDIRECT3DDEVICE9 pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;


	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImGui::Begin("Credits window", NULL, window_flags);
	ImGui::Text("Developers:\n");


	ImGui::Text("youneuoy\n\n");

	ImGui::Text("Participation in development:\n");

	ImGui::Text("Jojo00182\n\n");

	ImGui::Text("Many thanks to\n");
	ImGui::Text("anyone who expresses support for the project. Here are some of them:\n");
	ImGui::Text("Jadli\n\nXamax\n\nLord Baal\n\nErken\n\nleo.civil.uefs\n\nDinarMayor\n\n");


	if (ImGui::Button("Visit subforum of project on twcenter.net"))
	{
		ShellExecuteA(NULL, "open", "https://www.twcenter.net/forums/forumdisplay.php?2296-M2TW-Engine-Overhaul-Project", NULL, NULL, SW_SHOWNORMAL);
	}

	if (ImGui::Button("OK"))
	{
		Drawer::drawCredits = false;
	}


	ImGui::End();
}
