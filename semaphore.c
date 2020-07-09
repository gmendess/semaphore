#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"

int semaphore_init(semaphore_t* s, int counter) {
  int status;

  s->counter = counter;

  // inicia a mutex e verifica por erro
  status = pthread_mutex_init(&s->mutex, NULL);
  if(status != 0)
    return status;

  // inicia a variável condicional e verifica por erros
  status = pthread_cond_init(&s->cond, NULL);
  if(status != 0)
    return status;

  return 0; // ok
}

void semaphore_wait(semaphore_t* s) {
  pthread_mutex_lock(&s->mutex); // lock para manipular s->counter

  // verifica se o contador do semáforo é zero, se for, significa que nenhum sinal foi enviado até então,
  // dessa forma, o semáforo espera até que um sinal seja recebido (pthread_cond_wait)
  if(s->counter == 0)
    pthread_cond_wait(&s->cond, &s->mutex);

  s->counter--; // após o sinal ser recebido, decrementa counter, significando que a sinal foi tratado
  pthread_mutex_unlock(&s->mutex);
}

void semaphore_post(semaphore_t* s) {
  pthread_mutex_lock(&s->mutex); // lock para manipular s->counter
  s->counter++; // incrementa o contador do semáforo, significando que há 'counter + 1' sinais enviados e prontos para serem tratados
  pthread_mutex_unlock(&s->mutex);
  pthread_cond_signal(&s->cond); // envia o sinal para algum semáforo em espera, se ninguém estiver esperando, não tem problema
}

// destrói corretamente a mutex e a variável condicional
void semaphore_destroy(semaphore_t* s) {
  pthread_mutex_destroy(&s->mutex);
  pthread_cond_destroy(&s->cond);
}