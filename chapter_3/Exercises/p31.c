void switcher(long a, long b, long c, long *dest)
{
	long val;
	switch(a) {
		case 5:
			c = b ^ 15;
		case 0:
			val = 112 + c;
			break;
		case 2:
		case 7:
			val = (b + c) << 2;
			break;
		case 4:
			val = a;
			break;
		default:
			val = b;
	}
	*dest = val;
}