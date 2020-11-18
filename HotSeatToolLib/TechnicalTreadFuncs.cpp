#include "TechnicalTreadFuncs.h"



void TechnicalTreadFuncs::releaseTexture(LPDIRECT3DTEXTURE9 image)
{
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)release, image, 0, nullptr);
}

void TechnicalTreadFuncs::release(LPDIRECT3DTEXTURE9 image)
{
	image->Release();
}
