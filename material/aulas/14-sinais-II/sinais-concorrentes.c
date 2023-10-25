#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int status = 0;

void operacao_lenta() {
    sleep(10);
}


void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    operacao_lenta();
    printf("SIGINT: Vou usar status agora! status=%d\n", status);
}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    operacao_lenta();
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {

    struct sigaction handler;
    handler.sa_handler = sigint_handler;
    sigemptyset(&handler.sa_mask);
    sigaddset(&handler.sa_mask, SIGTERM);
    handler.sa_flags = 0;

    sigaction(SIGINT, &handler, NULL);

    struct sigaction h;
    h.sa_handler = sigterm_handler;
    sigemptyset(&h.sa_mask);
    sigaddset(&h.sa_mask, SIGINT);
    h.sa_flags = 0;

    sigaction(SIGTERM, &h, NULL);


    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
