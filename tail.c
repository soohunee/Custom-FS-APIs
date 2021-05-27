#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int offset, file;
	char file_path[1024]={'\0'};
	int n = atoi(argv[1]) * -1;
	strcpy(file_path, argv[2]);
	struct stat given_file;
	stat(file_path, &given_file);

	file = open(file_path, O_RDONLY);
	lseek(file, -1, SEEK_END);
	
	char buffer[given_file.st_size];
	while(n >0){
		read(file, buffer, 1);
		if(buffer[0] == '\n'){
			n -= 1;
		}
		offset = lseek(file, -2, SEEK_CUR);
		if(offset == -1){
			break;
		}
	}
	if (offset > 0 || n == 0){
		lseek(file, 2, SEEK_CUR);
	}
	else{
		lseek(file, 0, SEEK_SET);
	}
	memset(buffer, 0, given_file.st_size);
	read(file, buffer, given_file.st_size);
	printf("%s\n", buffer);
	close(file);
}
