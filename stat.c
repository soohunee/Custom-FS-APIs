#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("no given file\n");
		exit(1);
	}
	// argv[1] = given file/directory path
	struct stat given_path;

	if (stat(argv[1], &given_path) == -1){
		printf("stat error\n");
		exit(1);
	}
	printf("ID of device containing file : %ld\n", given_path.st_dev);
	printf("inode's number : %ld\n", (long)given_path.st_ino);
	printf("Mode of file : %lo (ocatl)\n", (unsigned long)given_path.st_mode);
	printf("Number of links to the file : %ld\n", (long)given_path.st_nlink);
	printf("User ID of the owner of the file : %ld\n", (long)given_path.st_uid);
	printf("Group ID of the owner of the file : %ld\n", (long)given_path.st_gid);
	printf("Device ID : %ld\n", given_path.st_rdev);
	printf("File size in bytes : %lld\n", (long long)given_path.st_size);
	printf("Time of last access : %s", ctime(&given_path.st_atime));
	printf("Time of last data modification : %s", ctime(&given_path.st_mtime));
	printf("Time of last file status change : %s", ctime(&given_path.st_ctime));
	printf("Block size : %ld\n", (long)given_path.st_blksize);
	printf("# of blocks allocated for this object : %lld\n", (long long)given_path.st_blocks);
}
