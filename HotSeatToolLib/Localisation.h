#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 
#include "overwritingValues.h"
#include <imgui.h>
//buttons
#define LOC_BUTTON_MAKE_HEIR 1
#define LOC_BUTTON_CANCEL 2
//messages
#define LOC_BIG_MESS_HEIR_ACCEPTED 1

struct locA {
	UINT32 id;
	string info;
	string tooltip;

	ImVec2 size;
};
class Localisation
{
public:
	static vector<locA*>locsMes;

	static vector<locA*>locsBut;

	static void readLoc();

	static locA* getLocMes(UINT32 id);

	static locA* getLocBut(UINT32 id);

	static void calcLocSize(vector<locA*>* v);
};

