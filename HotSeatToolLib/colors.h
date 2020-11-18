#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <imgui.h>
#include "configFiles.h"
#include"overwritingValues.h"
using namespace std;

//colors, UI, etc
class colors
{
public:
	static struct colorSettings
	{
		ImVec4 text = { 1,1,1,1 };

	}menuColors;

	static void readColors();


	static struct uiSettings
	{
		int textSize=50;

	}uiSett;
	static void readUI();
};