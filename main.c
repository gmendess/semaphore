#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "semaphore.h"

typedef struct stack {
  pthread_mutex_t mutex;
  int size;
  int array[5];
} Stack;

Stack stack;

semaphore_t sema;

// função a ser executada pela thread produtora. Ela adicionará números aleatórios numa stack de tamanho 5
void* producer(void* args) {
  int x = 0;

  // ocorrerão 2 inserções na stack
  while(x < 20) {
    pthread_mutex_lock(&stack.mutex); // lock para manipular a stack

    // se a stack não estiver lotada, posso gerar um valor e inserir nela
    if(stack.size < 5) {
      int rand_value = rand() % 100 + 1; // gera número entre 1 e 100
      printf("produced: %d\n", rand_value);
      stack.array[stack.size++] = rand_value; // insere valor na stack e incrementa o tamanho
      pthread_mutex_unlock(&stack.mutex); // unlock, pois não irei manipular a stack daqui pra baixo 

      x++; // incrementa x, indicando que +1 de 20 valores foram inseridos
      semaphore_post(&sema); // sinaliza que um valor foi gerado (incrementa o contador do semáforo)
    }
    else { // stack cheia, apenas dou unlock
      pthread_mutex_unlock(&stack.mutex);
    }
  }

  return NULL;
}

void* consumer(void* args) {

  for(int x = 0; x < 20; x++) {
    semaphore_wait(&sema); // espera por um sinal, se o contador for maior que zero, retorna imediatamente
    pthread_mutex_lock(&stack.mutex); // lock para manipular a stack
    printf("  consumed: %d\n", stack.array[--stack.size]); // lê o conteúdo do topo e decrementa o tamanho
    pthread_mutex_unlock(&stack.mutex);
  }
  return NULL;
}

int main() {

  // inicializa o semáforo (contador, mutex e variável condicional internas)
  semaphore_init(&sema);

  // cria a thread produtora e consumidora
  pthread_t a, b;
  pthread_create(&a, NULL, producer, NULL);
  pthread_create(&b, NULL, consumer, NULL);

  // espera pela finalização das threads
  pthread_join(a, NULL);
  pthread_join(b, NULL);

  return 0;
}