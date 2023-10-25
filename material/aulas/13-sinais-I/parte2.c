#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Filho: %d\n", getpid());
        while(1);
    }
    else {
        int wstatus;
        int x = wait(&wstatus);
        printf("Filho %d terminou\n", x);

        printf("EXITED %d\n", WIFEXITED(wstatus));
        printf("SIGNALED %d\n", WIFSIGNALED(wstatus));
        printf("TERMSIG %d\n", WTERMSIG(wstatus));
        printf("ERROR %s\n", strsignal(WTERMSIG(wstatus)));
    }

    return 0;
}