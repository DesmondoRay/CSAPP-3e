## homework 4.58
- 修改 ../sim/pipe/pipe-btfnt.hcl，如: 4.58-pipe-1w.hcl  
- 修改处详见difference
- 测试文件使用pipe-1w-test.ys, 用YAS汇编后的为文件为pipe-1w-test.yo  
```desmondo@Rays:~/Documents/CSAPP/chapter_4/4.58$ ../sim/misc/yas pipe-1w-test.ys```

### 重新生成pipe模拟器
将homework 4.58 的pipe-1w.hcl放入../sim/pipe文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ make psim VERSION=1w
```  
### 测试模拟器  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/pipe$ ./psim -g ../../4.58/pipe-1w-test.yo
```  
可打开GUI界面，运行后得到测试结果:

#### pipe-1w-Processor  
![pipe-1w-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.58/pipe-1w-Processor.png)
![pipe-1w-Memory-Contents](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.58/pipe-1w-Memory-Contents.png)  

#### pipe-std-Processor（原版pipe模拟器）  
![pipe-std-Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.58/pipe-std-Processor.png)
![pipe-std-Memory-Contents](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.58/pipe-std-Memory-Contents.png)  