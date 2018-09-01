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
#define NON_NUM '0'

int url_decode(const char* str, char* result);
int hex2num(char c);

int main(void)
{
	char *p, *host, *port;
	char url[MAXLINE], uri[MAXLINE], buf[MAXLINE], content[MAXLINE];
	int connfd;
	int read_length;
	rio_t rio;
	
	if ((p = getenv("QUERY_STRING")) != NULL) {
		char *temp = strchr(p, '=');
		strcpy(url, temp+1);
	}
	/* 将url转换成可识别的字符串 */
	url_decode(url, buf);
	strcpy(url, buf);
	/* 打开hosts文件，并检查url */
	FILE *hosts_fp, *log_fp;
	if ((hosts_fp = fopen("source/etc/hosts", "r")) == NULL) {
		fprintf(stderr, "Can't open file: hosts\n");
		exit(0);
	}
	while ((fgets(buf, MAXLINE, hosts_fp)) != NULL) {
		if (strstr(url, buf)) {
			/* 给浏览器返回错误提示 */
			strcpy(content, "This site can not be reached.\r\n<p>");
			strcat(content, buf);
			strcat(content, " refused to connect.\r\n<p>");
			printf("Connection: close\r\n");
			printf("Content-length: %d\r\n", (int)strlen(content));
			printf("Content-type: text/html\r\n\r\n");
			printf("%s", content);
			fflush(stdout);
			fclose(hosts_fp);
			return 0;
		}
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
	
	// 注：Open_clientfd(), Rio_writen(), Rio_readinitb()顺序不能错
	/* 与服务器连接 */ 
	connfd = Open_clientfd(host, port);
	Rio_writen(connfd, uri, strlen(uri)+1); 
	
	/* Generate the HTTP response */
	Rio_readinitb(&rio, connfd);
	content[0] = '\0';
	 while ((read_length = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
      Rio_writen(1, buf, read_length);
	fflush(stdout);
	
	return 0;
}
			   
int hex2num(char c)
{
    if (c>='0' && c<='9') return c - '0';
    if (c>='a' && c<='z') return c - 'a' + 10;
    if (c>='A' && c<='Z') return c - 'A' + 10;
    
    printf("unexpected char: %c", c);
    return NON_NUM;
}

int url_decode(const char* str, char* result)
{
    char ch,ch1,ch2;
    int i;
    int j = 0; //record result index
	int slen = strlen(str);
 
    if ((str==NULL) || (result==NULL)) {
        return 0;
    }
 
    for (i=0; i < slen; i++) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i+2 < slen) {
                    ch1 = hex2num(str[i+1]);//高4位
                    ch2 = hex2num(str[i+2]);//低4位
                    if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
                        result[j++] = (char)((ch1<<4) | ch2);
                    i += 2;
                    break;
                } else 
                    break;
            default:
                result[j++] = ch;
                break;
        }
    }
    
    result[j] = '\0';
    return j;
}