#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
 
char*joint(char* head, char* name){
	char* ret = (char*)malloc(sizeof(char)*(strlen(head)+strlen(name)+3));
	int i=0;
	int location = 0;
	for(i=0; head[i]!='\0'; i++)ret[location++]=head[i];
	ret[location++]='/';
	for(i=0; name[i]!='\0'; i++)ret[location++]=name[i];
	ret[location] = '\0';
	return ret;
}
 
void Search(char* target, char* name){
	DIR* dir = opendir(name);
        struct dirent* file;
        while((file = readdir(dir)) != NULL){
		if(file->d_name[0] == '.')continue;
		struct stat filebuf;
		char* nextname = joint(name, file->d_name);   //组合文件绝对路径
		lstat(nextname, &filebuf);
		if(S_ISREG(filebuf.st_mode)){                 //如果是文件则判断是否含有目标字段
			int srcfd = open(nextname, O_RDONLY);
			
			if(srcfd == -1) {
        			printf("open error");
        		}
			
			char buf[1024] = {0};
			int len = 0;
   		 	while(( len = read(srcfd, buf, sizeof(buf)) ) > 0 ) {  //用缓冲区读取文件内容
        				// 每读一次数据，就写入到拷贝文件中
        			if(strstr(buf, target) != NULL){   //利用strstr进行内容检索
        				// 
		        		printf("%s\n", nextname);
				}
				close(srcfd);
    			}
		}
		if(S_ISDIR(filebuf.st_mode)){               //如果是目录文件则进行递归
			Search(target, nextname);
		}
        }
	closedir(dir);
 
}
 
int main(int argv,  char* argc[]){
	Search(argc[1],argc[2]);
	return 0;
}
