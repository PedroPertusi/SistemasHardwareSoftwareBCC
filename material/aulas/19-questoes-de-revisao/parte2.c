#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// linha de compilação:

typedef struct {
    sem_t *s1, *s2;
} t_arg;

/* declarar tarefas aqui e lançar no main */
/* cada bloco na figura deverá ser representado por um print com sua letra */

void *t1(void *arg) {
    t_arg *arg_ = arg;
    printf("A\n");

    sem_wait(arg_->s1);

    printf("C\n");
    for (int i = 0; i < 3; i++) {
        sem_post(arg_->s2);
    }
    return NULL;
}

void *t2(void *arg) {
    t_arg *arg_ = arg;
    printf("B\n");

    sem_wait(arg_->s1);
    sem_wait(arg_->s2);

    printf("D\n");

    for (int i = 0; i < 3; i++) {
        sem_post(arg_->s2);
    }
    return NULL;
}

void *t3(void *arg) {
    t_arg *arg_ = arg;
    printf("E\n");

    sem_post(arg_->s1);
    sem_wait(arg_->s2);

    printf("F\n");
    return NULL;
}

void *t4(void *arg) {
    t_arg *arg_ = arg;
    printf("G\n");

    sem_post(arg_->s1);
    sem_wait(arg_->s2);

    printf("H\n");
    return NULL;
}


int main() {
    pthread_t* tids = malloc(4 * sizeof(pthread_t));

    t_arg *arg = malloc(sizeof(t_arg));

    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);

    arg->s1 = s1;
    arg->s2 = s2;

    pthread_create(&tids[0], NULL, t1, arg);
    pthread_create(&tids[1], NULL, t2, arg);
    pthread_create(&tids[2], NULL, t3, arg);
    pthread_create(&tids[3], NULL, t4, arg);

    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);
    pthread_join(tids[3], NULL);

    sem_destroy(s1);
    sem_destroy(s2);

    free(tids);
    free(s1);
    free(s2);
    free(arg);

    return 0;
}

// gcc para compilar
// gcc -pthread -o parte2 parte2.c