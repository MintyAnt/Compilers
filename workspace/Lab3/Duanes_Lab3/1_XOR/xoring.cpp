#include <stdio.h>

int main()
{
	int x = 0;
	
	x += 1;
	
	int y = 1;
	
	x -= y;
	
	for (int index=0; index < 50; index++)
	{
		printf("%d, %d", x, y);
	}
	
	return x;
}