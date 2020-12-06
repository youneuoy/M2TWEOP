#pragma once
#include <windows.h>
#include <string>
#include <fstream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_internal.h"
#include <d3d9.h>
#include "Startup.h"
#include "injector.h"
#include "music.h"
using namespace std;
class Drawer
{
public:
	static bool drawMain;
	static bool drawFAQ;
	static bool drawCredits;
	static void mainMenu(LPDIRECT3DDEVICE9 pDevice);

	static void FAQ(LPDIRECT3DDEVICE9 pDevice);
	static void credits(LPDIRECT3DDEVICE9 pDevice);
};

