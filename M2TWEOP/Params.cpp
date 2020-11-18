#include "Params.h"

void Params::readStringInQuotes(string* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0] != ';')
	{
		size_t pos = s.find_first_of("\"");
		size_t endpos = s.find_last_of("\"");
		if (pos == string::npos || endpos == string::npos || pos == endpos) return;
		pos++;
		*arg = s.substr(pos, endpos - pos);
	}
	string f = "\\n";
	string r = "\n";
	replaceAll(*arg, f, r);
}

void Params::findOWParam(char* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0] != ';')
	{
		int pos = s.find_first_of("0123456789");
		if (pos == string::npos)return;
		int endpos = s.find_first_not_of("0123456789", pos + 1);
		if (endpos == string::npos)endpos = s.length();
		string result = s.substr(pos, endpos - pos);

		strcpy(arg, result.c_str());
	}
}

string Params::getParrentDir(string patch)
{
	string str = patch;
	str = str.substr(0, str.find_last_of("/\\"));
	return str;
}

string Params::getFileName(string file)
{
	string str = file;
	size_t pos = str.find_last_of("/\\")+1;
	str = str.substr(pos, str.length()- pos);
	return str;
}

void Params::replaceAll(string& s, const string& search, const string& replace)
{
	for (size_t pos = 0; ; pos += replace.length()) {

		pos = s.find(search, pos);
		if (pos == string::npos) break;

		s.erase(pos, search.length());
		s.insert(pos, replace);
	}
}

void Params::findAnyParam(bool* arg, string s, string param)
{
	if (s.find(param) != string::npos && s[0] != ';')
	{
		float t;
		int pos = s.find_first_of("0123456789");
		int endpos = s.find_first_not_of("0123456789", pos + 1);
		string result = s.substr(pos, endpos - pos);
		*arg = stoi(result);
	}
}