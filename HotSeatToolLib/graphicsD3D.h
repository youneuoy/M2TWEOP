#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <string>
#include "configFiles.h"
#include <fstream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui_internal.h"
#include "familyEdit.h"
#include <system_error>
#include "colors.h"
#include "battlesResults.h"
using namespace std;



void getCPos(POINT *p);

void loadTexture(string* path, LPDIRECT3DTEXTURE9* image);

DWORD WINAPI InitS();