#include "customTiles.h"
customTiles::dataCustomS customTiles::customTilesData;
void __fastcall customTiles::onTileCheck(int* coords)
{
	if (coords == nullptr)
	{
		MessageBoxA(NULL, "Error in onTileCheck", "Attention", NULL);
		return;
	}
	int x = coords[0];
	int y = coords[1];

	for (custom_tile* ct : customTilesData.eopCustomTiles)
	{
		if (ct->x == x
			&&
			ct->y == y
			)
		{
			DWORD ctOffset = 0;
			if (structs::cfg.gamever == 2)//steam
			{
				ctOffset = 0x02BF2E98;
			}
			else
			{
				ctOffset = 0x02C3BF50;
			}
			custom_tile* ctRes = (custom_tile*)ctOffset;

			ctRes->name = ct->name;
			ctRes->nameCrypt = ct->nameCrypt;
			ctRes->pathToModel_UNICODE = ct->pathToModel_UNICODE;
			ctRes->timeCode = ct->timeCode;
			ctRes->weather = ct->weather;
			ctRes->weatherCrypt = ct->weatherCrypt;
			ctRes->x = ct->x;
			ctRes->y = ct->y;
			coords[0] = ct->x;
			coords[1] = ct->y;

			return;
		}
	}
}



void replaceAll2(string& s, const string& search, const string& replace) {
	for (size_t pos = 0; ; pos += replace.length()) 
	{
		pos = s.find(search, pos);
		if (pos == string::npos) break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

string getModString(string path)
{
	string ret;
	size_t pos = path.find("/mods/", 0);
	for (int i = 0; i < path.size(); i++)
	{
		if (i > pos)
		{
			ret.push_back(path[i]);
		}
	}
	return ret;
}

int getTimeCode(string time)
{
	if (time.find("afternoon") != string::npos)
	{
		return 3;
	}
	else if (time.find("midday") != string::npos)
	{
		return 2;
	}
	else if (time.find("morning") != string::npos)
	{
		return 1;
	}
	else if (time.find("night") != string::npos)
	{
		return 5;
	}
	else if (time.find("sunrise") != string::npos)
	{
		return 0;
	}
	else if (time.find("sunset") != string::npos)
	{
		return 4;
	}
	return 6;
}

void __stdcall customTiles::readTilesFile()
{
	customTilesData.eopCustomTiles.clear();

	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\custom_tiles.yoneuoycfg";

	ifstream f2(f);

	//for read events data
	string name, x, y, mapName, weather, time;
	while (f2.good())
	{
		getline(f2, f);
		if (f == "" || f == ";")continue;

		name = f;
		getline(f2, x);
		getline(f2, y);
		getline(f2, mapName);
		getline(f2, weather);
		getline(f2, time);

		custom_tile* newTile = new custom_tile();

		char* nameTemp = new char[name.length() + 1];
		memcpy(nameTemp, name.c_str(), name.length() + 1);

		UINT32 nameOffset = (UINT32)&newTile->name;
		UINT32 functionOffset = structs::gameCodeOffsets.setStringAndCryptOffset;
		_asm {
			push nameTemp
			mov ecx, nameOffset
			mov eax, functionOffset
			call eax
		}

		newTile->x = stoi(x);
		newTile->y = stoi(y);

		char* weatherTemp = new char[weather.length() + 1];
		memcpy(weatherTemp, weather.c_str(), weather.length() + 1);
		UINT32 weatherOffset = (UINT32)&newTile->weather;
		_asm {
			push weatherTemp
			mov ecx, weatherOffset
			mov eax, functionOffset
			call eax
		}

		newTile->timeCode = getTimeCode(time);


		string pathName = structs::cfg.modPatch;
		string f = "\\";
		string r = "/";
		replaceAll2(pathName, f, r);
		pathName = getModString(pathName);


		pathName = pathName + "/data/world/maps/campaign/imperial_campaign/custom_tiles/";

		pathName = pathName + mapName;

		char* pathTemp = new char[pathName.length() + 1];
		memcpy(pathTemp, pathName.c_str(), pathName.length() + 1);

		DWORD funcAdr = 0;
		if (structs::cfg.gamever == 2)//steam
		{
			funcAdr = 0x00f01eb0;
		}
		else
		{
			funcAdr = 0x00f018e0;
		}

		newTile->pathToModel_UNICODE = (char**)new char[(pathName.length() + 1) * 2];
		char** tileTest = (char**)newTile->pathToModel_UNICODE;
		_asm {
			mov ecx, tileTest
			push pathTemp
			mov eax, funcAdr
			call eax
		}
		newTile->pathToModel_UNICODE = (char**)*tileTest;
		customTilesData.eopCustomTiles.push_back(newTile);
	}
}
