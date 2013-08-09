#include <stdio.h>

int main()
{
	int x = 20;
	int y = 50;
	for (int index=0; index < 3; index++)
	{
		x = y / x;
		y = x / y;
	}
	
	printf("%d, %d", x, y);
}