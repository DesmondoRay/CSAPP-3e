## homework 4.55
- 修改 ../sim/pipe/pipe-nt.hcl，如: 4.55-pipe-nt.hcl  
- 修改处详见difference
- 测试文件使用homework 4.52 的iaddq_test.yo

### 重新生成pipe模拟器
将homework 4.55 的pipe-nt.hcl放入../sim/pipe文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make psim VERSION=nt
```
得到带有iaddq执行的pipe模拟器。  
### 测试模拟器  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/4.55$ ../sim/misc/yas pipe-nt-test.ys
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ ./psim -g ../../4.55/pipe-nt-test.yo
```  
可打开GUI界面，运行后得到测试结果:

#### pipe-nt-Processor  
![pipe-nt-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.55/pipe-nt-Processor.png)  

#### pipe-std-Processor  
![pipe-nt-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.55/pipe-std-Processor.png)