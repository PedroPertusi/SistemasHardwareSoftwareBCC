#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *tarefa_print_i(void *arg) {
    int *i = (int *) arg;
    printf("%d\n", *i);
    return NULL;
}

int main() {

    int* v = malloc(4 * sizeof(int));
    pthread_t* tids = malloc(4 * sizeof(pthread_t));

    for (int i = 0; i < 4; i++) {
        v[i] = i;
        pthread_create(&tids[i], NULL, tarefa_print_i, &v[i]);
        pthread_join(tids[i], NULL);
    }

    return 0;
}
