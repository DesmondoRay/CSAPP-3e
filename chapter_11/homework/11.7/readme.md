## homework 11.7

### diff
```
desmondo@Rays:~/Documents/CSAPP/chapter_11/homework/11.7$ diff 11.7-tiny.c ../11.6/11.6-tiny.c
177,178d176
< 	else if (strstr(filename, ".mpg"))
< 		strcpy(filetype, "video/mpeg");
```

### 运行
```
desmondo@Rays:~/Documents/CSAPP/chapter_11/homework$ ./11.7-tiny 4000
```
浏览器输入: ```http://127.0.0.1:4000/source/mpg.mpg```  
下载mpg.mpg