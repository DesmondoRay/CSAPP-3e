## homework 12.39

代理端口默认为3000  

### A.
1. 在浏览器打开代理的主页[127.0.0.1:3000](127.0.0.1:3000), 文件位置： source/proxy.html  
![proxy.html](http: )  
2. 输入一个服务器的请求，proxy.html将url请求转送到一个代理的url_handler程序，见url_handler.c  
![url_handler](http: )
3. url_handler程序将url转换成可识别的字符串，将url_handler.c中url_decode()函数  
![url_decode](http: )
4. url_handler程序检查url是否在过滤文件中，url过滤文件位置: source/etc/hosts  
检查通过:
- 将url请求记录到日志文件中, 日志文件位置: source/etc/log  
- 转发请求给服务器  
- 从服务器接收响应并返回结果给浏览器  
![4.1](http: )  
![4.2](http: )  
检查未通过:
- 将检查结果(url请求不可用)返回给浏览器  
![4.3](http: )  

### B.