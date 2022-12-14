#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char*joint(char* head, char* name){                                                        //将目录名进行链接
	char* ret = (char*)malloc(sizeof(char)*(strlen(head)+strlen(name)+3));
	int i=0;
	int location = 0;
	for(i=0; head[i]!='\0'; i++)ret[location++]=head[i];
	ret[location++]='/';
	for(i=0; name[i]!='\0'; i++)ret[location++]=name[i];
	ret[location] = '\0';
	return ret;
}
 
void SearchDir(char* target, char* name){                                                  //寻找name目录下有没有带有targe文件名的文件
	DIR* dir = opendir(name);
        struct dirent* file;
        while((file = readdir(dir)) != NULL){
		if(file->d_name[0] == '.')continue;
		struct stat filebuf;
		char* nextname = joint(name, file->d_name);
		if(strstr(nextname, target) != NULL){
		        printf("%s\n", nextname);
		}
		lstat(nextname, &filebuf);
		if(S_ISDIR(filebuf.st_mode)){                                             //如果此文件是目录文件则进行递归
			SearchDir(target, nextname);
		}
        }
	closedir(dir);
 
}
 
int main(int argv,  char* argc[]){
	SearchDir(argc[1],argc[2]);
	return 0;
}
