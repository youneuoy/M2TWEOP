#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 


using namespace std;
class customTiles
{
public:
	static struct dataCustomS
	{
		vector<custom_tile*>eopCustomTiles;
	}customTilesData;

	static void __fastcall onTileCheck(int* coords);

	static void __stdcall readTilesFile();
};

