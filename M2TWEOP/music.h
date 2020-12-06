#pragma once
#include <string>
#include <vector>
#include <windows.h>



#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
using namespace std;
class music
{
public:
	static void play(int vol);
	static void setVolume(int vol);
};

