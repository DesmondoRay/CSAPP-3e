## homework 4.54
- 修改 ../sim/pipe/pipe-full.hcl，如: 4.54-pipe-full.hcl  
- 修改处详见difference
- 测试文件使用homework 4.52 的iaddq_test.yo

### GUI版本测试
#### 重新生成pipe模拟器
将homework 4.54 的pipe-full.hcl放入../sim/pipe文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make psim VERSION=full
```
得到带有iaddq执行的pipe模拟器。  
#### 测试模拟器  
终端输入命令：  
```ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ ./psim -g ../../4.52/iaddq_test.yo```  
可打开GUI界面，运行后得到测试结果:
![Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.54/Processor.png)
![Memory Contents](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.54/Memory%20Contents.png)