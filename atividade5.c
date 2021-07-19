/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 1 */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS 2 //número de threads a serem executadas
#define SIZE 1000 // tamanho do array a ser processado

int myArray[SIZE];
int part = 0;

void *exp_array(void *arg) {
    int thread_part = part++; //identificador interno da thread

    for(int i = thread_part * (SIZE / 2 ); i < (thread_part + 1) * (SIZE / 2); i++) {
        myArray[i] = myArray[i] * myArray[i];
    }
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    
    //inicialização do vetor e print do vetor inicial
    for(int i = 0; i < SIZE; i++) {
        myArray[i] = rand() % 10;
        printf("%d ", myArray[i]);
    }

    for(thread = 0; thread < NTHREADS; thread++) {
        printf("--Cria a thread %d\n", thread);
        if (pthread_create(&tid_sistema[thread], NULL, exp_array, NULL)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }

    for (thread=0; thread<NTHREADS; thread++) {
        if (pthread_join(tid_sistema[thread], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    } 
    
    //print do vetor final
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", myArray[i]);
    }
    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}