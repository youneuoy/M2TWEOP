#pragma once

#include "graphicsD3D.h"

class TechnicalTreadFuncs
{
public:
	static void releaseTexture(LPDIRECT3DTEXTURE9 image);
private:
	static void release(LPDIRECT3DTEXTURE9 image);
};

