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

void readLabelsFile();

int checkAndChangeCharLabel(general* gen);

void checkAndChangeLabels();

void checkLabForDelete(string* command, general* character);