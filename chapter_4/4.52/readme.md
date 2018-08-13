## homework 4.52
- 修改 ../sim/seq/seq-full.hcl，如: 4.52-seq-full.hcl  
- 修改处详见difference
- 测试文件iaddq_test.ys，用YAS汇编后的为文件为iaddq_test.yo

### 文本版本测试
```
ubuntu:~/Documents/CSAPP/chapter_4/4.47$ ../sim/misc/yas iaddq_test.ys
ubuntu:~/Documents/CSAPP/chapter_4/4.47$ ../sim/misc/yis iaddq_test.yo
Stopped in 11 steps at PC = 0x13.  Status 'HLT', CC Z=0 S=0 O=0
Changes to registers:
%rax:	0x0000000000000000	0x0000000000000002
%rsp:	0x0000000000000000	0x0000000000000200
%rdi:	0x0000000000000000	0x0000000000000020

Changes to memory:
0x0018:	0x0000000000000000	0x0000000000000001
0x0020:	0x0000000000000000	0x0000000000000002
0x01f8:	0x0000000000000000	0x0000000000000013
```
### GUI版本测试
#### 重新生成模拟器
将homework 4.52 的seq-full.hcl放入../sim/seq文件夹内，修改Makefile  
将```TKLIBS=-L/usr/lib -ltk -ltcl```  
改为 ```TKLIBS=-L/usr/lib -ltk8.5 -ltcl8.5```  
终端输入命令：  
```
ubuntu:~/Documents/CSAPP/chapter_4/sim/seq$ make clean
ubuntu:~/Documents/CSAPP/chapter_4/sim/seq$ make ssim VERSION=full
```
得到带有iaddq执行的模拟器。  

#### 测试模拟器  
终端输入命令：  
```ubuntu:~/Documents/CSAPP/chapter_4/sim/seq$ ./ssim -g ../../4.52/iaddq_test.yo```  
可打开GUI界面，运行后得到测试结果  
![Processor](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.52/Processor.png)
![Memory Contents](https://github.com/DesmondoRay/CSAPP/blob/master/chapter_4/4.52/Memory%20Contents.png)