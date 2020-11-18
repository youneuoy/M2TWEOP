#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
using namespace std;
class fsystem
{
public:
	//get all subfolders
	static vector<string> getAllSubFolders(string s);

	//check name of mod folder, if it contains not .
	static int checkDots(string s);

	static vector<string> getAllFiles(string s);

	static string get_ext(const string& st);


	static void loadTexture(string* path, LPDIRECT3DTEXTURE9* image, LPDIRECT3DDEVICE9 g_pd3dDevice);
};

