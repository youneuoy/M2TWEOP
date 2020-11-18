#include "smallPatches.h"

void applySmallPaches()
{
	applyControlFaction();
	applyConsoleComands();
}

void applyControlFaction()
{
	if (!structs::cfg.unlockChangeFaction) return;

	//nopping the jump instruction
	unsigned char nops[6] = {0x90,0x90,0x90,0x90,0x90,0x90};
	Write(nops, structs::gameCodeOffsets.consoleChangeFactionOffset, 6);

}

void applyConsoleComands()
{
	if (!structs::cfg.unlockConsoleCommands)return;
	FastFuncts::unlockConsoleCommands();
	FastFuncts::writeConsoleCommandsFile();
}
