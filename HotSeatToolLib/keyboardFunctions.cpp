#include"keyboardFunctions.h"
#include "imgui/imgui.h"
#include "FastFuncts.h"

int battleFarCamera = 0;

bool highlightOn = false;

DWORD timez = 0;

struct camCoords {
    float x;
    float y;
    float z;
} battleCamcoords;

struct camFarCoords {
    float x=0;
    float y=0;
    float z=500;
} battleFarCamcoords;

unsigned char highLightOn = 0x8f;
unsigned char highLightOff = 0x8e;

void KeyboardHook()
{
    timez = GetTickCount();
    while (1)
    {
        if (GetAsyncKeyState('Z') && (GetAsyncKeyState(VK_CONTROL)))
        {
            if (GetTickCount() > (timez + 300))
            {
                changeCameraDistanceMode();
                timez = GetTickCount();
            }
        }
        else if(GetAsyncKeyState('Q') && (GetAsyncKeyState(VK_CONTROL)))
        {
            if (GetTickCount() > (timez + 300))
            {
                changeHighlightUnits();
                timez = GetTickCount();
            }
        }
        Sleep(100);
    }
}

void changeCameraDistanceMode()
{
    UINT32 battleState;
    Read(structs::gameDataOffsets.battleStacksOffsetStart+0x4, &battleState); 
    if (!battleState)   return;

    battleFarCamera=!battleFarCamera;
    if (battleFarCamera)
    {
        Read(structs::gameDataOffsets.cameraOffsetsStartB, &battleCamcoords.y);
        Read(structs::gameDataOffsets.cameraOffsetsStartB+0x8, &battleCamcoords.x);
        Read(structs::gameDataOffsets.cameraOffsetsStartB+0x20, &battleCamcoords.z);

        Write(&battleFarCamcoords.y,structs::gameDataOffsets.cameraOffsetsStartB,4);
        Write(&battleFarCamcoords.x,structs::gameDataOffsets.cameraOffsetsStartB + 0x8,4);
        Write(&battleFarCamcoords.z,structs::gameDataOffsets.cameraOffsetsStartB + 0x20,4);
    }
    else {
        Write(&battleCamcoords.y, structs::gameDataOffsets.cameraOffsetsStartB, 4);
        Write(&battleCamcoords.x, structs::gameDataOffsets.cameraOffsetsStartB + 0x8, 4);
        Write(&battleCamcoords.z, structs::gameDataOffsets.cameraOffsetsStartB + 0x20, 4);

    }
}

void changeHighlightUnits()
{
    if (!highlightOn)
    {
        Write(&highLightOn, structs::gameCodeOffsets.highlightCodeOffset+0x1, 1);
        highlightOn = true;
    }
    else 
    {
        highlightUnitsOff();
    }
}

void highlightUnitsOff()
{
    Write(&highLightOff, structs::gameCodeOffsets.highlightCodeOffset + 0x1, 1);
    highlightOn = false;
}



struct coordsMMB
{
    int x=-1;
    int y =-1;
};
coordsMMB MMBold;
coordsMMB MMBnew;


coordsMMB MMBstart;

bool ismWork = false;
void mmbWork()
{
  /*  ismWork = true;

    //center coords
    DWORD adrCoord = 0x0196a004;
    Read(adrCoord, &adrCoord);

    DWORD adrX = adrCoord + 0x11bc;
    DWORD adrY = adrCoord + 0x11c0;



    Read(adrX, &MMBstart.x);
    Read(adrY, &MMBstart.y);



    //mouse coourds
    adrX = 0x2C3DA48;
    adrY = 0x2C3DA48 + 0x4;

    Read(adrX, &MMBold.x);
    Read(adrX, &MMBnew.x);
    Read(adrY, &MMBold.y);
    Read(adrY, &MMBnew.y);*/
}

void mmbUnWork()
{
   /* ismWork = false;*/
}


int num = 0;
void mmbMove()
{
   /* ImGui::Begin("coordinates");

    ImGui::Text("Start = %d, %d", MMBstart.x, MMBstart.y);
    ImGui::Text("New = %d, %d", MMBnew.x, MMBnew.y);
    ImGui::Text("Old = %d, %d", MMBold.x, MMBold.y);
    ImGui::End();*/

  /*  num++;
    if (num % 2 == 0)return;
    if (ismWork == false)return;
    //center coords
    //mouse coourds
    DWORD adrX = 0x2C3DA48;
    DWORD adrY = 0x2C3DA48 + 0x4;

    Read(adrX, &MMBnew.x);
    Read(adrY, &MMBnew.y);

    if (MMBold.x == MMBnew.x
        && MMBold.y == MMBnew.y
        )
    {
        return;
    }
        


    int dX= MMBnew.x - MMBold.x;

    int dY= MMBnew.y - MMBold.y;
    if (dX > 1)dX = 1;
    if (dX < -1)dX = -1;
    if (dY > 1)dY = 1;
    if (dY < -1)dY = -1;

    MMBnew.x= MMBstart.x+ dX;
    MMBnew.y= MMBstart.y+ dY;



    DWORD adr = 0x0098e030;


    _asm
    {
        push MMBnew.y
        push MMBnew.x
        mov eax, [adr]
        call eax
        add esp, 8
    }

    Read(adrX, &MMBold.x);
    Read(adrX, &MMBnew.x);
    Read(adrY, &MMBold.y);
    Read(adrY, &MMBnew.y);


    DWORD adrCoord = 0x0196a004;
    Read(adrCoord, &adrCoord);

    adrX = adrCoord + 0x11bc;
    adrY = adrCoord + 0x11c0;



    Read(adrX, &MMBstart.x);
    Read(adrY, &MMBstart.y);*/
}
