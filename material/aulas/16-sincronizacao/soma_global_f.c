#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    double resultado;
};

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        spa->resultado += spa->vetor[i];
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

    pthread_t tids[4];
    struct soma_parcial_args args[4];

    
    for (int i = 0; i < 4; i++) {
        args[i].vetor = vetor;
        args[i].start = i * n / 4;
        args[i].end = (i + 1) * n / 4;
        args[i].resultado = 0;
        pthread_create(&tids[i], NULL, soma_parcial, &args[i]);
    }

    double soma_f = 0;
    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
        soma_f += args[i].resultado;
    }

    printf("Paralela: %lf\n", soma_f);
    free(vetor);

    return 0;
}

// gcc -pthread -o soma_global_f soma_global_f.c
