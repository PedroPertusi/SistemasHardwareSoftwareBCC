#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo1, semaforo2;

void *thread1(void *arg){
    printf("Thread 1 antes do ponto de encontro\n");
    sem_post(&semaforo2); // Libera a segunda thread
    sem_wait(&semaforo1); // Aguarda a segunda thread
    printf("Thread 1 depois do ponto de encontro\n");
    pthread_exit(NULL);
}

void *thread2(void *arg){
    printf("Thread 2 antes do ponto de encontro\n");
    sem_post(&semaforo1); // Libera a primeira thread
    sem_wait(&semaforo2); // Aguarda a primeira thread
    printf("Thread 2 depois do ponto de encontro\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t t1, t2;
    sem_init(&semaforo1, 0, 0);
    sem_init(&semaforo2, 0, 0);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&semaforo1);
    sem_destroy(&semaforo2);
    return 0;
}
