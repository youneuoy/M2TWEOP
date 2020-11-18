#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include"configFiles.h"
#include "realGameTypes.h"
#include "FastFuncts.h" 



void startEduWork();

void writeFieldOfEdu(DWORD adr, DWORD offset);

void writeUnitDBVtableAdress(DWORD adr);

void writeUnitDBUnitAdress(DWORD adr);

void replaceAdresses();

void fullFillEdu(DWORD adr, UINT32 size);

void fullFillEduEntry(DWORD adr);


//#1
//idk what is done here
void toFunc004101e0();

//#2
//idk what is done here
void toFunc00411e0c();

//#3
//idk what is done here
void toFunc0043c640();

//#4
//idk what is done here
void toFunc0043e390();

//#5
//idk what is done here
void toFunc004758f0();

//#6
//idk what is done here
void toFunc00477c50();

//#7
//one of script commands
void toFunc0047a140();

//#8
//something very important
void toFunc004d2600();

//#9
//idk what is done here
void toFunc004f11d0();

//#10
//idk what is done here
void toFunc004f27f0();

//#11
//idk what is done here
void toFunc004fab70();

//#12
//idk what is done here
void toFunc0050af60();

//#13
//idk what is done here
void toFunc0052f460();

//#14
//idk what is done here
void toFunc0052f640();

//#15
//idk what is done here
void toFunc005906a0();

//#16
//idk what is done here
void toFunc00590710();

//#17
//idk what is done here
void toFunc00590b90();

//#18
//idk what is done here
void toFunc005994d0();

//#19
//idk what is done here
void toFunc005d8230();

//#20
//idk what is done here
void toFunc005ee630();

//#21
//idk what is done here
void toFunc005f59a0();

//#22
//idk what is done here
void toFunc005f5a50();

//#23
//idk what is done here
void toFunc005f5af0();

//#24
//return of adress of element  #param
void toFunc005f6320();

//#25
//idk what is done here
void toFunc005f6360();

//#26
//return of adress of field of element  #param
void toFunc005f7890();

//#27
//idk what is done here
void toFunc0060bbd0();

//#28
//script command
void toFunc0060ca20();

//#29
//idk what is done here
void toFunc0060d2e0();

//#30
//idk what is done here
void toFunc0060e800();

//#31
//idk what is done here
void toFunc00632810();

//#32
//read? compare stirngs with some unit params from file?
void toFunc006343d0();

//#33
//CONSTRUCTOR OF SOMETHING?
void toFunc00635ea0();

//34
//looks important, many calls from here
void toFunc007156f0();

//#35
//many methods calls
void toFunc007185a0();

//#36
//idk what is done here
void toFunc00719ee0();

//#37
//idk what is done here
void toFunc0071a3e0();

//#38
//destructor of something?
void toFunc0071a770();

//#39
//something about units
void toFunc0071b520();

//#40
//something about units
void toFunc00749fd0();

//#41
//I_UnitExists script command
void toFunc0086cde0();

//#42
//somthing about unit types, agent types, etc
void toFunc008a9a60();

//#43
//something about buildings, etc
void toFunc008ba9d0();

//#44
//something about files, or strings compare, etc
void toFunc008e2330();

//#45
//something about sounds, etc
void toFunc00a3ea50();

//#46
//something about sounds, etc
void toFunc00a3ee30();

//#47
//something about voices, accents etc
void toFunc00a40c10();

//#48
//something about scripts
void toFunc00a84c60();


//#49
//something about scripts
void toFunc00a85160();

//#50
//something about scripts
void toFunc00a87000();

//#51
//something about scripts
void toFunc00a8cb40();

//#52
//something about scripts
void toFunc00a8d770();

//#53
//idk what is this
void toFunc00ab91a0();

//#54
//idk what is this
void toFunc00ad87d0();

//#55
//idk what is this
void toFunc00adfbd0();

//#56
//idk what is this
void toFunc00ae2bc0();

//#57
//idk what is this
void toFunc00b90e00();

//#58
//idk what is this
void toFunc00b91150();

//#59
//idk what is this
void toFunc00b94e50();

//#60
//idk what is this
void toFunc00ba1eb0();

//#61
//something with stringtoscreen
void toFunc00ba26b0();

//#62
//idk what is this
void toFunc00ba2ae0();

//#63
//idk what is this
void toFunc00bac9c0();

//#64
//idk what is this
void toFunc00c57720();

//#65
//idk what is this
void toFunc00c7d680();

//#66
//compare strings attributes/skills/traits/army/etc
void toFunc00ca30a0();

//#67
//idk what is this
void toFunc00cbb680();

//#68
//idk what is this
void toFunc00cf4020();

//#69
//@@@@stringToScreen("\tCreating army controlled by %S at 0x%x from script\n");
void toFunc00cf4fe0();

//#70
//idk what is this
void toFunc00d0d3e0();


//#71
//FROM HERE calling @@@@@@@@@@@@@@@generalModelsinbattle?(*(undefined4 *)(local_5c + 0xc),0x1f);
void toFunc00d0e140();

//#72
//idk what is this
void toFunc00d13310();

//#73
//MANY CALLS FROM IT
void toFunc00d19050();

//#74
//MANY CALLS FROM IT
void toFunc00d196e0();

//#75
//MANY CALLS FROM IT, FUN_00d32a60("Buffer manager failed to open.");
void toFunc00d19fa0();

//#76
////idk what is this, it writes or reading or soething else about units? pcVar6 = "  * unit(%s), initial_size(%f), replen_rate(%f), max_size(%f), exp(%d)\n";
void toFunc00d2da70();

//¹77
//idk what is this, FUN_00d27790(param_2,"\nRecruitment Pool\n================\n");,etc
void toFunc00d2dc20();

//#78
//add units to somethere
void toFunc00d2f3a0();

//#79
//add units to somethere, FUN_00d47420("cheat oliphants");
void toFunc00d2f890();

//#80
//add units to somethere,FUN_00d47420("Mercenary Rocket Launcher");
void toFunc00d2fc10();

//#81
//add units to somethere,FUN_00d47420("Elephant Rocketeer");
void toFunc00d2ffd0();

//#82
//add units to somethere,FUN_00d47420("Elephant Artillery Mercs");
void toFunc00d30390();

//#83
//add units to somethere,FUN_00d47420("Elephants Mercs");
void toFunc00d30750();

//#84
//add units to somethere,FUN_00d47420("Mercenary Monster Bombard");
void toFunc00d30b10();

//#85
//add units to somethere,FUN_00d47420("Mercenary Monster Ribault");
void toFunc00d30ed0();

//#86
//idk what is this
void toFunc00e78890();

//#87
//idk what is this
void toFunc012ca3d0();

//#88
//idk what is this
void toFun012e0250();



