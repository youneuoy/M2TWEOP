#include "familyEdit.h"
generalCharacterictics* familyEdit::prs=nullptr;
bool familyEdit::persCh =false;
POINT familyEdit::p;
ImVec2 familyEdit::size;

void familyEdit::enableHeirMenu(generalCharacterictics* pers)
{
	/*prs = pers;
    persCh = true;*/
}


void familyEdit::draw(LPDIRECT3DDEVICE9 pDevice)
{
    if (!persCh)return;
    if (!prs)return;
    if (!prs->gen)return;
    if (!(prs->age & 1))return;
    if (prs->status & 5)return;
    if (prs->status & 2)return;
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 0, 0, 20));
    ImGui::SetNextWindowPos(ImVec2(p.x + 10, p.y + 10));
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize;
    ImGui::Begin("family edit window", &persCh, window_flags);
   
    locA* loc = Localisation::getLocBut(LOC_BUTTON_MAKE_HEIR);

    if (ImGui::Button(loc->info.c_str(), loc->size))
    {
        
        for (UINT32 i = 0; i < prs->faction->numOfCharacters; i++)
        {
            if (prs->faction->characters[i]->genChar->status & 2)
                prs->faction->characters[i]->genChar->status = 0;
        }
        FastFuncts::setHeir(prs);
        prs->status = 2;
        persCh = false;
        Myeffects::setCharacterEffects(prs, EFFECT_heir_accepted);

        FastFuncts::closeFamilyTree();
        FastFuncts::closeOwnSettlement();
        FastFuncts::closeOwnCharacter();
        BigMenus::showMessage(BIG_MENU_MES_HEIR);
    }
    if (ImGui::IsItemHovered())
        Myeffects::drawEffectList(EFFECT_heir_accepted, loc->tooltip.c_str());

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
}

int familyEdit::checkDrawCond()
{   

    UINT32 tree;
    Read(structs::gameDataOffsets.stratUiOffset,&tree);

    if (!tree)return 0;
    Read(tree+0xec,&tree);

    if (!tree)return 0;
    Read(tree+0x44c,&tree);

    if (!tree)return 0;
    prs = reinterpret_cast<generalCharacterictics*>(tree);

    if(!(prs->age & 1))return 0;
    if (prs->status & 5)return 0;
    if (prs->status & 2)return 0;
    if(!prs->gen)return 0;

    getCPos(&p);
    calcButtSize();

    persCh = true;

    return 1;
}

void familyEdit::checkDisableDrawCond(int checkCoords)
{
    if (!checkCoords)
    {
        persCh = false;
        return;
    }
    else if (checkCoords == 2)
    {
        if (!checkDrawCond())persCh = false; return;

    }
    POINT pp;
    getCPos(&pp);

    if (TechFuncts::inside(pp.x, pp.y, p.x + 10, p.y + 10+size.y, p.x + 10+size.x, p.y + 10))return;
    persCh = false;

}

void familyEdit::calcButtSize()
{
    size = Localisation::getLocBut(LOC_BUTTON_MAKE_HEIR)->size;



    size.x += size.x / 100 * 10;
    size.y += size.y / 100 * 10;
}
