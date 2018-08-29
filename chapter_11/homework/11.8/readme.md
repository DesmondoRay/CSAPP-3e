## homework 11.8

### diff
```
desmondo@Rays:~/Documents/CSAPP/chapter_11/homework/11.8$ diff 11.8-tiny.c ../11.7/11.7-tiny.c
15d14
< void handler(int sig);
23,24d21
< 	
< 	Signal(SIGCHLD, handler);
44,50d40
< void handler(int sig)
< {
< 	int old_errno = errno;
< 	Wait(NULL); /* Parent waits for and reaps child */
< 	errno = old_errno;
< }
< 
211a202
>     Wait(NULL); /* Parent waits for and reaps child */
```

### test
```
desmondo@Rays:~$ telnet 127.0.0.1 4000
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
GET /source/cgi-bin/11.8 HTTP/1.1 

HTTP/1.0 200 OK
Server: Tiny Web Server
test start
running...
running...
running...
running...
running...
test done!
Connection closed by foreign host.
```