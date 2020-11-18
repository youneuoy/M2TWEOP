#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h"
#include <d3d9.h>
#include <imgui.h>
#include <imfilebrowser.h>
#include <thread>
using namespace std;



class bResults {
public:
	static bool isDrawNedeed;
	static bool isFuckGatesDrawNedeed;
	
	static int* battleState;

	static void setBattleResults();

	static vector<structs::arm*>stacksInBattle;
	//get poiters before battle
	static void grabPointers();

	static int findStringV(vector<string>* v,string fac);

	static void CreateBattleResultsFile();

	static void CreateBattleFile();

	static void switchDraw();

	static void draw(LPDIRECT3DDEVICE9 pDevice);

	static void msgFuckGates();
};

