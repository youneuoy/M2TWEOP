#include "colors.h"
colors::colorSettings colors::menuColors;
colors::uiSettings colors::uiSett;

void colors::readColors()
{
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\UI\\colors.youneuoyui";
	int textR;
	int textG;
	int textB;
	int textA;


	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		findOWParam(&textR, f, "Text_red");
		findOWParam(&textG, f, "Text_green");
		findOWParam(&textB, f, "Text_blue");
		findOWParam(&textA, f, "Text_alpha");
	}
	f2.close();


	menuColors.text = ImColor(textR, textG, textB, textA);
}

void colors::readUI()
{
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\UI\\ui.youneuoyui";

	ifstream f2(f);
	while (f2.good())
	{
		getline(f2, f);
		findOWParam(&uiSett.textSize, f, "textSize");
	}
	f2.close();
}
