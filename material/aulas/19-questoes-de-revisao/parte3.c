/* POSIX headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Standard C */
#include <stdio.h>
#include <stdlib.h>

char *proxima_linha(int fd) {
    char buf[1];

    int fd_dest = open("help.txt", O_WRONLY | O_CREAT, 0700); 
    int i = 0;

    while(read(fd, &buf[0], 1) > 0) {
        if (buf[0] == '\n') {
            break;
        }
        write(fd_dest, buf, 1);
        i++;
    }

    if (i == 0) {
        return NULL;
    }

    char *linha = malloc(i + 1);
    close(fd_dest);
    fd_dest = open("help.txt", O_RDONLY);

    read(fd_dest, linha, i);
    linha[i] = '\0';

    close(fd_dest);
    unlink("help.txt");

    return linha;
}


int main(int argc, char *argv[]) {
    // Faça agora uma função main que usa sua função acima para ler todas as linhas de um arquivo passado como argumento de linha de comando e mostrar somente as que iniciam com uma letra maiúscula. Você não precisa fazer a rubrica "completa" para fazer este item.

    if (argc != 2) {
        printf("Erro não recebi 1 argumento\n");
        return 0;
    }

    int fd = open(argv[1], O_RDONLY);

    char *linha = proxima_linha(fd);

    while (linha != NULL) {
        if (linha[0] >= 'A' && linha[0] <= 'Z') {
            printf("%s\n", linha);
        }
        else {
            printf("Linha não começa com letra maiúscula\n");
        }
        linha = proxima_linha(fd);
    }

    return 0;
}

//gcc para compilar
//gcc -Wall -Wextra -Werror -pedantic -std=c99 -o parte3 parte3.c