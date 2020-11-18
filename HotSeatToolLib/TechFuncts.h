#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "configFiles.h"
using namespace std;
//Here are the technical functions what not interacted with game data.
class TechFuncts
{
public:
	//check coordinates
	static bool inside(const int& px, const int& py, const int& ax, const int& ay, const int& dx, const int& dy);
	static void allLog(char* str);

	static void correctSize(UINT32* x, float coef);

	static float calcCoef(UINT32 xRes, UINT32 yRes);

	static string getSettlLevel(int lev);

	static int WINAPI findModel(vector<structs::modelStratStat*>* vec,string* s);
};