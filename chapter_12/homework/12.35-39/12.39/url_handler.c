/**
 * homework 12.39
 *
 * url_handler程序对浏览器发送过来的url进行检查
 * 首先检查url请求是否在过滤文件中；
 *   检查通过：
 *	   1. 将url请求记录到日志文件中
 *	   2. 转发请求给服务器
 *	   3. 从服务器接收响应并返回结果给浏览器
 *   检查未通过：
 *     4. 将检查结果(url请求不可用)返回给浏览器
 * url过滤文件位置: source/etc/hosts
 * 日志文件位置: source/etc/log
 */

#include "csapp.h"

int main(void)
{
	char *p, *host, *port;
	char url[MAXLINE], content[MAXLINE], uri[MAXLINE], buf[MAXLINE];
	int connfd;
	rio_t rio;
	
	if ((p = getenv("QUERY_STRING")) != NULL)
		strcpy(url, p);
	
	/* 打开hosts文件，并检查url */
	FILE *hosts_fp, *log_fp;
	if ((hosts_fp = fopen("source/etc/hosts", "r")) == NULL) {
		fprintf(stderr, "Can't open file: hosts\n");
		exit(0);
	}
	char read_temp[MAXLINE];
	while ((fgets(read_temp, MAXLINE, hosts_fp)) != NULL) {
		if (strstr(read_temp, url))
			;
	}
	fclose(hosts_fp);
	/* 打开log文件，并将url请求记录到log文件 */
	if ((log_fp = fopen("source/etc/log", "a")) == NULL) {
		fprintf(stderr, "Can't open file: log\n");
		exit(0);
	}
	fputs(url, log_fp);
	fputc('\n', log_fp);
	fclose(log_fp);
	/* 提取host, port, uri */
	p = strchr(url, ':');
	*p = '\0';
	host = url;
	port = p+1;
	p = strchr(port, '/');
	strcpy(uri, "GET ");
	strcat(uri, p);
	strcat(uri, " HTTP/1.1\r\n\r\n");
	*p = '\0';
	
	/* 与服务器连接 */
	connfd = Open_clientfd(host, port);
	Rio_writen(connfd, uri, strlen(uri)+1);
	
	Rio_readinitb(&rio, connfd);
	/* Make the response body */
	content[0] = '\0';
	while (Rio_readlineb(&rio, buf, MAXLINE) != 0)
		strcat(content, buf);
	
	/* Generate the HTTP response */
	printf("%s", content);
	
	fflush(stdout);
	return 0;
}