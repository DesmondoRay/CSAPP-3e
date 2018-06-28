long lt_cnt = 0;
long ge_cnt = 0;

long absdiff_se_goto(long x, long y)
{
	long result;
	if (x < y)
		goto x_lt_y;
	ge_cnt++;
	result = x - y;
	return result;
x_lt_y:
	lt_cnt++;
	result = y - x;
	return result;
}