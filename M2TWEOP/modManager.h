#pragma once


#include <string>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <fstream>
#include <d3d9.h>
#include "mod.h"
#include "fsystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui_internal.h"
#include <shlwapi.h>

using namespace std;
class modManager
{
public:


	static struct mds 
	{
		string lastMod="";
		//selected mod
		int selected;
		//path to mods folder
		string modFolder;
		//mod list
		vector<mod*>list;


		LPDIRECT3DTEXTURE9 background;

		LPDIRECT3DTEXTURE9 stdbackground;
	}mods;
	static void findMods(LPDIRECT3DDEVICE9 g_pd3dDevice);

	static void run(LPDIRECT3DDEVICE9 g_pd3dDevice,char* path);

	static int Draw(LPDIRECT3DDEVICE9 g_pd3dDevice,bool* isdraw);

	static int updateBackgroundTexture(LPDIRECT3DDEVICE9 g_pd3dDevice);

	static void writeLastMod(char* path);
	static void loadLastMod(char* path);
};

