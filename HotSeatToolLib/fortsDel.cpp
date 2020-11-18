#include"fortsDel.h"

void readFortsFile()
{
	ofstream f1("logs\\fortsUnDel.youneuoylog");
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\fortsUnDel.yoneuoycfg";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		UINT32 t = findParam(f);
		if (t != 500) { continue; }
		else
		{
			structs::fortCond* frt = new structs::fortCond();

			getline(f2, f);
			frt->x = stoi(f);

			getline(f2, f);
			frt->y = stoi(f);

			structs::lForts.push_back(frt);
		}
	}
	f2.close();

	f1 << "Log, readed params:" << endl;

	for (structs::fortCond* frt : structs::lForts)
	{
		f1 << "fort coords:" << endl;
		f1 <<"x= "<<frt->x<<", y="<<frt->y<< endl;
	}
	f1 << "end" << endl;
	f1.close();
}

int __stdcall checkFort()
{
	fortStruct* frtIn;
	_asm {
		mov frtIn,edi
	}
	if (frtIn->army)return 1;

	for (structs::fortCond* frt : structs::lForts)
	{
		if (frtIn->xCoord == frt->x
			&&
			frtIn->yCoord == frt->y
			)
		{
			return 1;
		}
	}

	return 0;
}
