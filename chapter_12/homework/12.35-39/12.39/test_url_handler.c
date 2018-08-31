#include "csapp.h"

int main(void)
{
	char *emptylist[] = { NULL };
	setenv("QUERY_STRING", 
		   "127.0.0.1:4000/source/cgi-bin/adder?first=100&last=20", 1);
	Execve("./source/cgi-bin/url_handler", emptylist, environ);
}

/* output: 
desmondo@Rays:~/Documents/CSAPP/chapter_12/homework/12.35-39/12.39$ ./test
HTTP/1.0 200 OK
Server: Tiny Web Server
Connection: close
Content-length: 108
Content-type: text/html

Welcome to adder: THE Internet addition portal.
<p>The answer is: 100 + 20 = 120
<p>Thanks for visiting!
*/