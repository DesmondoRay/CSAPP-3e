# homework 7.9

## test 1
```
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ gcc foo6.c bar6.c
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ ./a.out
0x55
```
## 反汇编 
```
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ objdum -d a.out
...
0000000000400526 <main>:
  400526:	55                   	push   %rbp
  400527:	48 89 e5             	mov    %rsp,%rbp
  40052a:	e8 12 00 00 00       	callq  400541 <p2>
  40052f:	b8 00 00 00 00       	mov    $0x0,%eax
  400534:	5d                   	pop    %rbp
  400535:	c3                   	retq
...
```

## 解释
foo6.c中定义的main是一个强(strong)符号，而bar6.c中定义的main是一个弱(weak)符号；  
根据规则2，p2函数中使用的是foo6.c中定义的main，而main符号的值是main函数编译后的指令的值；  
所以使用```printf("0x%x\n", main);```语句打印0x55.  

## test 2 
修改 bar6.c: ```printf("0x%x\n", main);```  
改为bar6_1.c: ```printf("0x%x\n", *(&main+1));```  
output:  
```
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ gcc foo6.c bar6_1.c
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ ./a.out
0x48
```

## test 3 
修改 bar6.c: ```char main;```  
改为 bar6_2.c:  ```int main;```   
output:  
```desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ gcc foo6.c bar6_2.c
/usr/bin/ld: Warning: alignment 1 of symbol `main' in /tmp/ccQS2Jk5.o is smaller than 4 in /tmp/ccUubKls.o
desmondo@Rays:~/Documents/CSAPP/chapter_7/homework_7.9$ ./a.out
0xe5894855
```
打印main地址int大小的值(小端机器)。