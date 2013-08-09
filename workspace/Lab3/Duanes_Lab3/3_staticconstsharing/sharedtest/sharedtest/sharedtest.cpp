#include "stdafx.h"
#include <stdio.h>
#include <string>

using namespace std;
#pragma optimize( "", off )
char* ModifyValue(const char* inVal)
{
	char* modifyingVal = const_cast<char*>(inVal);
	int ptrAddress = (int)(void*)inVal;
	__asm
	{
		mov eax, ptrAddress
		mov WORD PTR [eax], 'f'
	}
	return modifyingVal;
}
#pragma optimize( "", on )

int main()
{
	static char* val0 = "hello";
	static const char* val1 = "hello";
	const char* val2 = "hello";
	char* val3 = "hello";
	string val4 = "hello";

	printf("\nbefore: %s, %s, %s, %s, %s", val0, val1, val2, val3, val4.c_str());

	//char* newVal = ModifyValue(val3);

	printf("\nafter: %s, %s, %s, %s, %s", val0, val1, val2, val3, val4.c_str());

	const char* cval = val4.c_str();
	printf("\nafter: %p, %p, %p, %p, %p\n", (void*)val0, (void*)val1, (void*)val2, (void*)val3, (void*)cval);

	return 0;
}