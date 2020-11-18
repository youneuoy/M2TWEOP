#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <d3d9.h>
#include "fsystem.h"
#include "Params.h"
using namespace std;
class mod 
{
public:
	//current cfg
	int cfgFile=0;
	//list of cfgs
	vector<string>cfgFiles;
	//name of folder
	string path;
	//display name
	string name="";
	//description
	string descr="mod not have description";
	//internet link
	string link="https://discord.gg/xpPrysj";
	//if have EOP files
	int EOP=0;
	//image
	struct im {
		LPDIRECT3DTEXTURE9 texture;
		string name="";
	}image;


	//set data
	mod* initMod(string modpath, LPDIRECT3DDEVICE9 g_pd3dDevice);

	//check mod folder for mod data
	static int ifMod(string path);

private:
	//set cfg files
	mod* setCfgs();
	//set EOP
	mod* setEOP();

	//set name, image, descr
	mod* setDisplayData(LPDIRECT3DDEVICE9 g_pd3dDevice);

	//if not EOP
	mod* setNotEOPDData(LPDIRECT3DDEVICE9 g_pd3dDevice);



};

