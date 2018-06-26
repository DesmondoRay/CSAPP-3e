#include <stdio.h>
#include <limits.h>

int tadd_ok(int x, int y);
int tsub_ok(int x, int y);

int main(void)
{
	int x, y;
	
	x = -3;
	y = INT_MIN;
	
	printf("%d\n", tsub_ok(x, y));
	return 0;
}

int tadd_ok(int x, int y)
{
	int s = x + y;
	if (x >= 0 && y >= 0)
		return s >= 0;
	else if (x < 0 && y < 0)
		return s <= 0;
}

int tsub_ok(int x, int y)
{
	return tadd_ok(x, -y);
}
