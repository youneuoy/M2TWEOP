#pragma once
#include <string>
#include <vector>
#include <windows.h>



#pragma comment(lib, "Winmm.lib")
using namespace std;
class music
{
public:
	static void play(int vol);
	static void setVolume(int vol);
};

