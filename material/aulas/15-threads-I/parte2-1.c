#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct dois_numeros {
    int n1;
    int n2;
    int resultado;
};

void *minha_thread(void *arg) {
    struct dois_numeros *i = (struct dois_numeros *) arg;
    printf("Hello thread! n1: %d, n2: %d\n", i->n1, i->n2);
    i->resultado = i->n1 + i->n2;

    return NULL;
}

//receber dois numeros
int main() {
    pthread_t tid[4];
    struct dois_numeros *numeros = malloc(sizeof(struct dois_numeros));
    scanf("%d %d", &numeros->n1, &numeros->n2);

    for (int i = 0; i < 4; i++) {
        pthread_create(&tid[i], NULL, minha_thread, numeros);
    }
    
    
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("Resultado: %d\n", numeros->resultado);
    
    return 0;
}
