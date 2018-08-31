#include "csapp.h"

int main(void)
{
	char *emptylist[] = { NULL };
	setenv("QUERY_STRING", 
		   "127.0.0.1:4000/source/cgi-bin/adder?first=100&last=20", 1);
	Execve("./source/cgi-bin/url_handler", emptylist, environ);
}

/* output: (日志文件记录正常工作)
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

/* 在hosts文件中添加"127.0.0.1"时，提示错误
Connection: close
Content-length: 60
Content-type: text/html

This site can’t be reached
127.0.0.1 refused to connect.
*/