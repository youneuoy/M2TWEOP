#pragma once
#include <windows.h>
bool Hook(char* src, char* dst, int len);

char* TrampHook(char* src, char* dst, unsigned int len);