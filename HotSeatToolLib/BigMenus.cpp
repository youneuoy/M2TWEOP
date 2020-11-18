#include "BigMenus.h"
vector<BigMenus::menuStruct*> BigMenus::messages;
BigMenus::screenInfo BigMenus::screenParams;
BigMenus::menuDrawStruct BigMenus::drawParams;
bool BigMenus::isDrawNedeed = false;
void BigMenus::readMessageFiles()
{
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\textures\\big_menu_scroll.dds";
	loadTexture(&f, &drawParams.bigScroll);

	screenParams.resCoef=TechFuncts::calcCoef(screenParams.rect.right, screenParams.rect.bottom);



	menuStruct* test = new menuStruct ();
	messages.push_back(test);
	messages[0]->message = Localisation::getLocMes(LOC_BIG_MESS_HEIR_ACCEPTED);
	f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\textures\\heir_accepted_message.dds";

	loadTexture(&f, &messages[0]->image);
	D3DSURFACE_DESC desc;
	messages[0]->image->GetLevelDesc(0, &desc);
	messages[0]->weight = desc.Width * screenParams.resCoef;
	messages[0]->height = desc.Height * screenParams.resCoef;



	calcWindowPos();
}

void BigMenus::calcWindowPos()
{
	UINT32 xproc = screenParams.rect.right / 100 * 20;
	drawParams.x = screenParams.rect.right / 2- xproc;

	drawParams.weight = xproc * 2;

	UINT32 yproc= screenParams.rect.bottom / 100 * 10;
	drawParams.y= 0 + yproc;
	drawParams.height = yproc * 8;


	drawParams.xImg = 150;
	drawParams.yImg = 120;

	locA* loc = Localisation::getLocBut(LOC_BUTTON_CANCEL);
	drawParams.weightCloseBut =loc->size.x;
	drawParams.heightCloseBut = loc->size.y;

	drawParams.xCloseBut = drawParams.weight / 2- drawParams.weightCloseBut/2;
	drawParams.yCloseBut = drawParams.height- yproc- drawParams.heightCloseBut;

	drawParams.xText = drawParams.weight/ 100 * 20;
	drawParams.yText = drawParams.height/ 100 * 40;
	drawParams.weightText = drawParams.weight- drawParams.xText;
	drawParams.heightText = drawParams.height/ 100 * 40;

	ofstream f1("logs\\bigmenu.youneuoylog");
	f1<<"drawParams.x:"<< drawParams.x <<endl;
	f1 << "drawParams.y:" << drawParams.y <<endl;
	f1 << "drawParams.weight:" << drawParams.weight <<endl;
	f1 << "drawParams.height:" << drawParams.height <<endl;
	f1 << "drawParams.xImg:" << drawParams.xImg <<endl;
	f1 << "drawParams.yImg:" << drawParams.yImg <<endl;
	f1 << "drawParams.xCloseBut:" << drawParams.xCloseBut <<endl;
	f1 << "drawParams.yCloseBut:" << drawParams.yCloseBut <<endl;
	f1 << "drawParams.weightCloseBut:" << drawParams.weightCloseBut <<endl;
	f1 << "drawParams.heightCloseBut:" << drawParams.heightCloseBut <<endl;
	f1 << "drawParams.xText:" << drawParams.xText <<endl;
	f1 << "drawParams.yText:" << drawParams.yText <<endl;
	f1.close();
}

void BigMenus::showMessage(int id)
{
	if (id > messages.size()) {
		MessageBoxA(NULL, "try to set invalid draw message!", "Error!", NULL);
		exit(0);
	}
	drawParams.drawCode = id - 1;


	isDrawNedeed = true;
}

void BigMenus::Draw(LPDIRECT3DDEVICE9 pDevice)
{
	if (isDrawNedeed ==false) return;
	ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 0, 0, 20));
	ImGui::SetNextWindowPos(ImVec2(drawParams.x, drawParams.y));
	ImGui::SetNextWindowSize(ImVec2(drawParams.weight, drawParams.height));
	ImGui::SetNextWindowBgAlpha(0.f);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize;
    ImGui::Begin("Big menu window", &isDrawNedeed, window_flags);

	ImGui::Image(drawParams.bigScroll, ImVec2(drawParams.weight, drawParams.height));
	ImGui::SetCursorPos((ImVec2(drawParams.xImg, drawParams.yImg)));
	ImGui::Image(messages[drawParams.drawCode]->image, ImVec2(messages[drawParams.drawCode]->weight, messages[drawParams.drawCode]->height));

	ImGui::SetCursorPos((ImVec2(drawParams.xText, drawParams.yText)));
	ImGui::PushTextWrapPos(drawParams.weightText);
	ImGui::TextWrapped(messages[drawParams.drawCode]->message->info.c_str());
	ImGui::PopTextWrapPos();

	ImGui::SetCursorPos((ImVec2(drawParams.xCloseBut, drawParams.yCloseBut)));
	
	locA* loc = Localisation::getLocBut(LOC_BUTTON_CANCEL);
    if (ImGui::Button(loc->info.c_str(), ImVec2(drawParams.weightCloseBut, drawParams.heightCloseBut)))
    {
		stopShowMessage();
    }
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(loc->tooltip.c_str());

    ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void BigMenus::stopShowMessage()
{
	isDrawNedeed = false;
}
