#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char*argv[])  // ./a.out   源文件 目标文件)
{

    // 1. 通过open打开文件，只读
    int srcfd = open(argv[1], O_RDONLY);

    if(srcfd == -1) {
        perror("open");
        return -1;
    }
    // 2. 创建一个新的文件（拷贝文件），只写
    int destfd = open(argv[2], O_WRONLY | O_CREAT, 0664);
    
    if(destfd == -1) {
        perror("open");
        return -1;
    }
    // 3. 读写操作
    // 创建缓冲区
    char buf[1024] = {0};

    int len = 0;
    while(( len = read(srcfd, buf, sizeof(buf)) ) > 0 ) {
        // 每读一次数据，就写入到拷贝文件中
        write(destfd, buf, len);
    }

    // 4. 关闭文件
    close(srcfd);
    close(destfd);
    
    return 0;
}
