/* POSIX headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Standard C */
#include <stdio.h>
#include <stdlib.h>


long getFileSize(char *filename) {
    FILE *file = fopen(filename, "r");

    long size;
    // Save the current position
    long currentPosition = ftell(file);

    // Move to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the current position, which is the file size
    size = ftell(file);

    // Restore the position
    fseek(file, currentPosition, SEEK_SET);

    fclose(file);
    return size;
}

// Modifique o copy_file para usar um buffer de 100 caracteres. 
// Meça o tempo de execução para a cópia de um arquivo grande (~100Mb) usando o comando time. 
// Não se esqueça de verificar que os resultados ficaram iguais com o comando diff.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Erro não recebi 2 argumentos\n");
        return 0;
    }
    long size_arq1 = getFileSize(argv[1]);
    char buf[size_arq1];

    int fd_source = open(argv[1], O_RDONLY);
    int fd_dest = open(argv[2], O_WRONLY | O_CREAT, 0700); 

    for (long i = 0; i < size_arq1; i++) {  
        read(fd_source, &buf[i], 1);
    }

    write(fd_dest, buf, size_arq1);

    close(fd_source);
    close(fd_dest);

    return 0;
}
