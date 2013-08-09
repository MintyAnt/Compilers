#include <stdio.h>

int main()
{
	int x = 0;
	
	x += 1;
	
	int y = 1;
	
	x -= y;
	
	for (int index=0; index < 50; index++)
	{
		x *= index;
		y /= x;
		x /= y;
		printf("%d, %d", x, y);
	}
	
	x = 0;
	
	return x;
}