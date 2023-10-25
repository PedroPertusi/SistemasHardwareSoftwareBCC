#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *minha_thread(void *arg) {
    sleep(1);
    printf("Hello thread!\n");
    return NULL;
}

void *minha_thread2(void *arg) {
    sleep(1);
    printf("Hello thread1!\n");
    return NULL;
}

void *minha_thread3(void *arg) {
    sleep(1);
    printf("Hello thread2!\n");
    return NULL;
}

void *minha_thread4(void *arg) {
    sleep(1);
    printf("Hello thread3!\n");
    return NULL;
}


int main() {
    pthread_t tid;
    
    int error = pthread_create(&tid, NULL, minha_thread, NULL);

    pthread_t tid2;

    int error2 = pthread_create(&tid2, NULL, minha_thread2, NULL);

    pthread_t tid3;

    int error3 = pthread_create(&tid3, NULL, minha_thread3, NULL);

    pthread_t tid4;

    int error4 = pthread_create(&tid4, NULL, minha_thread4, NULL);

    sleep(3);
    printf("Hello main\n");

    return 0;
}
