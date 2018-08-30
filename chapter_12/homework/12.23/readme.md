## homework 12.23

如果echoclient.c如下所示   
``` C
int main(int argc, char **argv)
{
	int clientfd;
	char *host, *port, buf[MAXLINE];
	rio_t rio;
	
	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = argv[2];
	
	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
	
	while (Fgets(buf, MAXLINE, stdin) != NULL) {
		Rio_writen(clientfd, buf, strlen(buf));
		exit(0);  // 发送文本行之后就终止
		Rio_readlineb(&rio, buf, MAXLINE);
		Fputs(buf, stdout);
	}
}
```
使用这个echoclient与服务器连接，在发送一条文本行后，服务器终止，提示错误：
``` C
Rio_readlineb error: Connection reset by peer
```

修改如下：  
将check_clients()函数的```if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {```  
改为```if ((n = rio_readlineb(&rio, buf, MAXLINE)) > 0) {```  
不使用csapp.c的包装函数，可忽略该错误，并关闭该连接符，也就是执行```else```语句。  