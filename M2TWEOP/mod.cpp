#include "mod.h"

mod* mod::initMod(string modpath, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	path = modpath;
	setCfgs()->setEOP()->setDisplayData(g_pd3dDevice);
	return this;
}

int mod::ifMod(string path)
{

	/*vector<string> dlcs = {
		"americas",
		"british_isles",
		"crusades",
		"teutonic"
	};

	for (string s : dlcs)
	{
		if (path.find(s) != string::npos)
		{
			return 0;
		}
	}*/


	vector<string> names= fsystem::getAllSubFolders(path);
	
	vector<string> modId = 
	{
		"data",
	};

	int finded = 0;
	for (string search : modId)
	{
		for (string s : names)
		{
			if(s== search)
			{
				finded++;
				break;
			}

		}
	}
	if(finded< modId.size())
	{
		return 0;
	}

	names = fsystem::getAllFiles(path);

	modId =
	{
		"cfg",
	};

	finded = 0;
	for (string search : modId)
	{
		for (string s : names)
		{
			s = fsystem::get_ext(s);
			if (s == search)
			{
				finded++;
				break;
			}

		}
	}
	if (finded < modId.size())
	{
		return 0;
	}

	return 1;
}

mod* mod::setCfgs()
{
	vector<string> names = fsystem::getAllFiles(path);

	string modId ="cfg";


	for (string s : names)
	{
		string ext = fsystem::get_ext(s);
		if (ext != modId)
		{
			continue;
		}
		cfgFiles.push_back(s);
	}
	return this;
}

mod* mod::setEOP()
{
	vector<string> names = fsystem::getAllSubFolders(path);

	vector<string> modId =
	{
		"youneuoy_Data",
	};

	int finded = 0;
	for (string search : modId)
	{
		for (string s : names)
		{
			if (s == search)
			{
				finded++;
				break;
			}

		}
	}
	if (finded < modId.size())
	{
		return this;
	}

	EOP = 1;
	return this;
}

mod* mod::setDisplayData(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	if (!EOP) { setNotEOPDData(g_pd3dDevice); return this; }
	string infoPach = path + "\\youneuoy_Data";
	vector<string> names = fsystem::getAllSubFolders(infoPach);

	vector<string> modId =
	{
		"modInfo",
	};

	int finded = 0;
	for (string search : modId)
	{
		for (string s : names)
		{
			if (s == search)
			{
				finded++;
				break;
			}

		}
	}
	if (finded < modId.size())
	{
		setNotEOPDData(g_pd3dDevice);
		return this;
	}
	
	infoPach = infoPach + "\\modInfo";
	string infoFile = infoPach + "\\modInfo.txt";

	string s;
	ifstream f1;
	f1.open(infoFile);

	string texture = "";
	while (f1.good())
	{
		getline(f1, s);

		Params::readStringInQuotes(&texture, s, "image");

		Params::readStringInQuotes(&name, s, "mod_name");

		Params::readStringInQuotes(&descr, s, "description");

		Params::readStringInQuotes(&link, s, "link");
	}
	image.name = infoPach + "\\" + texture;
	if (name == "")
		name = path;

	fsystem::loadTexture(&image.name,&image.texture, g_pd3dDevice);

	return this;
}

mod* mod::setNotEOPDData(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	name = path;

	return this;
}
