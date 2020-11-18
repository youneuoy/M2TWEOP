#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 
#include "graphicsD3D.h"
#include "BigMenus.h"
#include "Myeffects.h"
using namespace std;
//manager and drawer of the tooltips


class tipsEs
{
public:
	static bool hCheck;

	static int strNum;

	static vector<string> tipS;

	static void readTips();

	static bool drawTip;

	static void draw(LPDIRECT3DDEVICE9 pDevice);

	static void checkDraws(void);

	static void startChecks(UINT32 some);

	

	static int checkFamTree();
};

