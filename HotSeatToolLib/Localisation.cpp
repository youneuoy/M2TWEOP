#include "Localisation.h"
vector<locA*> Localisation::locsMes;
vector<locA*> Localisation::locsBut;

void Localisation::readLoc()
{
	string f = structs::cfg.langP + "\\" + "buttons.youneuoyloc";

	string s;
	ifstream f2(f);
	UINT32 n = 0;
	while (f2.good())
	{
		getline(f2, s);
		if (s[0] == ';')continue;
		n++;
		locA* t = new locA();
		t->id = n;
		readStringInQuotes(&t->info, s, "button string");
		getline(f2, s);
		readStringInQuotes(&t->tooltip, s, "button tooltip");
		locsBut.push_back(t);
	}

	f2.close();
	f = structs::cfg.langP + "\\" + "messages.youneuoyloc";

	f2.open(f);
	f2.unsetf(std::ios_base::skipws);
	while (f2.good())
	{
		getline(f2, s);
		if (s[0] == ';')continue;
		n++;
		locA* t = new locA();
		t->id = n;
		readStringInQuotes(&t->info, s, "message string");
		locsMes.push_back(t);
	}

	f2.close();

	calcLocSize(&locsBut);
	calcLocSize(&locsMes);
}

locA* Localisation::getLocMes(UINT32 id)
{
	if (locsMes.size() < id ) {
		MessageBoxA(NULL, "try to get invalid message from id!", "Error!", NULL);
		ofstream f1("logs\\error.youneuoyerr");
		f1 << "error in getLocMes, argument out of range, try to get:" << endl;
		f1 << id << endl;
		f1 << "elements:" << endl;
		for (locA* l : locsMes)
		{
			f1 << l->id << endl;
			f1 << l->info << endl;
			f1 << l->tooltip << endl;
		}
		f1.close();
		exit(0);
	}
	return locsMes[id-1];
}

locA* Localisation::getLocBut(UINT32 id)
{
	if (locsBut.size() < id ) {
		MessageBoxA(NULL, "try to get invalid button message from id!", "Error!", NULL);
		ofstream f1("logs\\error.youneuoyerr");
		f1 << "error in getLocBut, argument out of range, try to get:" << endl;
		f1 << id << endl;
		f1 << "elements:" << endl;
		for (locA* l : locsBut)
		{
			f1 << l->id << endl;
			f1 << l->info << endl;
			f1 << l->tooltip << endl;
		}
		f1.close();
		exit(0);
	}
	return locsBut[id-1];
}

void Localisation::calcLocSize(vector<locA*>* v)
{
	for (locA* l : *v)
	{
		l->size = ImGui::CalcTextSize(l->info.c_str());
		l->size.x += l->size.x/l->info.size()*4;
		l->size.y += 20;
	}
}
