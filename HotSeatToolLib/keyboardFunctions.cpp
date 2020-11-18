#include"keyboardFunctions.h"
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
