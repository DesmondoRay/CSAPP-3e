## homework 11.13

1. 在tiny.c主函数中添加  
``` 
if (Signal(SIGPIPE, SIG_IGN) == SIG_ERR)
{
    unix_error("mask signal pipe error");
}
```

2. 修csapp.c的```Rio_writen()```，如下： 
```
void Rio_writen(int fd, void *usrbuf, size_t n) 
{
    if (rio_writen(fd, usrbuf, n) != n) {
		unix_error("Rio_writen error");
		if (errno == EPIPE)
			unix_error("EPIPE error. Connection closed");
	}
}
```

3. 修改tiny.c的```serve_dynamic```函数，当子进程可以处理EPIPE错误
```
if (Fork() == 0) 
{
    setenv("QUERY_STRING", cgiargs, 1); 
    Dup2(fd, STDOUT_FILENO);
    if (Signal(SIGPIPE, SIG_DFL) == SIG_ERR)
    {
        unix_error("mask signal pipe error");
    }
    Execve(filename, emptylist, environ);
}
```