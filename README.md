# Semaphore

Implementando um semáforo para estabelecer comunicação entre uma thread produtora e consumidora. Para isso, foi usado `pthread_mutex_t` e `pthread_cond_t` da biblioteca `pthread`. A ideia é bem simples e acredito que lendo os comentários dê para ter noção de como funciona.

## Algumas referências

- [Conceito desse semáforo](http://faculty.cs.niu.edu/~hutchins/csci480/semaphor.htm)
- [pthread_cond_t](https://www.man7.org/linux/man-pages/man3/pthread_cond_init.3p.html)
- [pthread_mutex_t](https://www.man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html)