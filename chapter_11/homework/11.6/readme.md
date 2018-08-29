## homework 11.6

### A.
```
desmondo@Rays:~/Documents/CSAPP/chapter_11/homework$ diff 11.6-tiny.c ../source/tiny.c
55c55
< 	// printf("Request headers:\n");
---
> 	printf("Request headers:\n");
99d98
< 	printf("%s\n", buf);
```

### B.
```
Accepted connection from (localhost, 44130)
GET / HTTP/1.1
Host: 127.0.1.1:4000

Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/68.0.3440.106 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9,ja;q=0.8
Cookie: _ga=GA1.1.1691636378.1535544355; tz=Asia%2FShanghai

Response headers:
HTTP/1.0 200 OK
Server: Tiny Web Server
Connection: close
Content-length: 15
Content-type: text/html
```

### C.
HTTP/1.1

### D.
