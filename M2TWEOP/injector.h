#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <sstream>
#include <fstream>
#include <shlwapi.h>
#include <iostream>
#include <thread>

#include "Startup.h"
using namespace std;
class injector
{
public:
	static void start();
private:
	static void threadF();
};

int test();