int main()
{
    int fd, result;
    size_t size;
    char resstring[14];
    char name[] = "filee.fifo";
    (void)umask(0);
    
    printf("Reading data from FIFO\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }
    
    size = read(fd, resstring, 14);
    printf("File was read\n");
    
    if (size < 0) {
        printf("Can\'t read string\n");
        exit(-1);
    }

    printf("Read from FIFO: %s\n", resstring);
    close(fd);
    printf("Reader closed\n");
    return 0;
}
