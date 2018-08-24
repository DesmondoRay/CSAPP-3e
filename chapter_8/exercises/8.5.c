/* exercise 8.5 */

unsigned int snooze(unsigned int secs)
{
	unsigned int rest = sleep(secs);
	printf("Slept for %d of %d secs.\n", secs-rest, secs);
	return rest;
}