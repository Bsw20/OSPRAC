#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
int main(){
	// Указатель на разделяемую память
	int *ptr;
	int md, fd, flag;
	key_t key;
	// Генерируем ключ(при ошибке выходим)
	if((key = ftok("lab7Task1.c", 0)) < 0){
		printf("Error of generate key\n");
		exit(-1);
	}
	// Пытаемся создать область разделяемой памяти размером 9000*int(по факту рандомное число, относительно большое, чтобы влез весь текст)(при ошибке выходим). 
	if((md = shmget(key, 9000*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
		// Случай, когда не создалась область.
		if(errno != EEXIST){
			printf("Error of create shared memory\n");
			exit(-1);
		} else {
		// Случай, когда не удалось найти эту область
			if((md = shmget(key, 9000*sizeof(int), 0)) < 0){
				printf("Error of find shared memory\n");
				exit(-1);
			}
		}
	}
	// Пытаемся отобразить разделяемую память. 
	if((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
		printf("Error attach shared memory\n");
		exit(-1);
	}
	int i;
	i = 0;
	fd = open ("./lab7Task1.c", O_RDONLY);
	while ((flag = read (fd, &ptr[i], 1)) > 0){
		i++;
	}
	ptr[i+1]=EOF;
	if (flag < 0){
		printf ("Can not read file\n");
		exit (1);
	}
	// Удаляем разделяемую память.
	if(shmdt(ptr) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}
	printf("\nWriting doneeee\n\n");
	return 0;
}


