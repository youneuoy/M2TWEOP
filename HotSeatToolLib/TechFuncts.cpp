#include"TechFuncts.h"

bool TechFuncts::inside(const int& px, const int& py, const int& ax, const int& ay, const int& dx, const int& dy)
{
    if ((px <= dx) && (px >= ax) && (py >= dy) && (py <= ay)) {
        return true;
    }
    return false;
}

void TechFuncts::allLog(char* str)
{
}

void TechFuncts::correctSize(UINT32* x, float coef)
{
    *x = *x * coef;
}

float TechFuncts::calcCoef(UINT32 xRes, UINT32 yRes)
{
    float x = 1920;
    float y = 1080;

    float coef = xRes / x;
    float coef2 = yRes / y;
    if (coef < coef2)return coef;
    return coef2;
}

string TechFuncts::getSettlLevel(int lev)
{
    string s;
    if (lev == 0)
        s= "village";
    else if (lev == 1)
    {
        s = "town";
    }
    else if (lev == 2)
    {
        s = "large_town";
    }
    else if (lev == 3)
    {
        s = "city";
    }
    else if (lev == 4)
    {
        s = "large_city";
    }
    else if (lev == 5)
    {
        s = "huge_city";
    }
    else
    {
        MessageBoxA(NULL, "Not correct town level :-(", "Not good, see descr_battle.txt", NULL);
        s = "error :-)";
    }
    return s;
}

int __stdcall TechFuncts::findModel(vector<structs::modelStratStat*>* vec, string* s)
{
    for (structs::modelStratStat* mod : *vec)
    {
        if (mod->patch == *s)
        {
            return mod->index;
        }
    }
    return -1;
}


