#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main() {
	int fd[2];
	char a[100];
	int size=0;
	if(pipe2(fd, 04000) < 0){
		printf("Can't create pipe");
		exit(1);
	} else {
	while (write(fd[1], "a", 1) == 1)
		size++;
	printf("Size ofр pipe is:%d bytes.\n",size);
	}	

	return 0;
}
