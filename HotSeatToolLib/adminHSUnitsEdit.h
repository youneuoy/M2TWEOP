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
#include <thread>
using namespace std;


class adminHSUnitsEdit
{
public:
	struct xyStruct
	{
		int x=0;
		int y=0;
	};
	struct unitData
	{
		int num=0;
		int exp = 0;
	};

	struct newUnitData
	{
		int exp=0;
		int arm=0;
		int weapon=0;
	};

	struct  armStruct
	{
		stackStruct* stack;
		string stackName;
	};


	static string createStackName(stackStruct* stack);
	static void draw(LPDIRECT3DDEVICE9 pDevice);
	static void switchDraw();
private:
	static void unitEdited(unit* un, unitData* unData);

	static struct adminHSUnitsEditData
	{
		bool isDraw = false;

		xyStruct armyCoords;
		vector<armStruct*> armiesAtCoords;

		char unCreateFilter[200] = { 0 };
		newUnitData newUnitD;
	}unitEditData;
};
