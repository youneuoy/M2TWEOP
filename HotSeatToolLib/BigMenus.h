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
#include "TechFuncts.h"
#include "Localisation.h"
#include "TechnicalTreadFuncs.h"
#define BIG_MENU_MES_HEIR 1
using namespace std;
class BigMenus
{
public:
	static bool isDrawNedeed;

	static struct screenInfo {
		D3DDEVICE_CREATION_PARAMETERS cparams;
		RECT rect;

		float resCoef;
	}screenParams;

	struct menuStruct {
		UINT32 weight;
		UINT32 height;

		locA* message;
		LPDIRECT3DTEXTURE9 image;
	};


	static vector<menuStruct*>messages;

	static struct menuDrawStruct {
		//BIG scroll params
		UINT32 x;
		UINT32 y;
		UINT32 weight;
		UINT32 height;
		LPDIRECT3DTEXTURE9 bigScroll;
		//image on the top of the scroll params
		UINT32 xImg;
		UINT32 yImg;

		//close button
		UINT32 xCloseBut;
		UINT32 yCloseBut;
		UINT32 weightCloseBut;
		UINT32 heightCloseBut;
		//text
		UINT32 xText;
		UINT32 yText;
		UINT32 weightText;
		UINT32 heightText;

		UINT32 drawCode=0;
	}drawParams;


	static void readMessageFiles();

	static void calcWindowPos();

	static void showMessage(int id);

	static void Draw(LPDIRECT3DDEVICE9 pDevice);

	static void stopShowMessage();

};

