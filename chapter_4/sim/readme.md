### 来源：  
[Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)/Student Site](http://csapp.cs.cmu.edu/3e/students.html)  

[下载链接: Chapter 4: Processor Architecture/Source distribution](http://csapp.cs.cmu.edu/3e/sim.tar)  

### 注意事项：  
安装Tcl和Tk: ```sudo apt-get install tcl8.5-dev tk8.5-dev tcl8.5 tk8.5```  
修改Makefile:   
```
GUIMODE=-DHAS_GUI (去掉#号)
TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5
TKINC=-isystem /usr/include/tcl8.5
```

make命令可能需要安装flex和bison: ```sudo apt-get install flex bison```  