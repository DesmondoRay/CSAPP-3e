## homework 4.59

**4.47的冒泡排序性能最好；**  

三种版本代码的循环部分和测试结果如下：
- 4.47循环部分
```
    mrmovq 8(%rax), %r9
    mrmovq (%rax), %r10
    rrmovq %r9, %r11
    subq %r10, %r11
    jge update2
    rmmovq %r10, 8(%rax)
    rmmovq %r9, (%rax)
```
平均指令数为：5 + (7+2)/2 = 7;  没有跳转执行7条指令和2条nop指令；  
测试结果(详见4.47/4.47_b_test_result.txt):   
Stopped in 103 steps at PC = 0x13.  Status 'HLT', CC Z=1 S=0 O=0  

- 4.48循环部分
```
    mrmovq 8(%rax), %r9
    mrmovq (%rax), %r10
    rrmovq %r9, %r11
    subq %r10, %r11
    cmovl %r9, %r12
    cmovl %r10, %r9
    cmovl %r12, %r10
    rmmovq %r9, 8(%rax)
    rmmovq %r10, (%rax)
```
平均指令数为：9;  
测试结果(详见4.48/4.48_test_result.txt):   
Stopped in 121 steps at PC = 0x13.  Status 'HLT', CC Z=1 S=0 O=0  

- 4.49循环部分
```
    mrmovq 8(%rax), %r9
    mrmovq (%rax), %r10
    rrmovq %r9, %r11
    subq %r10, %r11
    rrmovq %r9, %r12
    cmovl %r10, %r12
    xorq %r12, %r10
    xorq %r9, %r10
    rrmovq %r12, %r9
    rmmovq %r9, 8(%rax)
    rmmovq %r10, (%rax)
```
平均指令数为：11;  
测试结果(详见4.49/4.49_test_result.txt):   
Stopped in 133 steps at PC = 0x13.  Status 'HLT', CC Z=1 S=0 O=0  