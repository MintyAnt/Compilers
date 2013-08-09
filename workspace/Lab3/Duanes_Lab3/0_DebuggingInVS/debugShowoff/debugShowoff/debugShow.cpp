#include <stdio.h>
#include <string>

using namespace std;

int shittyAdd(int inX, int inY)
{
	int newVariable = inX + inY;
	newVariable += 10;
	newVariable -= 10;
	return newVariable;
}

static int HASH_DAT(const char* inHash)
{
	int returnVal = 0;
	for (int x = 0; x < sizeof(inHash); ++x)
	{
		returnVal += inHash[x] % 10;
	}
	return returnVal;
}

int main(int argc, char **argv, char **envp)
{
	bool bRunIfLoop = false;
	if (bRunIfLoop)
	{
		printf("%d", shittyAdd(20, 15));
	}
	
	if (false)
	{
		int yy = 200;
		yy /= 43;
		printf("%d", yy);
	}

	int hashedValue = HASH_DAT("best");
	if (hashedValue == HASH_DAT("test"))
	{
		int x = 0;
	}

	for (int x = 0; x < 1000; ++x)
	{
		x += 2;
		if (x == 733)
			printf("X is now equal to 733!!!");
	}
}