## homework 4.57
- 修改 ../sim/pipe/pipe-btfnt.hcl，如: 4.57-pipe-lf.hcl  
- 修改处详见difference
- 测试文件使用pipe-lf-test.ys, 用YAS汇编后的为文件为pipe-lf-test.yo  
```ubuntu:~/Documents/CSAPP/chapter_4/4.57$ ../sim/misc/yas pipe-lf-test.ys```

### 重新生成pipe模拟器
将homework 4.57 的pipe-lf.hcl放入../sim/pipe文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make psim VERSION=lf
```  
### 测试模拟器  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ ./psim -g ../../4.57/pipe-lf-test.yo
```  
可打开GUI界面，运行后得到测试结果:

#### pipe-lf-Processor  
![pipe-lf-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.57/pipe-lf-Processor.png)  

#### pipe-std-Processor（原版pipe模拟器）  
![pipe-std-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.57/pipe-std-Processor.png)