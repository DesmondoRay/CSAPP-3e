# homework 12.39

代理端口默认为3000  

## A. 主程序代码: proxy.c
### 1. 在浏览器打开代理的主页[127.0.0.1:3000](127.0.0.1:3000), 文件位置： source/proxy.html  
![proxy.html](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/1.png)  
### 2. 输入一个服务器的请求，proxy.html将url请求转送到一个代理的url_handler程序，位置/source/cgi-bin/url_handler  
![4.1](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/4.1.png)  
图为代理程序服务器上接受的请求信息：  
![url_handler](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/2.png)
### 3. url_handler程序将url请求转换成可识别的字符串——调用url_handler.c中url_decode()函数  

### 4. url_handler程序检查url请求是否在过滤文件中，url过滤文件位置: /source/etc/hosts  
#### 4.1 检查通过:
- 将url请求记录到日志文件中, 日志文件位置: /source/etc/log  
- 转发请求给服务器  
图为Tiny Web服务器上接受的请求信息：  
![url_decode](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/3.png)
- 从服务器接收响应并返回结果给浏览器  
![4.2](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/4.2.png)  
#### 4.2 检查未通过:
如：在/source/etc/hosts文件中添加：127.0.0.1  
检查未通过，将检查结果(url请求不可用)返回给浏览器  
![4.3](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_12/homework/12.39/source/4.3.png)  

### B.
可参考homework 12.37，代码见: proxy_thread.c