#pragma once


#include <string>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <fstream>
#include <shlwapi.h>

#pragma comment(lib,"Version.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Psapi.lib")
#include "Params.h"
#include "music.h"
using namespace std;
class Startup
{
public:
	//startup
	static struct config {
		char modCFGName[128];
		string modCFGNameTip = ";Name of your config file(dont used for vanilla)";

		int musicVolume;
		string musicVolumeTip=";volume of music in the launcher";

		bool startTypeB;
		string startTypeTip = ";show config windows-1, show only start buttons - 0";

		bool closeAfterStart=true;

		bool justStartMod = false;
		string justStartModTip = ";dont show menu, just start mod";
	}cfg;
	

	static struct  cfgStructLim {
		char Religion_Limit[4];
		string Religion_LimitTip = ";Religions limit. Change only if you need it!";

		char Ancillaries_Limit[4];
		string Ancillaries_LimitTip = ";Ancillaries limit for each character";
		
		char Lock_Size_Of_Unit[2];
		string Lock_Size_Of_UnitTip = ";Disable changing of unit size from game settings. Use only if you need it!";
		
		char Size_Of_Unit[2];
		string Size_Of_UnitTip = ";Set unit size. Used only with lock unit size!";
				
		char Min_Soldiers_In_Edu[4];
		string Min_Soldiers_In_EduTip = ";Minimum soldiers number in unit in EDU. Change only if you need it!";
						
		char Max_Soldiers_In_Edu[4];
		string Max_Soldiers_In_EduTip = ";Maximum soldiers number in unit in EDU. Change only if you need it!";
								
		//char Battlefield_Map_Size_X[5];
		int Battlefield_Map_Size_X;
		string Battlefield_Map_Size_XTip = ";X size of battlefield. Change only if you need it!";
										
		//char Battlefield_Map_Size_Y[5];
		int Battlefield_Map_Size_Y;
		string Battlefield_Map_Size_YTip = ";Y size of battlefield. Change only if you need it!";
												
		char Siege_Ram_Cost[5];
		string Siege_Ram_CostTip = ";Cost of siege ram";
														
		char Siege_Ladder_Cost[5];
		string Siege_Ladder_CostTip = ";Cost of siege ladder";
																
		char Siege_Tower_Cost[5];
		string Siege_Tower_CostTip = ";Cost of siege tower";

	}cfgLimits;

	static struct  cfgStructType {

		char langP[128];
		string langPTip = ";Language path(example youneuoy_Data\\localisation\\ENG)";

		bool fullLoggingB;
		string fullLoggingTip = ";Enable full logging(file all.youneuoylog), 0 or 1 \n;Break perfomance!";

		bool unlockChangeFactionB;
		string unlockChangeFactionTip = ";unlock console command change faction in singleplayer game, 0 or 1\n;Enable only if you need it!";

		//berserkers crach fix
		bool bersPatchB;
		string bersPatchTip = ";berserkers crach fix, 0 or 1";

		//online history battles fix
		bool histBattleFixB;
		string histBattleFixTip = ";fix for soldiers numbers in units for history battles\n;Also allow set your own soldiers count in descr_strat.\n;Needed if in units in battle not standard number of soldiers\n;, without this fix in this case units have full number of soldiers";

		bool DCIB;
		string DCITip = ";Creatures crash fix\n;Enable only if you need it!";

		//character ui functions
		bool characterUIMenusB;
		string characterUIMenusTip=";family tree menus enable/disable(make heir, etc)";

		//allow spawn_army changes
		bool spawnArmyCoordsB;
		string spawnArmyCoordsTip=";Allow use spawn_army at ports coods";

		//unlock console commands
		bool unlockConsoleCommands;
		string unlockConsoleCommandsTip = ";Unlock all console commands.\n;If you turn on full logging, when in the game logs folder appear file with commands list and tips";

		//bodyguard replenish max count
		char maxBodSize [3];
		string maxBodSizeTip = ";maximum bodyguard size(this value*multiplier from units size(max = 2.5))\n;if MaxBodyguardSize=31 then on maximum units size count is 31*2.5(77)";

		//overwritingValues:
		char legioString[128];
		string legioStringTip=";owerwrite \"Legio \" string";
	}modCfg;

	static struct gameInfoS {
		char* filePatch;
		string filePatchTip = "Executable file of M2TW";
		string ver;
		string verTip="Version of the game";
		char* currentMod;
		string currentModTip="Patch of the mod";

		int v;
	}gameInfo;



	static struct gameCfg {
		int antialiasing=1;
		string antialiasingTip="It is recommended to adjust the level of anti-aliasing here. \nBy setting it up in the game, you will most likely get a crash.";

		bool borderlWindow = true;
		string borderlWindowTip = "Enable borderless window mode. It is highly recommended to leave activated";

		bool destkopResolution = true;
		string destkopResolutionTip = "Set the destkop resolution for game. It is highly recommended to leave activated";

		bool applyGameConfig=true;
		string applyGameConfigTip = "It is highly recommended to leave activated";
	}gameConfig;

	static void loadParams();

	static void startP();

	static void writeStartup();

	static void writeModCfg();

	static void writeLimits();

	static int getGameInfo();

	static int runMod();

	static int runVanilla();

	static void writeGameCfg(int ifmod);

	
private:
	static string findMTW(string s,int* ver);

	static vector<string> findFile(string folder, string fileName);

	static void createModInfoFile();


	static int getVersion(LPCSTR file);
};

