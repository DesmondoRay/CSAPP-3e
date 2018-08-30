/**
 * homework 12.21
 */

int writecnt;	// Initially = 0
sem_t mutex, w; 		// Both initially = 1

void reader(void)
{
	while (1) {
		if (writecnt > 0) 
			continue;
		P(&w);
		
		/* Critical section */
		/* Reading happends */
		
		V(&w);
	}
}

vlid writer(void)
{
	while (1) {
		P(&mutex);
		writecnt++;
		V(&mutex);
		
		P(&w);
		
		/* Critical section */
		/* Writing happends */
		
		V(&w);
		P(&mutex);
		writecnt--;
		V(&mutex);
	}
}