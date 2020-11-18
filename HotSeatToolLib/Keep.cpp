#include "Keep.h"
vector<Keep::typeI*> Keep::typesI;

void Keep::readInfo()
{

	string f = structs::cfg.langP + "\\" + "effectsInfo.youneuoyloc";

	string s;
	ifstream f2(f);
	UINT32 n = 0;
	while (f2.good())
	{
		getline(f2, s);
		if (s[0] == ';')continue;
		n++;
		typeI* t = new typeI();
		t->typeId = n;
		readStringInQuotes(&t->info, s, "effect string");
		typesI.push_back(t);
	}

	f2.close();
}

string* Keep::getEffectLoc(UINT32 id)
{
	if (typesI.size() < id) {
		MessageBoxA(NULL, "try to get invalid effect localisation from id!", "Error!", NULL);
		ofstream f1("logs\\error.youneuoyerr");
		f1 << "error in getEffectLoc(UINT32 id), argument out of range, try to get:" << endl;
		f1 << id << endl;
		f1 << "elements:" << endl;
		for (Keep::typeI*ti : typesI)
		{
			f1 << ti->typeId << endl;
			f1 << ti->info << endl;
		}
		f1.close();
		exit(0);
	}
	return &typesI[id - 1]->info;
}
