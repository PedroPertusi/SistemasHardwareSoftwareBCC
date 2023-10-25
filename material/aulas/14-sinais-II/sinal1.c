#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int contador = 0;

void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
    contador += 1;
    if (contador == 3) {
        struct sigaction h;

        h.sa_handler = SIG_DFL;
        h.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);
        
        kill(getpid(), SIGINT);
    }
}

int main() {
    /* TODO: registre a função sig_handler
     * como handler do sinal SIGINT
    */

    struct sigaction handler;
    handler.sa_handler = sig_handler;
    sigemptyset(&handler.sa_mask);
    handler.sa_flags = 0;

    sigaction(SIGINT, &handler, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
