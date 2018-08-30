## homework 11.12

用POST方法传递参数，URI中将不含参数，而是在消息体中传递参数; 修改如下：

### 修改adder.htlm
```<form action="/source/cgi-bin/adder" method="GET">```  
改为```<form action="/source/cgi-bin/adder" method="POST">```  

### 修改tiny.c
```
desmondo@Rays:~/Documents/CSAPP/chapter_11/homework/11.12$ diff 11.12-tiny.c ../11.11/11.11-tiny.c
8,9c8,9
< void read_requesthdrs(rio_t *rp, char *cgiargs, int method);
< int parse_uri(char *uri, char *filename, char *cgiargs, int method);
---
> void read_requesthdrs(rio_t *rp);
> int parse_uri(char *uri, char *filename, char *cgiargs);
73,74d72
< 	else if (strcasecmp(method, "POST") == 0)
< 		http_method = 2;
80c78
<     read_requesthdrs(&rio, cgiargs, http_method);
---
>     read_requesthdrs(&rio);
83c81
<     is_static = parse_uri(uri, filename, cgiargs, http_method);
---
>     is_static = parse_uri(uri, filename, cgiargs);
111c109
< void read_requesthdrs(rio_t *rp, char *cgiargs, int method) 
---
> void read_requesthdrs(rio_t *rp) 
121,126d118
< 	fflush(stdout);
< 	
< 	if (method == 2) { /* method: POST */
< 		Rio_readnb(rp, buf, rp->rio_cnt);
< 		strcpy(cgiargs, buf);
< 	}
134c126
< int parse_uri(char *uri, char *filename, char *cgiargs, int method) 
---
> int parse_uri(char *uri, char *filename, char *cgiargs) 
147,154c139,142
< 		if (method == 0) {
< 			ptr = index(uri, '?');
< 			if (ptr) {
< 	    		strcpy(cgiargs, ptr+1);
< 	    		*ptr = '\0';
< 			}
< 			else 
< 	    		strcpy(cgiargs, "");
---
> 		ptr = index(uri, '?');
> 		if (ptr) {
> 	    	strcpy(cgiargs, ptr+1);
> 	    	*ptr = '\0';
155a144,145
> 		else 
> 	    	strcpy(cgiargs, "");
```