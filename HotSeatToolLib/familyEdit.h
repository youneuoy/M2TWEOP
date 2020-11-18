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
#include "tipsEs.h"
using namespace std;
class familyEdit
{
public:
	static generalCharacterictics* prs;
	static void enableHeirMenu(generalCharacterictics* pers);

	static POINT p;
	static ImVec2 size;

	static bool persCh;

	static void draw(LPDIRECT3DDEVICE9 pDevice);

	static int checkDrawCond();

	static void checkDisableDrawCond(int checkCoords=0);

	static void calcButtSize();
};

