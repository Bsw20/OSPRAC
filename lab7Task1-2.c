#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int *ptr;
	int md, flag;
	key_t key;
	int fd;
	// Пытаемся сгенерировать ключ, выходим с ошибкой, если не удалось.
	if((key = ftok("lab7Task1.c", 0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}
	// Случай, когда не удалось найти область разделяемой памяти.
	if((md = shmget(key, 9000*sizeof(int), 0)) < 0){
		printf("Can\'t find shared memory\n");
		exit(-1);
	}
	// Попытка отобразить разделяемую память в пространство процесса. 
	if((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	int i;
	i = 0;
	// Выводим текст программы.
	printf("lab7Task1.c\n");
	while (ptr[i] != EOF ){
		putchar(ptr[i]);
		++i;
	}
	// Освобождаем разделяемую память.
	if(shmctl(md, IPC_RMID, NULL) < 0){
		printf("Can't free shared memory\n");
		exit(-1);
	}
	printf("\nAll shared memory is free. Printing done.\n\n");
	return 0;
}

