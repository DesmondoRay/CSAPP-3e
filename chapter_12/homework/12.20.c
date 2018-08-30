/**
 * homework 12.20
 */

#define N 10

int readcnt, writecnt; // Initially = 0
int read_first;
sem_t mutex, w; // Both initially = 1

void reader(void)
{
	while (1) {
		if (read_first == 0 && writecnt == 1)
			continue;
		P(&mutex);
		readcnt++;
		if (readcnt == 1) {
			P(&w);
			read_first = 0;
		}
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
		if (read_first == 1 && readcnt > 1)
			continue;
		P(&w);
		writecnt = 1;
		
		/* Critical section */
		/* Writing happends */
		
		writecnt = 0;
		read_first = 1;
		V(&w);
	}
}