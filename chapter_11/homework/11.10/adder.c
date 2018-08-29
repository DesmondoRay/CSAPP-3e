#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000


int main(void)
{
	char *buf, *p;
	char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
	int n1 = 0, n2 = 0;
	
	if ((buf = getenv("QUERY_STRING")) != NULL) {
		p = strchr(buf, '&');
		*p = '\0';
		strcpy(arg1, buf);
		strcpy(arg2, p+1);
		sscanf(arg1, "first=%d", &n1);
		sscanf(arg2, "last=%d", &n2);
	}
	
	sprintf(content, "Welcome to adder: ");
	sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
	sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
			content, n1, n2, n1+n2);
	sprintf(content, "%sThanks for visiting!\r\n", content);
	
	printf("Connection: close\r\n");
	printf("Content-length: %d\r\n", (int)strlen(content));
	printf("Content-type: text/html\r\n\r\n");
	printf("%s", content);
	fflush(stdout);
	
	exit(0);
}