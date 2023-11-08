#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    sem_t *s1, *s2;
    queue_t *q;
} t_arg;

typedef struct {
    /* Tamanho máximo da fila*/
    int n;
    /* Tamanho atual da fila */
    int sz;
    /* Primeiro elemento da fila */
    int front;
    /*Dados */
    int *data;
} queue_t;

queue_t *queue_create(int n) {
    queue_t *new_queue = malloc(sizeof(queue_t));

    if (new_queue == NULL) {
        return NULL;
    }

    new_queue->n = n;
    new_queue->front = 0;
    new_queue->sz = 0;
    new_queue->data = malloc( n * sizeof(int));

    if (new_queue->data == NULL) {
        free(new_queue);
        return NULL;
    }

    return new_queue;
}

void queue_destroy(queue_t **q) {
    free((*q)->data);
    (*q)->data = NULL;
    free(*q);
    *q = NULL;
}

int queue_size(queue_t *q) {
    return q->sz;
}

int queue_dequeue(queue_t *q) {
    if (q->sz == 0) {
        return -1;
    }

    int val = q->data[q->front];
    
    q->sz--;
    q->front = q->sz != 0 ? (q->front + 1) % q->n : 0;
    
    return val;
}

void queue_enqueue(queue_t *q, int val) {
    if (q->sz == q->n) {
        return;
    }
    
    q->data[(q->front + q->sz) % q->n] = val;
    q->sz++;
}

void *produtora(void *arg_) {
    t_arg *arg = arg_;

    while (1) {
        int valor = rand() % 100 + 1; // Números aleatórios de 1 a 100
        queue_enqueue(arg->q, valor);

        sem_post(arg->s1);
        
        sem_wait(arg->s2);
    }

    return NULL;
}

void *consumidora(void *arg_) {
    t_arg *arg = arg_;

    while (1) {
        sem_wait(arg->s1);

        sleep(rand() % 5 + 1); // Aguarde por um período aleatório de 1 a 5 segundos

        int valor = queue_dequeue(arg->q);
        printf("%d\n", valor);

        sem_post(arg->s2);
    }

    return NULL;
}

int main() {
    pthread_t *tid = malloc(sizeof(pthread_t) * 2);

    t_arg *arg = malloc(sizeof(t_arg));

    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);

    arg->s1 = s1;
    arg->s2 = s2;

    queue_t *q = queue_create(10);

    arg->q = q;

    pthread_create(&tid[0], NULL, produtora, arg);
    pthread_create(&tid[1], NULL, consumidora, arg);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sem_destroy(s1);
    sem_destroy(s2);

    free(tid);
    free(s1);
    free(s2);
    free(arg);
    queue_destroy(&q);

    return 0;
}
