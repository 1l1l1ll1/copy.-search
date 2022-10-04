# 1.利用文件I/O实现copy函数
## 1.文件描述符
    对于内核而言，所有打开的文件都通过文件描述符引用。文件描述符是一个非负整数。当打开一个现有文件或创建一个新文件时，内核向进程返回一个文件描述符。当读、写一个文件时，使用open或creat返回的文件描述符标识该文件，将其作为参数传送给read或write。
    
    按照惯例，UNIX系统shell把文件描述符0与进程的标准输入关联，文件描述符1与标准输出关联，文件描述符2与标准错误关联。这是各种 shell以及很多应用程序使用的惯例，与UNIX内核无关。尽管如此，如果不遵循这种惯例，很多UNIX系统应用程序就不能正常工作。
    
    在符合POSIX.1的应用程序中，幻数0、1、2虽然已被标准化，但应当把它们替换成符号常量STDIN_FILENO、STDOUT_FILENO和STDERR_FILENO以提高可读性。这些常量都在头文件<unistd.h>中定义。

## 2.使用文件IO完成文件的复制
UNIX系统中的大多数文件I/O只需用到5个函数：open、read、write、lseek以及close。然后说明不同缓冲长度对read和write函数的影响。

其中open，read，write的函数原型如下

![image](https://user-images.githubusercontent.com/114986300/193774527-a23c9cf4-1616-4a51-874f-b8bdb81b98a1.png)  
这两个函数的返回值：若成功返回文件描述符。若失败返回-1。
![image](https://user-images.githubusercontent.com/114986300/193775070-357d1583-2b8b-4cb2-8079-7b21a5039ec0.png)  
函数返回值：读到的字节数，若已到达文件尾返回0。若出错返回-1。
![image](https://user-images.githubusercontent.com/114986300/193775129-3d57a049-4a56-46b4-84c3-d66ace2f6df4.png)  
若成功返回写入的字节数，若失败返回-1。

这些函数也称为不带缓冲的I/O，不带缓冲的I/O指的是每个read和write函数都调用内核中的一个系统调用。
## 3.运行截图
Ubuntu以及gcc版本  
![image](https://user-images.githubusercontent.com/114986300/193778858-d1a9db63-edd2-4d3b-8554-5b3c0c6a1cc1.png)
![image](https://user-images.githubusercontent.com/114986300/193779502-025a80e9-21a9-4905-8669-244457587dd9.png)

