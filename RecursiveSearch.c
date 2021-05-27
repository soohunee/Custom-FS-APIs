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

#define USER_PATH "/home"
bool exit_flag = false;

int find_file(char file_path[], char file_name[])
{
	DIR *dir;
	struct dirent *dir_entry;
	struct stat given_path;
	dir = opendir(file_path);
	char tmp[1024] = {'\0'};
	while((dir_entry = readdir(dir)) != NULL)
	{
		strcpy(tmp, file_path);
		if ((strcmp(dir_entry->d_name, ".")==0) || (strcmp(dir_entry->d_name, "..") == 0)){
			continue;
		}
		printf("%s\n", dir_entry->d_name);
		strcat(tmp, "/");
		strcat(tmp, dir_entry->d_name);

		if(strcmp(dir_entry->d_name, file_name) == 0)
		{
			printf("found it : %s\n", tmp);
			exit_flag = true;
			exit(1);
		}
		stat(tmp, &given_path);
		if (S_ISDIR(given_path.st_mode))
		{
			find_file(tmp, file_name);
		}
	}
	closedir(dir);
	return 1;
}



int find(char file_path[])
{
	DIR *dir;
	struct dirent *dir_entry;
	struct stat given_path;
	dir = opendir(file_path);
	char tmp[1024] = {'\0'};
	while((dir_entry = readdir(dir)) != NULL)
	{
		strcpy(tmp, file_path);
		if ((strcmp(dir_entry->d_name, ".")==0) || (strcmp(dir_entry->d_name, "..") == 0)){
			continue;
		}
		printf("%s\n", dir_entry->d_name);
		strcat(tmp, dir_entry->d_name);
		stat(tmp, &given_path);
		if (S_ISDIR(given_path.st_mode))
		{
			find(tmp);
		}
	}
	closedir(dir);
	return 1;
}

int main(int argv, char* args[]){
	
	char file_path[1024] = "";
	char temp[1024] = "";
	char arg_path[1024] = "";
	bool find_flag = false;

	if(argv == 1){
		strcat(file_path,"./");
		find(file_path);
	}
	else if(argv == 2){
		strcat(arg_path, args[1]);
		int l = strlen(arg_path);
		if (arg_path[l-1] == '/'){

			strcat(file_path, "./");
			strcat(file_path, arg_path);
		}
		else{

			strcat(file_path, "./");
			strcat(file_path,arg_path);
			strcat(file_path, "/");
		}
		find(file_path);
	}
	else{
		strcat(file_path, USER_PATH);
		char file_name[1024] = "";
		if(strcmp(args[1], "-f") == 0){
			strcat(file_name,args[2]);
		}
		else{
			strcat(file_name, args[1]);
		}
		find_file(file_path,file_name);
		if(exit_flag == false)
		{
			printf("Cannot find the file!\n");
		}

	}
}	

