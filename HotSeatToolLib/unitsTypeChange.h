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

void readUnitsTypeFile();

void readUnitsTypesFunc();



int checkAndChangeUnitType(unit* un);
void checkAndChangeUnitsTypeFunc();