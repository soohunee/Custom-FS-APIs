#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argv, char* args[]){
	DIR *dir;
	struct dirent *dir_entry;
	bool stat_flag = false;
	struct stat given_path;
	char file_path[1024] = "";
	if (argv == 1){
		dir = opendir(".");
		strcat(file_path, ".");
	}
	else if (argv == 2){
		if (strcmp(args[1], "-l") != 0){
			dir = opendir(args[1]);
			strcat(file_path, args[1]);
		}
		else{
			dir = opendir(".");
			strcat(file_path, ".");
			stat_flag = true;
		}
	}
	else if(argv == 3){
		stat_flag = true;
		if (strcmp(args[1], "-l") == 0){
			dir = opendir(args[2]);
			strcat(file_path, args[2]);
		}
		else{
			dir = opendir(args[1]);
			strcat(file_path, args[1]);
		}
	}
	if(dir == NULL){
		printf("directory open error\n");
		exit(1);
	}
	else{
		int l = strlen(file_path);
		if(file_path[l-1] != '/'){
			strcat(file_path, "/");
		}
		char temp[1024]={'\0'};
		

		while((dir_entry = readdir(dir)) != NULL){
			strcpy(temp, file_path);

			if(stat_flag == true){
				printf("%s ", dir_entry->d_name);
				strcat(temp, dir_entry->d_name);

				stat(temp, &given_path);

				if(S_ISDIR(given_path.st_mode)) printf("d"); else printf("-");
				if(given_path.st_mode & S_IRUSR) printf("r"); else printf("-");
				if(given_path.st_mode & S_IWUSR) printf("w"); else printf("-");
				if(given_path.st_mode & S_IXUSR) printf("x"); else printf("-");
				if(given_path.st_mode & S_IRGRP) printf("r"); else printf("-");
				if(given_path.st_mode & S_IWGRP) printf("w"); else printf("-");
				if(given_path.st_mode & S_IXGRP) printf("x"); else printf("-");
				if(given_path.st_mode & S_IROTH) printf("r"); else printf("-");
				if(given_path.st_mode & S_IWOTH) printf("w"); else printf("-");
				if(given_path.st_mode & S_IXOTH) printf("x"); else printf("-");
				printf(" ");
				printf(" UID:%ld", (long)given_path.st_uid);
				printf(" GID:%ld ", (long)given_path.st_gid);
				printf("%s", ctime(&given_path.st_atime));
			}
			else{
				printf("%s\n", dir_entry->d_name);
			}
		}
	}
	closedir(dir);
}	

