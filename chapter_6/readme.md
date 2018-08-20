# CPU 信息

## cache
linux系统cache相关信息保存在：/sys/devices/system/cpu/cpu0/cache 目录；  
``` terminal
desmondo@Rays:~$ cd /sys/devices/system/cpu/cpu0/cache
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache$ ls
index0  index1  index2  index3  power  uevent
``` 
### 位置： 
- L1: 只保存数据的d-cache, index0  
- L1: 只保存指令的i-cache, index1  
- L2: 统一的高速缓存 unified cache, index2  
- L3: 统一的高速缓存 unified cache, index3  

### 说明：
``` terminal
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache$ cd index0
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ ls
coherency_line_size  number_of_sets           shared_cpu_list  type
id                   physical_line_partition  shared_cpu_map   uevent
level                power                    size             ways_of_associativity
```

- coherency_line_size: 行(块)大小
- number_of_sets: 组数
- type: 类型，d-cache、i-cache等
- size: 缓存大小，容量
- ways_of_associativity: 每组的行数 

``` terminal
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache$ cd index0
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ cat coherency_line_size
64
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ cat number_of_sets
64
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ cat type
Data
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ cat size
32K
desmondo@Rays:/sys/devices/system/cpu/cpu0/cache/index0$ cat ways_of_associativity
8
``` 