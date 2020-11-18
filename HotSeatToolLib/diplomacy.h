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

class diplomacy
{
public:

	static void readDipFile();

	static int checkAndChangeFacDip(CompareCounter* compareCounter=0, int counter=0);

	static void checkAndChangeDips();

	static void checkAndChangeDipsCompareCounter(CompareCounter* compareCounter, int counter);

	static int compareCounterValue(int counterV, int operation, int checkV);

	static int WINAPI checkDipString();

	//at DiplomaticStanceFromFaction
	static int WINAPI checkFacDip();
};

