#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <pthread.h>

struct semaphore {
  int counter; // indica a quantidade de sinais enviados ao semáforo
  pthread_mutex_t mutex; // mutex para evitar race-condition no membro 'counter'
  pthread_cond_t  cond; // variável condicional da biblioteca pthread, ela espera por um sinal caso counter seja 0
};
typedef struct semaphore semaphore_t;

int semaphore_init(semaphore_t* s);
void semaphore_wait(semaphore_t* s);
void semaphore_post(semaphore_t* s);
void semaphore_destroy(semaphore_t* s);

#endif // _SEMAPHORE_H