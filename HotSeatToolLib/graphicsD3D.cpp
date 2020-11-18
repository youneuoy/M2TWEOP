#include "graphicsD3D.h"
#include "BigMenus.h"
bool Open = false;

static bool ImInitialized = false;
void* d3d9Device[119];
WNDPROC oWndProc = nullptr;
HRESULT(APIENTRY* oEndScene)(LPDIRECT3DDEVICE9);
HWND Window = nullptr;
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT APIENTRY EndScene(LPDIRECT3DDEVICE9 pDevice);
LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

D3DCOLOR fontColor = 0;
ID3DXFont* m_font = 0;
RECT fontRect = { 20, 20, 555, 555 };


LPDIRECT3DDEVICE9 actualDevice= nullptr;


DWORD menuStopTime = 0;
bool init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    menuStopTime = GetTickCount()+ 7000;
    while (Window == nullptr)
    {
        Window = FindWindowA(0, ("Medieval 2"));
        if (Window) break;
        Sleep(20);
    }

    oWndProc = (WNDPROC)SetWindowLongA(Window, GWL_WNDPROC, (LONG)hkWndProc);
    if (oWndProc == nullptr) return false;
    return true;
}

bool show_another_window = false;
void Draw(LPDIRECT3DDEVICE9 pDevice)
{

    if (structs::cfg.characterUIMenus == 1)
    {
        familyEdit::draw(pDevice);
    }
    BigMenus::Draw(pDevice);
    tipsEs::draw(pDevice);
    bResults::draw(pDevice);
    if (show_another_window)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            ScreenToClient(Window, &p);
        }
        string s = "x= ";
        s += to_string(p.x);
        s += "y= ";
        s += to_string(p.y);
        //ImGui::SetNextWindowPos(ImVec2(p.x+10,p.y+10));
        ImGui::SetNextWindowBgAlpha(-1.f);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::Begin("Cursor coordinates:", &show_another_window, window_flags);

        ImGui::Text(s.c_str());
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(1, 50, 32, 255));
        if (ImGui::Button("test button!"))
        {
            MessageBoxA(NULL, "Click!", "Info", NULL);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Fucking gates!");

        ImGui::PopStyleColor();
        ImGui::End();

    }
}


HRESULT APIENTRY EndScene(LPDIRECT3DDEVICE9 pDevice)
{
    

    D3DDEVICE_CREATION_PARAMETERS cparams;
    RECT rect;

    if (GetTickCount()< menuStopTime)
    {

        pDevice->GetCreationParameters(&cparams);
        GetWindowRect(cparams.hFocusWindow, &rect);
        UINT32 fontSize = rect.bottom / 25;
        D3DXCreateFont(pDevice, fontSize, 0, 5, 0, 0, 1, 0, 0, 0 | FF_DONTCARE, TEXT("MariageAntD"), &m_font);
        fontColor = D3DCOLOR_XRGB(255, 255, 255);
        m_font->DrawText(0, L"MTW2EOP v1.19", -1, &fontRect, DT_LEFT, fontColor);
        m_font->Release();
    }




    if (!ImInitialized)
    {
        actualDevice = pDevice;

        pDevice->GetCreationParameters(&BigMenus::screenParams.cparams);
        GetWindowRect(BigMenus::screenParams.cparams.hFocusWindow, &BigMenus::screenParams.rect);


        ImFontConfig font_config;
        font_config.OversampleH = 1;
        font_config.OversampleV = 1;
        font_config.PixelSnapH = 1;
        static const ImWchar ranges[] =
        {
            0x0020, 0x00FF, // Basic Latin + Latin Supplement
            0x0400, 0x044F, // Cyrillic
            0,
        };
        ImGuiIO& io = ImGui::GetIO();
        string f = structs::cfg.modPatch;
        f = f + "\\youneuoy_Data\\inGame.ttf";


        pDevice->GetCreationParameters(&cparams);
        GetWindowRect(cparams.hFocusWindow, &rect);

        colors::readUI();
        float fontSize = rect.bottom / colors::uiSett.textSize;
        io.Fonts->AddFontFromFileTTF(f.c_str(), fontSize, &font_config, ranges);

        ImGui_ImplWin32_Init(Window);
        ImGui_ImplDX9_Init(pDevice);

        //styles
        colors::readColors();
        ImGui::PushStyleColor(ImGuiCol_Text, colors::menuColors.text);
        ImInitialized = true;
    }


        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        Draw(pDevice);

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    return oEndScene(pDevice);
}   

LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_KEYDOWN)
    {
        if (familyEdit::persCh)
        {

            if (wParam == VK_ESCAPE)
            {
                familyEdit::checkDisableDrawCond();
            }
        }

        if (wParam == 0x56 && (GetAsyncKeyState(VK_CONTROL)))
        {
            bResults::switchDraw();
        }
    }

    switch (uMsg)
    {
         case WM_LBUTTONDOWN: 
         {
             if (wParam != MK_LBUTTON)break;
             if (familyEdit::persCh)
             {
                 familyEdit::checkDisableDrawCond(1);
                 break;
             }
             break;
         }
         case WM_RBUTTONDOWN:
         {
             if (wParam != MK_RBUTTON)break;
             if (familyEdit::persCh)
             {
                 familyEdit::checkDisableDrawCond(2);
                 break;
             } else if (!familyEdit::persCh)
             {
                 familyEdit::checkDrawCond();
                 break;
             }
         }
    }

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return 1;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


DWORD WINAPI InitS()
{
    init();
	string f = structs::cfg.modPatch;
	f = f + "\\youneuoy_Data\\mainFont.ttf";
	std::wstring stemp = std::wstring(f.begin(), f.end());
	LPCWSTR sw = stemp.c_str();

	AddFontResourceEx(sw, FR_PRIVATE, NULL);

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)EndScene, 7);

	}
	return 0;
}

void getCPos(POINT* p)
{
    if (GetCursorPos(p))
    {
        ScreenToClient(Window, p);
    }
}

void loadTexture(string* path, LPDIRECT3DTEXTURE9* image)
{
    HRESULT res = D3DXCreateTextureFromFileA(actualDevice, path->c_str(), image);
    string t = std::system_category().message(res);
    if(res!=D3D_OK)
    {
        MessageBoxA(NULL, t.c_str(), "Loading texture err!", MB_OK | MB_ICONASTERISK);
    }
}




