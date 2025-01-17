#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    pthread_mutex_t *mutex;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        //lock
        pthread_mutex_lock(spa->mutex);
        soma += spa->vetor[i];
        //unlock
        pthread_mutex_unlock(spa->mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t tids[4];
    struct soma_parcial_args args[4];

    
    for (int i = 0; i < 4; i++) {
        args[i].vetor = vetor;
        args[i].start = i * n / 4;
        args[i].end = (i + 1) * n / 4;
        args[i].mutex = &mutex;
        pthread_create(&tids[i], NULL, soma_parcial, &args[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("Paralela: %lf\n", soma);

    // soma = 0;
    // struct soma_parcial_args *aa = malloc(sizeof(struct soma_parcial_args));
    // aa->vetor = vetor;
    // aa->start = 0;
    // aa->end = n;
    // aa->mutex = &mutex;
    // soma_parcial(aa);

    // printf("Sequencial: %lf\n", soma);

    free(vetor);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// gcc -pthread -o soma_global soma_global.c
