## homework 4.56
- 修改 ../sim/pipe/pipe-btfnt.hcl，如: 4.56-pipe-btfnt.hcl  
- 修改处详见difference
- 测试文件使用homework 4.48的48_bubble_sort.yo

### 重新生成pipe模拟器
将homework 4.56 的pipe-brfnt.hcl放入../sim/pipe文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make psim VERSION=btfnt
```  
### 测试模拟器  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ ./psim -g ../../4.48/48_bubble_sort.yo
```  
可打开GUI界面，运行后得到测试结果:

#### pipe-btfnt-Processor  
![pipe-btfnt-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.56/pipe-btfnt-Processor.png)  

#### pipe-std-Processor（原版pipe模拟器）  
![pipe-std-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.55/pipe-std-Processor.png)