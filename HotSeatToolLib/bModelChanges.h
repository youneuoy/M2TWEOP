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
class bModelChanges
{
public:

	static void readModelsFile();

	static void checkAndChangeModels();

	static int checkAndChangeCharModel(general* gen);
};

