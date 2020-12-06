#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <psapi.h>

using namespace std;
class Params
{
public:
	static void readStringInQuotes(string* arg, string s, string param);
	
	static void findOWParam(char* arg, string s, string param);

	static string getParrentDir(string patch);

	static string getFileName(string file);

	static void findAnyParam(bool* arg, string s, string param);
private:
	static void replaceAll(string& s, const string& search, const string& replace);
};

