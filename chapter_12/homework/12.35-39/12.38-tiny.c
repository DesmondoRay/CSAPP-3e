/*
 * homework 12.38
 *
 * 实现一个 TINY Web 服务器的并发预线程化的版本
 * 服务器应该根据当前的负载，动态地增加或减少线程的数目； 
 * 可行的一个策略是当缓冲区变满时，将线程数量翻倍，而当缓冲区变为空时，将线程数量减半。
 *
 * 注：chrome测试出错，firefox测试正常！！！
 */

#include "csapp.h"
#include "sbuf.h"
#define SBUFSIZE 2
#define MAXTHREADS 16

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);
void *thread(void *vargp);
void *add_thread(void *vargp);
void create_threads(void);

sbuf_t sbuf; /* Shared buffer of connected descriptors */
pthread_t tid[MAXTHREADS]; // 保存临时增加的线程id
int thread_num; // 当前线程数量
int nthreads;  // 动态调整的最大线程数
sem_t mutex;

int main(int argc, char **argv)
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
	nthreads = 1; // 初始只有一个对等线程处理请求
	thread_num = 1;

    /* Check command line args */
    if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
	sbuf_init(&sbuf, SBUFSIZE);
	sem_init(&mutex, 0, 1);
	Pthread_create(&tid[0], NULL, thread, NULL);
	
    while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
		sbuf_insert(&sbuf, connfd);  /* Insert connfd in buffer */
		/* 判断缓冲区是否已满 */
		int val_slots, val_items;
		sem_getvalue(&(sbuf.slots), &val_slots);
		//sem_getvalue(&(sbuf.items), &val_items);
		if (val_slots == 0) {
			puts("**************** val_slots *****************\n");  // 用于测试
			nthreads *= 2;
			create_threads();
		}
		/*
		else if (val_items == 0) {
			puts("**************** val_items *****************\n");  // 用于测试
			if (nthreads > 1)
				nthreads /= 2;
		}
		*/
		printf("nthreads = %d, thread_num = %d \n", nthreads, thread_num); // 用于测试
    }
}

/* 第一个线程，永不终止 */
void *thread(void *vargp)
{
	Pthread_detach(pthread_self());
	while (1) {
		int connfd = sbuf_remove(&sbuf);  /* Remove connfd from buffer */
		doit(connfd);
		sleep(10);  // 用于测试
		Close(connfd);
	}
}

/* 添加临时线程 */
void create_threads(void)
{
	int i;
	for (i = thread_num; i < nthreads; i++) {
		thread_num++;
		Pthread_create(&tid[thread_num], NULL, add_thread, NULL);
	}
}

/* 之后添加的临时线程
 * 每次需要判断当前线程的数量(thread_num)和动态调整的最大线程数(nthreads)
 * 当thread_num > nthreads时，关闭当前线程，以达到动态调整线程数量的功能
 */
void *add_thread(void *vargp)
{
	Pthread_detach(pthread_self());
	int i = 0;
	while (1) {
		/* 判断缓冲区是否为空 */
		int val_items;
		sem_getvalue(&(sbuf.items), &val_items);
		if (nthreads > 1 && val_items == 0) {
			P(&mutex);
			nthreads /= 2;
			V(&mutex);
		}
		/* 判断当前线程的数量(thread_num)和动态调整的最大线程数(nthreads) */
		P(&mutex);
		if (thread_num > nthreads) {  /* 该操作需要在调用sbuf_remove()函数之前 */
			thread_num--;
			i = 1;
		}
		V(&mutex);
		if (i) Pthread_cancel(pthread_self());
		int connfd = sbuf_remove(&sbuf);  /* Remove connfd from buffer */
		doit(connfd);
		sleep(10);  // 用于测试
		Close(connfd);
	}
}

/*
 * doit - handle one HTTP request/response transaction
 */
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
	printf("Request headers:\n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }
    read_requesthdrs(&rio);

    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0) {
		clienterror(fd, filename, "404", "Not found",
					"Tiny couldn't find this file");
		return;
    }

    if (is_static) { /* Serve static content */          
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
						"Tiny couldn't read the file");
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
    }
    else { /* Serve dynamic content */
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
						"Tiny couldn't run the CGI program");
			return;
		}
		serve_dynamic(fd, filename, cgiargs);
    }
}

/*
 * read_requesthdrs - read HTTP request headers
 */
void read_requesthdrs(rio_t *rp) 
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) {
		Rio_readlineb(rp, buf, MAXLINE);
		printf("%s", buf);
    }
    return;
}

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {  /* Static content */
		strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		if (uri[strlen(uri)-1] == '/')
	    	strcat(filename, "home.html");
		return 1;
    }
    else {  /* Dynamic content */
		ptr = index(uri, '?');
		if (ptr) {
	    	strcpy(cgiargs, ptr+1);
	    	*ptr = '\0';
		}
		else 
	    	strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		return 0;
    }
}

/*
 * serve_static - copy a file back to the client 
 */
void serve_static(int fd, char *filename, int filesize) 
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
 
    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sConnection: close\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    printf("Response headers:\n");
    printf("%s", buf);

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
		strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
		strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpeg");
    else
		strcpy(filetype, "text/plain");
}  

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
void serve_dynamic(int fd, char *filename, char *cgiargs) 
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n"); 
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
  
    if (Fork() == 0) { /* Child */
		/* Real server would set all CGI vars here */
		setenv("QUERY_STRING", cgiargs, 1);
		Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */
		Execve(filename, emptylist, environ); /* Run CGI program */
    }
    Wait(NULL); /* Parent waits for and reaps child */
}

/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
