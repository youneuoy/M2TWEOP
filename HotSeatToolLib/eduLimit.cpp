#include"eduLimit.h"
//adress of methods before unit types start on stard of unit db
DWORD VTableAdress = 0x013351CC;

//start of units db, with Vtable
//018c2ba8 in steam version
DWORD ourUDB;
//edu entries in unit db
//018c2bac in steam version
DWORD ourEDU;

//number of types
//after edu entries
//0193c4fc in steam version
DWORD numberOfTupes;


void startEduWork()
{
	char* ed=(char*)new EduEntry[1000];
	//after allocation data, our new unit db
	ed = ed + 8;
	ourUDB = reinterpret_cast<DWORD>(ed);

	//write vtable adress
	Write(&VTableAdress,(DWORD)ed,4);
	//it is start of our new unit db edu entries
	ed = ed + 4;
	ourEDU = reinterpret_cast<DWORD>(ed);

	
	ofstream f1("logs\\11.youneuoylog");
	f1 << hex << (void*)ed << "-here ed" << endl;
	f1 << hex << ourUDB << "- UDB" << endl;
	f1 << hex << ourEDU << "- EDU" << endl;

	//In order of increasing addresses, we replace the data in RAM
	replaceAdresses();

	fullFillEdu(ourEDU,1000);


	int lim = 500;
	Write(&lim, ourEDU + 0x79954, 4);
	f1 << "done" << endl;
	f1.close();

}


void replaceAdresses()
{
	toFunc004101e0();

	toFunc00411e0c();

	toFunc0043c640();

	toFunc0043e390();

	toFunc004758f0();

	toFunc00477c50();

	toFunc0047a140();

	toFunc004d2600();

	toFunc004f11d0();

	toFunc004f27f0();

	toFunc004fab70();

	toFunc0050af60();

	toFunc0052f460();

	toFunc0052f640();

	toFunc005906a0();

	toFunc00590710();

	toFunc00590b90();

	toFunc005994d0();

	toFunc005d8230();

	toFunc005ee630();

	toFunc005f59a0();

	toFunc005f5a50();

	toFunc005f5af0();

	toFunc005f6320();

	toFunc005f6360();

	toFunc005f7890();

	toFunc0060bbd0();

	toFunc0060ca20();

	toFunc0060d2e0();

	toFunc0060e800();

	toFunc00632810();

	toFunc006343d0();

	toFunc00635ea0();

	toFunc007156f0();

	toFunc007185a0();

	toFunc00719ee0();

	toFunc0071a3e0();

	toFunc0071a770();

	toFunc0071b520();

	toFunc00749fd0();

	toFunc0086cde0();

	toFunc008a9a60();

	toFunc008ba9d0();

	toFunc008e2330();

	toFunc00a3ea50();

	toFunc00a3ee30();

	toFunc00a40c10();

	toFunc00a84c60();

	toFunc00a85160();

	toFunc00a87000();

	toFunc00a8cb40();

	toFunc00a8d770();

	toFunc00ab91a0();

	toFunc00ad87d0();

	toFunc00adfbd0();

	toFunc00ae2bc0();

	toFunc00b90e00();

	toFunc00b91150();

	toFunc00b94e50();

	toFunc00ba1eb0();

	toFunc00ba26b0();

	toFunc00ba2ae0();

	toFunc00bac9c0();

	toFunc00c57720();

	toFunc00c7d680();

	toFunc00ca30a0();

	toFunc00cbb680();

	toFunc00cf4020();

	toFunc00cf4fe0();

	toFunc00d0d3e0();

	toFunc00d0e140();

	toFunc00d13310();

	toFunc00d19050();

	toFunc00d196e0();

	toFunc00d19fa0();

	toFunc00d2da70();

	toFunc00d2dc20();

	toFunc00d2f3a0();

	toFunc00d2f890();

	toFunc00d2fc10();

	toFunc00d2ffd0();

	toFunc00d30390();

	toFunc00d30750();

	toFunc00d30b10();

	toFunc00d30ed0();

	toFunc00e78890();

	toFunc012ca3d0();

	toFun012e0250();
}

void fullFillEdu(DWORD adr, UINT32 size)
{
	for (int i = 0; i < size; i++)
	{
		fullFillEduEntry(adr);
		adr = adr + 0x3e4;
	}

}

void fullFillEduEntry(DWORD adr)
{
	int o3c = 6;
	Write(&o3c, adr+0x3c, 4);

	int o40 = 5;
	Write(&o40, adr + 0x40, 4);

	int o44 = 11;
	Write(&o44, adr + 0x44, 4);

	int o48 = 3;
	Write(&o48, adr + 0x48, 4);

	int o84 = 3;
	Write(&o84, adr + 0x84, 4);

	int o88 = 5;
	Write(&o88, adr + 0x88, 4);

	int oA4 = 3;
	Write(&oA4, adr + 0xA4, 4);

	int oA8 = -1;
	Write(&oA8, adr + 0xA8, 4);

	int oB0 = 3;
	Write(&oB0, adr + 0xB0, 4);

	int oB4 = -1;
	Write(&oB4, adr + 0xB4, 4);

	int oBC = 3;
	Write(&oBC, adr + 0xBC, 4);

	int oC0 = -1;
	Write(&oC0, adr + 0xC0, 4);

	float o11C = 1;
	Write(&o11C, adr + 0x11C, 4);

	int o120 = 1053609165;
	Write(&o120, adr + 0x120, 4);

	int o124 = 1071225242;
	Write(&o124, adr + 0x124, 4);

	int o140 = 5;
	Write(&o140, adr + 0x140, 4);

	int o144 = 7;
	Write(&o144, adr + 0x144, 4);

	int o148 = 4;
	Write(&o148, adr + 0x148, 4);

	int o14C = 10;
	Write(&o14C, adr + 0x14C, 4);

	int o16C = 15;
	Write(&o16C, adr + 0x16C, 4);

	int o188 = 5;
	Write(&o188, adr + 0x188, 4);

	int o18C = 7;
	Write(&o18C, adr + 0x18C, 4);

	int o190 = 4;
	Write(&o190, adr + 0x190, 4);

	int o194 = 10;
	Write(&o194, adr + 0x194, 4);

	int o1B4 = 15;
	Write(&o1B4, adr + 0x1B4, 4);

	int o1BC = 6;
	Write(&o1BC, adr + 0x1BC, 4);

	int o244 = 5;
	Write(&o244, adr + 0x244, 4);

	int o248 = 7;
	Write(&o248, adr + 0x248, 4);

	int o24C= 4;
	Write(&o24C, adr + 0x24C, 4);

	int o250 = 10;
	Write(&o250, adr + 0x250, 4);


	int o270 = 15;
	Write(&o270, adr + 0x270, 4);

	int o28C = 5;
	Write(&o28C, adr + 0x28C, 4);

	int o290 = 7;
	Write(&o290, adr + 0x290, 4);

	int o294 = 4;
	Write(&o294, adr + 0x294, 4);

	int o298 = 10;
	Write(&o298, adr + 0x298, 4);

	int o2B8 = 15;
	Write(&o2B8, adr + 0x2B8, 4);

	int o2C0 = 6;
	Write(&o2C0, adr + 0x2C0, 4);

	int o2E4 = 5;
	Write(&o2E4, adr + 0x2E4, 4);

	int o2E8 = 7;
	Write(&o2E8, adr + 0x2E8, 4);

	int o2EC = 4;
	Write(&o2EC, adr + 0x2EC, 4);

	int o2F0 = 10;
	Write(&o2F0, adr + 0x2F0, 4);

	int o310 = 15;
	Write(&o310, adr + 0x310, 4);

	int o31C = 6;
	Write(&o31C, adr + 0x31C, 4);


	int o340 = 5;
	Write(&o340, adr + 0x340, 4);

	int o344 = 7;
	Write(&o344, adr + 0x344, 4);

	int o348 = 4;
	Write(&o348, adr + 0x348, 4);

	int o34C = 10;
	Write(&o34C, adr + 0x34C, 4);

	int o36C = 15;
	Write(&o36C, adr + 0x36C, 4);

	int o374 = 6;
	Write(&o374, adr + 0x374, 4);



	char* p388 = (char*)new char[100];

	p388 = p388 + 8;
	DWORD o388 = reinterpret_cast<DWORD>(p388);
	Write(&o388, adr + 0x388, 4);


	char* p38c390 = (char*)new char[100];

	p38c390 = p38c390 + 8;
	DWORD o38C = reinterpret_cast<DWORD>(p38c390);
	Write(&o38C, adr + 0x38C, 4);

	DWORD o390 = reinterpret_cast<DWORD>(p38c390);
	Write(&o390, adr + 0x390, 4);


	int o3B0 = 32;
	Write(&o3B0, adr + 0x3B0, 4);

	float o3B4 = 1;
	Write(&o3B4, adr + 0x3B4, 4);

	int o3d0 = 15;
	Write(&o3d0, adr + 0x3d0, 4);


}

void writeFieldOfEdu(DWORD adr, DWORD offset)
{
	DWORD fild = ourEDU;
	fild += offset;
	Write(&fild, adr, 4);
}


void writeUnitDBVtableAdress(DWORD adr)
{
	Write(&ourUDB, adr, 4);
}

void writeUnitDBUnitAdress(DWORD adr)
{
	Write(&ourEDU,adr,4);
}

void writeNumberOfTupes(DWORD adr)
{
	DWORD* fild = &numberOfTupes;

	Write(&fild, adr, 4);
}

void toFunc004101e0()
{
	//        0041023f   MOV        ECX ,eduEntryes_018c2ba8
	//function argument
	//0041023f+1 - adress
	writeUnitDBVtableAdress(0x0041023f + 1);

	//        00410249     MOV        ECX ,eduEntryes_018c2ba8
	//functon argument
	//00410249+1 - adress
	writeUnitDBVtableAdress(0x00410249 + 1);

}

void toFunc00411e0c()
{
	//        00411fdc     MOV        ECX ,eduEntryes_018c2ba8
	//function argument
	//00411fdc+1
	writeUnitDBVtableAdress(0x00411fdc + 1);

	//        00411fe6    MOV        ECX ,eduEntryes_018c2ba8
	//function argument
	//00411fe6+1
	writeUnitDBVtableAdress(0x00411fe6 + 1);

	//        00411ff8      MOV        ECX ,eduEntryes_018c2ba8
	//function argument
	//00411ff8+1
	writeUnitDBVtableAdress(0x00411ff8 + 1);
}

void toFunc0043c640()
{
	//        0043c77f       MOV        param_1 ,eduEntryes_018c2ba8 
	//function argument
	//0043c77f+1
	writeUnitDBVtableAdress(0x0043c77f + 1);
}

void toFunc0043e390()
{
	//0043e464      MOV        param_1, eduEntryes_018c2ba8
	//function argument
	//0043e464+1
	writeUnitDBVtableAdress(0x0043e464 + 1);
}

void toFunc004758f0()
{
	//        00475f3e       MOV        param_1 ,eduEntryes_018c2ba8
	//function argument
	//00475f3e+1
	writeUnitDBVtableAdress(0x00475f3e + 1);
}

void toFunc00477c50()
{
	//        00477e80     CMP        dword ptr [eduEntryes_018c2ba8.numberOfTupes ]   = null
	//comparison if (0 < (int)eduEntryes_018c2ba8.numberOfTupes) {
	//00477e80+2
	writeNumberOfTupes(0x00477e80 + 2);

	//        00477e8c be  e8  2b       MOV        ESI ,eduEntryes_018c2ba8.unitTupes[0].field_0x3c = null
	//getting field 0x3c
	//00477e8c+1
	writeFieldOfEdu(0x00477e8c + 1,0x3c);
 
	//        00477ee6    CMP        EDI ,dword ptr [eduEntryes_018c2ba8.numberOfTup  = null
	// while ((int)uVar13 < (int)eduEntryes_018c2ba8.numberOfTupes);
	//00477ee6+2
	writeNumberOfTupes(0x00477ee6 + 2);


}

void toFunc0047a140()
{
	//        0047a6f8 TEST       byte ptr [EDI *0x4  + eduEntryes_018c2ba8.unitTu  = null
	//((*(byte *)&eduEntryes_018c2ba8.unitTupes[iVar3].field_0x3af & 0x20) 
	//0047a6f8+3
	writeFieldOfEdu(0x0047a6f8 + 3, 0x3af);

	//        0047a700  LEA        EDI ,[EDI *0x4  + eduEntryes_018c2ba8.unitTupes[0]  = null
	//iVar3 = FUN_008ec7d0(piVar11,iVar3 * 0x3e4 + 0x18c2bac);
	//0047a700+3
	writeUnitDBUnitAdress(0x0047a700 + 3);


	//        0047a71a     MOV        param_1 ,eduEntryes_018c2ba8 
	//0047a71a+1
	writeUnitDBVtableAdress(0x0047a71a + 1);


	//        0047a767        MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//0047a767+1
	writeUnitDBVtableAdress(0x0047a767 + 1);




}

void toFunc004d2600()
{
	//        004d2aa3      LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0]  = null
	//*extraout_EAX_00 = (undefined *)(iVar3 * 0x3e4 + 0x18c2bac);
	//004d2aa3+ 3
	writeUnitDBUnitAdress(0x004d2aa3 + 3);


	//        004d2b08   LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//*extraout_EAX_01 = (undefined *)(iVar3 * 0x3e4 + 0x18c2bac);
	//004d2b08+3
	writeUnitDBUnitAdress(0x004d2b08 + 3);

	//        004d2bf2      MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function argument
	//004d2bf2+1
	writeUnitDBVtableAdress(0x004d2bf2 + 1);

	//        004eae3e     MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function argument
	//004eae3e+1
	writeUnitDBVtableAdress(0x004eae3e + 1);


}

void toFunc004f11d0()
{
	//        004f122c     MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//004f122c+1
	writeUnitDBVtableAdress(0x004f122c + 1);


}

void toFunc004f27f0()
{
	//        004f282c 66  8b  14       MOV        DX,word ptr [EDX *0x4  + eduEntryes_018c2ba8.uni  = null
	//for comparison, first line
	//       (*(ushort *)&eduEntryes_018c2ba8.unitTupes[*(int *)(param_1 + uVar2 * 4)].field_0xd6 <
	//*(ushort*)&eduEntryes_018c2ba8.unitTupes[*(int*)(param_1 + 4 + uVar2 * 4)].field_0xd6))
	//004f282c+4
	writeFieldOfEdu(0x004f282c + 4, 0xd6);

	//        004f2834     CMP        DX,word ptr [ESI *0x4  + eduEntryes_018c2ba8.uni  = null
	//for comparison, next line
	//       (*(ushort *)&eduEntryes_018c2ba8.unitTupes[*(int *)(param_1 + uVar2 * 4)].field_0xd6 <
	//*(ushort*)&eduEntryes_018c2ba8.unitTupes[*(int*)(param_1 + 4 + uVar2 * 4)].field_0xd6))
	//004f2834 + 4
	writeFieldOfEdu(0x004f2834 + 4, 0xd6);

	//        004f2851  MOV        SI,word ptr [ESI *0x4  + eduEntryes_018c2ba8.uni  = null
	//for comparison, first line
	//    if (*(ushort *)&eduEntryes_018c2ba8.unitTupes[iVar1].field_0xd6 <=
	//*(ushort*)&eduEntryes_018c2ba8.unitTupes[*(int*)(param_1 + param_2 * 4)].field_0xd6)
	//004f2851 + 4
	writeFieldOfEdu(0x004f2851 + 4, 0xd6);


	//        004f2863      CMP        SI,word ptr [EBP *0x4  + eduEntryes_018c2ba8.uni  = null
	//for comparison, next line
	//    if (*(ushort *)&eduEntryes_018c2ba8.unitTupes[iVar1].field_0xd6 <=
	//*(ushort*)&eduEntryes_018c2ba8.unitTupes[*(int*)(param_1 + param_2 * 4)].field_0xd6)
	//004f2863+4
	writeFieldOfEdu(0x004f2863 + 4, 0xd6);


}

void toFunc004fab70()
{
	//        004fab92      CMP        dword ptr [eduEntryes_018c2ba8.numberOfTupes ]   = null
	//comparison
	//004fab92+2
	writeNumberOfTupes(0x004fab92 + 2);

	//        004faba0      MOV        EBP ,eduEntryes_018c2ba8.unitTupes[0].field_0x3  = null
	//getting field
	//puVar9 = (uint *)&eduEntryes_018c2ba8.unitTupes[0].field_0x380;
	//004faba0+1
	writeFieldOfEdu(0x004faba0 + 1, 0x380);
	

	//        004fabdb      CMP        EDI ,dword ptr [eduEntryes_018c2ba8.numberOfTup  = null
	//} while ((int)ppiVar11 < (int)eduEntryes_018c2ba8.numberOfTupes);
	//004fabdb+2
	writeNumberOfTupes(0x004fabdb + 2);

	//        004fac53     CMP        dword ptr [EAX *0x4  + eduEntryes_018c2ba8.unitT  = null
	//if (*(int *)&eduEntryes_018c2ba8.unitTupes[*piVar8].field_0x3c == 4) {
	//004fac53+3
	writeFieldOfEdu(0x004fac53 + 3, 0x3c);


	//        004fad59      CMP        byte ptr [EAX *0x4  + eduEntryes_018c2ba8.unitTu  = null
	//if (*(char *)&eduEntryes_018c2ba8.unitTupes[*piVar8].field_0x8d < '\0') {
	//004fad59+3
	writeFieldOfEdu(0x004fad59 + 3, 0x8d);



}

void toFunc0050af60()
{
	//        0050afa4   MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//0050afa4+1
	writeUnitDBVtableAdress(0x0050afa4 + 1);

}

void toFunc0052f460()
{
	//        0052f52f      MOV        param_1 ,dword ptr [EAX *0x4  + eduEntryes_018c2b  = null
	//*(int *)&eduEntryes_018c2ba8.unitTupes[param_1_00[2]].field_0x44 * 4);
	//0052f52f+3
	writeFieldOfEdu(0x0052f52f + 3, 0x44);

	//        0052f53d    LEA        EAX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//0052f53d+3
	writeUnitDBUnitAdress(0x0052f53d + 3);

	//        0052f5c8    MOV        param_1 ,dword ptr [EAX *0x4  + eduEntryes_018c2b  = null
	//*(int *)&eduEntryes_018c2ba8.unitTupes[param_1_00[2]].field_0x44 * 4);
	//0052f5c8+3
	writeFieldOfEdu(0x0052f5c8 + 3, 0x44);

	//        0052f5d6   LEA        EAX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//0052f5d6+3
	writeUnitDBUnitAdress(0x0052f5d6 + 3);



}

void toFunc0052f640()
{
	//        0052f694      CMP        dword ptr [eduEntryes_018c2ba8.numberOfTupes ]   = null
	//if (0 < (int)eduEntryes_018c2ba8.numberOfTupes) {
	//0052f694+2
	writeNumberOfTupes(0x0052f694 + 2);

	//        0052f6aa  MOV        param_1 ,eduEntryes_018c2ba8.unitTupes[0].field  = null
	//pfVar3 = (float *)&eduEntryes_018c2ba8.unitTupes[0].field_0x398;
	//0052f6aa+1
	writeFieldOfEdu(0x0052f6aa + 1, 0x398);

	//        0052f6fb   CMP        EDX ,dword ptr [eduEntryes_018c2ba8.numberOfTup  = null
	//} while (iVar4 < (int)eduEntryes_018c2ba8.numberOfTupes);
	//0052f6fb+2
	writeNumberOfTupes(0x0052f6fb + 2);


}

void toFunc005906a0()
{
	//        005906be       TEST       byte ptr [EAX *0x4  + eduEntryes_018c2ba8.unitTu  = null
	//if ((*(byte *)&eduEntryes_018c2ba8.unitTupes[*piVar4].field_0x3af & 0x20) == 0) {
	//005906be+3
	writeFieldOfEdu(0x005906be + 3, 0x3af);

}

void toFunc00590710()
{
	//        005907b1     CMP        word ptr [EAX *0x4  + eduEntryes_018c2ba8.unitTu  = null
	//CMP word ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0xd6],BP
	//005907b1+4
	writeFieldOfEdu(0x005907b1 + 4, 0xd6);


	//maybe another function))
	//        005909f1   CMP        word ptr [EAX *0x4  + eduEntryes_018c2ba8.unitTu  = null
	//        if (*(ushort *)(param_1 + 0xc) <=*(ushort*)&eduEntryes_018c2ba8.unitTupes[local_18[uVar2]].field_0xd6)
	//005909f1+4
	writeFieldOfEdu(0x005909f1 + 4, 0xd6);

}

void toFunc00590b90()
{
	//        00590c16      MOV        EDX ,eduEntryes_018c2ba8.unitTupes[0].field_0xd6 = null
	//00590c16+1
	writeFieldOfEdu(0x00590c16 + 1, 0xd6);
}

void toFunc005994d0()
{
	//        005994ed     MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//005994ed+1
	writeUnitDBVtableAdress(0x005994ed + 1);



}

void toFunc005d8230()
{
	//        005d82c4    MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//005d82c4+1
	writeUnitDBVtableAdress(0x005d82c4 + 1);

	//        005d82f5     LEA        EAX ,[EDX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//*param_1 = iVar3 * 0x3e4 + 0x18c2bac;
	//005d82f5+3
	writeUnitDBUnitAdress(0x005d82f5 + 3);

	//        005d832c       MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//005d832c+1
	writeUnitDBVtableAdress(0x005d832c + 1);


	//        005d835d     LEA        EAX ,[EDX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//*param_1 = iVar3 * 0x3e4 + 0x18c2bac;
	//005d835d+3
	writeUnitDBUnitAdress(0x005d835d + 3);

	//        005e61a6   LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//iVar1 = local_40 * 0x3e4 + 0x18c2bac;
	//005e61a6+3
	writeUnitDBUnitAdress(0x005e61a6 + 3);




}

void toFunc005ee630()
{
	//        005eea76     MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//sub_faction = FUN_008ee9e0(uVar14,uVar6,uVar5,uVar12,uVar15,uVar11,uVar10);
	//005eea76+1
	writeUnitDBVtableAdress(0x005eea76 + 1);


	//        005eee9b     MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//age = FUN_008ee9e0(uVar14,uVar6,uVar5,uVar12,uVar15,uVar10,uVar11);
	//005eee9b+1
	writeUnitDBVtableAdress(0x005eee9b + 1);


}

void toFunc005f59a0()
{
	//005f59ce        MOV        param_1, dword ptr[eduEntryes_018c2ba8.numberO = null
	//MOV param_1,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//005f59ce+2
	writeNumberOfTupes(0x005f59ce + 2);



}

void toFunc005f5a50()
{
	//005f5a93      MOV        param_1, dword ptr[eduEntryes_018c2ba8.numberO = null
	//MOV param_1,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//005f5a93+2
	writeNumberOfTupes(0x005f5a93 + 2);


}

void toFunc005f5af0()
{
	//005f5b32       MOV        param_1, dword ptr[eduEntryes_018c2ba8.numberO = null
	//MOV param_1,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//005f5b32+2
	writeNumberOfTupes(0x005f5b32 + 2);

}

void toFunc005f6320()
{
	//        005f632c       LEA        EAX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EAX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//005f632c+3
	writeUnitDBUnitAdress(0x005f632c + 3);

}

void toFunc005f6360()
{
	//        005f6412      MOV        EDX ,dword ptr [EAX *0x4  + eduEntryes_018c2ba8.u  = null
	//MOV EDX,dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x30]
	//005f6412+3
	writeFieldOfEdu(0x005f6412 + 3, 0x30);

	//        005f6419     LEA        EAX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EAX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//005f6419+3
	writeUnitDBUnitAdress(0x005f6419 + 3);

}

void toFunc005f7890()
{
	//005f78a2
	//LEA EAX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//return param_1[2] * 0x3e4 + 0x18c2bac
	//005f78a2+3
	writeUnitDBUnitAdress(0x005f78a2 + 3);
}

void toFunc0060bbd0()
{
	//        0060bc62       MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function param
	//0060bc62+1
	writeUnitDBVtableAdress(0x0060bc62 + 1);


	//        0060bef7      MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function param
	//0060bef7+1
	writeUnitDBVtableAdress(0x0060bef7 + 1);

}

void toFunc0060ca20()
{
	//        0060cbe4      LEA        EAX ,[EDX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//*param_1 = iVar6 * 0x3e4 + 0x18c2bac;
	//0060cbe4+3
	writeUnitDBUnitAdress(0x0060cbe4 + 3);


}

void toFunc0060d2e0()
{
	//        0060d329      MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function param
	//0060d329+1
	writeUnitDBVtableAdress(0x0060d329 + 1);

	//        0060d561   LEA        EDX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EDX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//0060d561+3
	writeUnitDBUnitAdress(0x0060d561 + 3);



}

void toFunc0060e800()
{
	//        0060e866 LEA        EDI ,[EDI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EDI,[EDI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//0060e866+3
	writeUnitDBUnitAdress(0x0060e866 + 3);



}

void toFunc00632810()
{
	//        00632848      LEA        ECX ,[ECX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA ECX,[ECX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00632848+3
	writeUnitDBUnitAdress(0x00632848 + 3);
}

void toFunc006343d0()
{
	//        0063443a     MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function param
	//0063443a+1
	writeUnitDBVtableAdress(0x0063443a + 1);
}

void toFunc00635ea0()
{
	//        00635f1d    CMP        dword ptr [eduEntryes_018c2ba8.numberOfTupes ]   = null
	//if (eduEntryes_018c2ba8.numberOfTupes != 0) {
	//00635f1d+2
	writeNumberOfTupes(0x00635f1d + 2);

	//        00635f34    MOV        ESI ,eduEntryes_018c2ba8.unitTupes[0].field_0x3  = null
	//MOV ESI,eduEntryes_018c2ba8.unitTupes[0].field_0x3ac
	//iVar12 = 0x18c2f58;
	//00635f34 + 1
	writeFieldOfEdu(0x00635f34+1, 0x3ac);

	//        00635fbb      CMP        EBP ,dword ptr [eduEntryes_018c2ba8.numberOfTup  = null
	//} while (uVar9 < eduEntryes_018c2ba8.numberOfTupes);
	//00635fbb+2
	writeNumberOfTupes(0x00635fbb + 2);

}

void toFunc007156f0()
{
	//        0071598b       MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//0071598b+1
	writeUnitDBVtableAdress(0x0071598b + 1);

}

void toFunc007185a0()
{
	//        00718891      MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//00718891+1
	writeUnitDBVtableAdress(0x00718891 + 1);


}

void toFunc00719ee0()
{
	//        0071a1ea     MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function argument
	//0071a1ea+1
	writeUnitDBVtableAdress(0x0071a1ea + 1);


}

void toFunc0071a3e0()
{
	//        0071a3fe     MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function argument
	//0071a3fe+1
	writeUnitDBVtableAdress(0x0071a3fe + 1);

}

void toFunc0071a770()
{
	//        0071a8ec     LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA ESI,[ESI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//0071a8ec+3
	writeUnitDBUnitAdress(0x0071a8ec + 3);

	//        0071aa91       LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//*extraout_EAX_01 = iVar1 * 0x3e4 + 0x18c2bac;
	//0071aa91+3
	writeUnitDBUnitAdress(0x0071aa91 + 3);

	//        0071acb0    LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA ESI,[ESI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//0071acb0+3
	writeUnitDBUnitAdress(0x0071acb0 + 3);

	//        0071ae66     LEA        ESI ,[ESI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA ESI,[ESI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//0071ae66+3
	writeUnitDBUnitAdress(0x0071ae66 + 3);

}

void toFunc0071b520()
{
	//        0071b5b9       MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function param
	//0071b5b9+1
	writeUnitDBVtableAdress(0x0071b5b9 + 1);

}

void toFunc00749fd0()
{
	//        0074a03a      MOV        param_1 ,eduEntryes_018c2ba8                     = 
	//function param
	//0074a03a+1
	writeUnitDBVtableAdress(0x0074a03a + 1);

}

void toFunc0086cde0()
{
	//        0086ce39      MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function param
	//0086ce39+1
	writeUnitDBVtableAdress(0x0086ce39 + 1);

}

void toFunc008a9a60()
{
	//        008a9c19     LEA        EDX ,[ECX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EDX,[ECX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//008a9c19+3
	writeUnitDBUnitAdress(0x008a9c19 + 3);

	//        008a9ce5      LEA        ECX ,[EAX *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA ECX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//008a9ce5+3
	writeUnitDBUnitAdress(0x008a9ce5 + 3);
}

void toFunc008ba9d0()
{
	//        008bba47      MOV        ECX ,eduEntryes_018c2ba8                         = 
	//function param
	//008bba47+1
	writeUnitDBVtableAdress(0x008bba47 + 1);

}

void toFunc008e2330()
{
	//        008e2692     LEA        EDI ,[EDI *0x4  + eduEntryes_018c2ba8.unitTupes[0  = null
	//LEA EDI,[EDI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//008e2692+3
	writeUnitDBUnitAdress(0x008e2692 + 3);
}

void toFunc00a3ea50()
{
	//        00a3ea53      CMP        dword ptr [eduEntryes_018c2ba8.numberOfTupes ]   = null
	//CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],0x0
	//00a3ea53+2
	writeNumberOfTupes(0x00a3ea53 + 2);

	//        00a3ea7c       MOV        dword ptr [ESP  + local_30 ],eduEntryes_018c2ba8  = null
	//MOV dword ptr [ESP + local_30],eduEntryes_018c2ba8.unitTupes[0].unitType
	//00a3ea7c+4
	writeUnitDBUnitAdress(0x00a3ea7c + 4);

	//        00a3ed87      CMP        EAX ,dword ptr [eduEntryes_018c2ba8.numberOfTup  = null
	//CMP EAX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00a3ed87+2
	writeNumberOfTupes(0x00a3ed87 + 2);
}

void toFunc00a3ee30()
{
	//00a3ee33	CMP dword ptr[eduEntryes_018c2ba8.numberOfTupes], 0x0
	//00a3ee33+2
	writeNumberOfTupes(0x00a3ee33 + 2);

	//00a3ee58		MOV EBP,eduEntryes_018c2ba8.unitTupes[0].unitType
	//ppcVar9 = (char **)0x18c2bac;
	//00a3ee58+1
	writeUnitDBUnitAdress(0x00a3ee58 + 1);


	//00a3efa3  CMP EAX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00a3efa3+2
	writeNumberOfTupes(0x00a3efa3 + 2);

}

void toFunc00a40c10()
{
	//00a40c13		CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],0x0
	//00a40c13+2
	writeNumberOfTupes(0x00a40c13 + 2);


	//!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!
	//00a40c3e		//MOV dword ptr [ESP + local_24],eduEntryes_018c2ba8.unitTupes[0].field_0x14[52]
	//local_24 = (int *)(eduEntryes_018c2ba8.unitTupes[0].field_0x14 + 0x34);
	//00a40c3e+4
	writeFieldOfEdu(0x00a40c3e + 4, 0x48);


	//00a40dcd		CMP EAX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//} while ((int)local_c < (int)eduEntryes_018c2ba8.numberOfTupes);
	//00a40dcd+2
	writeNumberOfTupes(0x00a40dcd + 2);
}

void toFunc00a84c60()
{
	//00a84eed		MOV ECX,eduEntryes_018c2ba8
	//00a84eed+1
	writeUnitDBVtableAdress(0x00a84eed+1);



}

void toFunc00a85160()
{
	//00a853ed		MOV ECX,eduEntryes_018c2ba8
	//00a853ed+1
	writeUnitDBVtableAdress(0x00a853ed + 1);
}

void toFunc00a87000()
{
	//00a870c9		MOV param_1,eduEntryes_018c2ba8
	//00a870c9+1
	writeUnitDBVtableAdress(0x00a870c9 + 1);

}

void toFunc00a8cb40()
{
	//00a8d606		MOV param_1,eduEntryes_018c2ba8
	//00a8d606+1
	writeUnitDBVtableAdress(0x00a8d606 + 1);

}

void toFunc00a8d770()
{
	//00a8da2d		CMP dword ptr [EDX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//if (*(int *)(eduEntryes_018c2ba8.unitTupes[iVar1].field_0x14 + 0x28) == 4) {
	//00a8da2d+3
	writeFieldOfEdu(0x00a8da2d + 3, 0x3C);

	//00a8db48		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//if (*(int *)(eduEntryes_018c2ba8.unitTupes[iVar1].field_0x14 + 0x28) == 4) {
	//00a8db48+3
	writeFieldOfEdu(0x00a8db48 + 3, 0x3C);

	//00a8dc7e		MOV param_1,eduEntryes_018c2ba8
	//00a8dc7e+1
	writeUnitDBVtableAdress(0x00a8dc7e + 1);
}

void toFunc00ab91a0()
{
	//00ab92a8		LEA EAX,[EDX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00ab92a8+3
	writeUnitDBUnitAdress(0x00ab92a8 + 3);



}

void toFunc00ad87d0()
{
	//00ad8acd		LEA ECX,[EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00ad8acd+3
	writeUnitDBUnitAdress(0x00ad8acd + 3);
}

void toFunc00adfbd0()
{
	//00adfe9c		LEA EAX,[EDX*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00adfe9c+3
	writeUnitDBUnitAdress(0x00adfe9c + 3);

}

void toFunc00ae2bc0()
{
	//00ae2eb5		LEA EDX,[param_1*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00ae2eb5+3
	writeUnitDBUnitAdress(0x00ae2eb5 + 3);
}

void toFunc00b90e00()
{
	//00b90ea1		MOV EDX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00b90ea1+2
	writeNumberOfTupes(0x00b90ea1 + 2);


	//00b90eba		MOV EDI,eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]
	//piVar5 = (int *)(eduEntryes_018c2ba8.unitTupes[0].field_0x14 + 0x28);
	//00b90eba+1
	writeFieldOfEdu(0x00b90eba + 1, 0x3C);


}

void toFunc00b91150()
{
	//00b91220		MOV param_1,eduEntryes_018c2ba8
	//00b91220+1
	writeUnitDBVtableAdress(0x00b91220 + 1);
}

void toFunc00b94e50()
{
	//00b94fd6		MOV EAX,[eduEntryes_018c2ba8.numberOfTupes]
	//00b94fd6+1
	writeNumberOfTupes(0x00b94fd6 + 1);


	//00b94feb		MOV EBP,eduEntryes_018c2ba8.unitTupes[0].unitType
	//00b94feb+1
	writeUnitDBUnitAdress(0x00b94feb + 1);
}

void toFunc00ba1eb0()
{
	//00ba1ee8		MOV EAX,[eduEntryes_018c2ba8.numberOfTupes]
	//00ba1ee8+1
	writeNumberOfTupes(0x00ba1ee8 + 1);


	//00ba1ef7		MOV EDI,eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]	
	//00ba1ef7+1
	writeFieldOfEdu(0x00ba1ef7 + 1, 0x3C);
}

void toFunc00ba26b0()
{
	//00ba26cf		MOV param_1,eduEntryes_018c2ba8
	//00ba26cf+1
	writeUnitDBVtableAdress(0x00ba26cf + 1);

}

void toFunc00ba2ae0()
{
	//00ba2af7		MOV param_1,eduEntryes_018c2ba8
	//00ba2af7+1
	writeUnitDBVtableAdress(0x00ba2af7 + 1);

	//00ba2b0e		MOV param_1,eduEntryes_018c2ba8
	//00ba2b0e+1
	writeUnitDBVtableAdress(0x00ba2b0e + 1);
}

void toFunc00bac9c0()
{
	//00bacd67		MOV param_1,eduEntryes_018c2ba8
	//00bacd67+1
	writeUnitDBVtableAdress(0x00bacd67 + 1);
}

void toFunc00c57720()
{
	//00c57744		CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],EBX
	//00c57744+2
	writeNumberOfTupes(0x00c57744 + 2);


	//00c57756		MOV ESI,eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]
	//00c57756+1
	writeFieldOfEdu(0x00c57756 + 1, 0x3C);

	//00c577c7		CMP EBX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00c577c7+2
	writeNumberOfTupes(0x00c577c7 + 2);

}

void toFunc00c7d680()
{
	//00c7d6c9		CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],EDI
	//00c7d6c9 + 2
	writeNumberOfTupes(0x00c7d6c9 + 2);

	//00c7d6d9		MOV ESI,eduEntryes_018c2ba8.unitTupes[0].unitType
	//00c7d6d9+1
	writeUnitDBUnitAdress(0x00c7d6d9 + 1);


	//00c7d71f		CMP EDI,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00c7d71f+2
	writeNumberOfTupes(0x00c7d71f + 2);
}

void toFunc00ca30a0()
{
	//00ca3235		MOV ECX,eduEntryes_018c2ba8
	//00ca3235+1
	writeUnitDBVtableAdress(0x00ca3235 + 1);
}

void toFunc00cbb680()
{
	//00cbb717		CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],EBX
	//00cbb717+2
	writeNumberOfTupes(0x00cbb717 + 2);

	//00cbb72b		MOV ESI,eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]
	//00cbb72b+1
	writeFieldOfEdu(0x00cbb72b + 1, 0x3C);


	//00cbb77a		CMP EAX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00cbb77a+2
	writeNumberOfTupes(0x00cbb77a + 2);

}

void toFunc00cf4020()
{
	//00cf404d		MOV EBP,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00cf404d+2
	writeNumberOfTupes(0x00cf404d + 2);


	//00cf405f		MOV EBX,eduEntryes_018c2ba8.unitTupes[0].unitType
	//00cf405f+1
	writeUnitDBUnitAdress(0x00cf405f + 1);
}

void toFunc00cf4fe0()
{
	//00cf50af		MOV param_1,eduEntryes_018c2ba8
	//00cf50af+1
	writeUnitDBVtableAdress(0x00cf50af + 1);



}

void toFunc00d0d3e0()
{
	//00d0d414		MOV param_1,eduEntryes_018c2ba8
	//00d0d414+1
	writeUnitDBVtableAdress(0x00d0d414 + 1);

}

void toFunc00d0e140()
{
	//00d0e3ec		MOV param_1,eduEntryes_018c2ba8
	//00d0e3ec+1
	writeUnitDBVtableAdress(0x00d0e3ec + 1);
}

void toFunc00d13310()
{
	//00d133c6		MOV param_1,eduEntryes_018c2ba8
	//00d133c6+1
	writeUnitDBVtableAdress(0x00d133c6 + 1);
}

void toFunc00d19050()
{
	//00d19093	MOV ECX,eduEntryes_018c2ba8
	//00d19093+1
	writeUnitDBVtableAdress(0x00d19093 + 1);

}

void toFunc00d196e0()
{
	//00d19f4f		MOV param_1,eduEntryes_018c2ba8
	// 00d19f4f + 1
	writeUnitDBVtableAdress(0x00d19f4f + 1);
}

void toFunc00d19fa0()
{
	//00d1a0ac		MOV param_1,eduEntryes_018c2ba8
	//00d1a0ac+1
	writeUnitDBVtableAdress(0x00d1a0ac + 1);
}

void toFunc00d2da70()
{
	//00d2db3a		LEA ESI,[ESI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00d2db3a+3
	writeUnitDBUnitAdress(0x00d2db3a + 3);
}

void toFunc00d2dc20()
{
	//00d2dce2		LEA ESI,[ESI*0x4 + eduEntryes_018c2ba8.unitTupes[0].unitType]
	//00d2dce2+3
	writeUnitDBUnitAdress(0x00d2dce2 + 3);

}

void toFunc00d2f3a0()
{
	//00d2f4aa		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2f4aa+3
	writeFieldOfEdu(0x00d2f4aa + 3, 0x3C);

	//00d2f5c1		MOV ECX,eduEntryes_018c2ba8
	//00d2f5c1+1
	writeUnitDBVtableAdress(0x00d2f5c1 + 1);

	//00d2f6de		CMP dword ptr [EDX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2f6de+3
	writeFieldOfEdu(0x00d2f6de + 3, 0x3C);

	//00d2f7db		MOV ECX,eduEntryes_018c2ba8
	//00d2f7db+1
	writeUnitDBVtableAdress(0x00d2f7db + 1);
}

void toFunc00d2f890()
{
	//00d2f981		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2f981+3
	writeFieldOfEdu(0x00d2f981 + 3, 0x3C);

	//00d2fa1e		MOV ECX,eduEntryes_018c2ba8
	//00d2fa1e+1
	writeUnitDBVtableAdress(0x00d2fa1e + 1);

	//00d2faec		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2faec+3
	writeFieldOfEdu(0x00d2faec + 3, 0x3C);

	//00d2fb8e		MOV ECX,eduEntryes_018c2ba8
	//00d2fb8e+1
	writeUnitDBVtableAdress(0x00d2fb8e + 1);
}

void toFunc00d2fc10()
{
	//00d2fd1c		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2fd1c + 3
	writeFieldOfEdu(0x00d2fd1c + 3, 0x3C);

	//00d2fdea		MOV ECX,eduEntryes_018c2ba8
	//00d2fdea+1
	writeUnitDBVtableAdress(0x00d2fdea + 1);

	//00d2feb4		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d2feb4 + 3
	writeFieldOfEdu(0x00d2feb4 + 3, 0x3C);

	//00d2ff4f		MOV ECX,eduEntryes_018c2ba8
	//00d2ff4f+1
	writeUnitDBVtableAdress(0x00d2ff4f + 1);
}

void toFunc00d2ffd0()
{
	//00d300dc		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d300dc+3
	writeFieldOfEdu(0x00d300dc + 3, 0x3C);

	//00d301aa		MOV ECX,eduEntryes_018c2ba8
	//00d301aa+1
	writeUnitDBVtableAdress(0x00d301aa + 1);

	//00d30274		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	// 00d30274 + 3
	writeFieldOfEdu(0x00d30274 + 3, 0x3C);

	//00d3030f		MOV ECX,eduEntryes_018c2ba8
	//00d3030f+1
	writeUnitDBVtableAdress(0x00d3030f + 1);


}

void toFunc00d30390()
{
	//00d3049c		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d3049c+3		
	writeFieldOfEdu(0x00d3049c + 3, 0x3C);

	//00d3056a		MOV ECX,eduEntryes_018c2ba8
	//00d3056a+1
	writeUnitDBVtableAdress(0x00d3056a + 1);

	//00d30634		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d30634+3
	writeFieldOfEdu(0x00d30634 + 3, 0x3C);

	//00d306cf		MOV ECX,eduEntryes_018c2ba8
	//00d306cf+1
	writeUnitDBVtableAdress(0x00d306cf + 1);

}

void toFunc00d30750()
{
	//00d3085c		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d3085c+3
	writeFieldOfEdu(0x00d3085c + 3, 0x3C);

	//00d3092a		MOV ECX,eduEntryes_018c2ba8
	//00d3092a+1
	writeUnitDBVtableAdress(0x00d3092a + 1);

	//00d309f4		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d309f4+3
	writeFieldOfEdu(0x00d309f4 + 3, 0x3C);

	//00d30a8f		MOV ECX,eduEntryes_018c2ba8
	//00d30a8f+1
	writeUnitDBVtableAdress(0x00d30a8f + 1);

}

void toFunc00d30b10()
{
	//00d30c1c		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d30c1c+3
	writeFieldOfEdu(0x00d30c1c + 3, 0x3C);

	//00d30cea		MOV ECX,eduEntryes_018c2ba8
	//00d30cea+1
	writeUnitDBVtableAdress(0x00d30cea + 1);

	//00d30db4		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d30db4+3
	writeFieldOfEdu(0x00d30db4 + 3, 0x3C);

	//00d30e4f		MOV ECX,eduEntryes_018c2ba8
	//00d30e4f+1
	writeUnitDBVtableAdress(0x00d30e4f + 1);
}

void toFunc00d30ed0()
{
	//00d30fdc		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d30fdc+3
	writeFieldOfEdu(0x00d30fdc + 3, 0x3C);

	//00d310aa		MOV ECX,eduEntryes_018c2ba8
	//00d310aa+1
	writeUnitDBVtableAdress(0x00d310aa + 1);

	//00d31174		CMP dword ptr [EAX*0x4 + eduEntryes_018c2ba8.unitTupes[0].field_0x14[40]],0x4
	//00d31174+3
	writeFieldOfEdu(0x00d31174 + 3, 0x3C);

	//00d3120f		MOV ECX,eduEntryes_018c2ba8
	//00d3120f+1
	writeUnitDBVtableAdress(0x00d3120f + 1);
}

void toFunc00e78890()
{
	//00e788c8		CMP dword ptr [eduEntryes_018c2ba8.numberOfTupes],EBP
	//00e788c8+2
	writeNumberOfTupes(0x00e788c8 + 2);

	//00e788dc		MOV EAX,eduEntryes_018c2ba8.unitTupes[0].field_0xd4[48]
	//00e788dc+1
	writeFieldOfEdu(0x00e788dc + 1, 0x104);

	//00e789af		CMP ECX,dword ptr [eduEntryes_018c2ba8.numberOfTupes]
	//00e789af+2
	writeNumberOfTupes(0x00e789af + 2);
}

void toFunc012ca3d0()
{
	//012ca3d0		MOV ECX,eduEntryes_018c2ba8
	//012ca3d0+1
	writeUnitDBVtableAdress(0x012ca3d0 + 1);

}

void toFun012e0250()
{
	//012e0250		MOV ECX,eduEntryes_018c2ba8
	//012e0250+1
	writeUnitDBVtableAdress(0x012e0250 + 1);
}
