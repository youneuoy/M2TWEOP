#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "MemWork.h"
#include"configFiles.h"
#include "Injects.h"


class owW {
public:
	static struct config {
		int religionLimit = 10;
		int ancillariesLimit = 8;
		int lockSizeOfUnit = 0;
		int sizeOfUnit = 0;
		INT16 minSoldiersEdu = 4;
		INT16 maxSoldiersEdu = 100;
		float battlefieldMapSizeX = 1728;
		float battlefieldMapSizeY = 1728;



		UINT32 siegeRamCost = 50;
		UINT32 siegeLadderCost = 15;
		UINT32 siegeTowerCost = 65;
	}cfg;
};

void readWriteValues();

void writeValues();

void findOWParam(int* arg, string s, string param);

void readStringInQuotes(string* arg,string s, string param);

void limitsFile(MemWork* mem);

template <typename param_type>
void findAnyParam(param_type* arg, string s, string param);

template <typename param_type>
void findFloatParam(param_type* arg, string s, string param);

void doDisk();
void doSteam();
void doCount(DWORD code);

void writeRet(DWORD code);