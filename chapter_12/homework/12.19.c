/**
 * homework 12.19
 *
 * 只要有正在等待的读者，readcnt一定是大于0的
 */

int readcnt;
sem_t mutex, w;

void reader(void)
{
	while (1) {
		P(&mutex);
		readcnt++;
		if (readcnt == 1)
			P(&w);
		V(&mutex);
		
		/* Critical section */
		/* Reading happends */
		
		P(&mutex);
		readcnt--;
		if (readcnt == 0) /* Last out */
			V(&w);
		V(&mutex);
	}
}

void writer(void)
{
	while (1) {
		if (readcnt > 1)  /*** homework 12.19 added***/
			continue;
		P(&w);
		
		/* Critical section */
		/* Writing happends */
		
		V(&w);
	}
}