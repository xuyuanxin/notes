#include <pthread.h>
/*
All three return: 0 if OK, positive Exxx value on error
*/
int pthread_mutex_lock(pthread_mutex_t *mptr) ;
int pthread_mutex_trylock(pthread_mutex_t *mptr) ;
int pthread_mutex_unlock(pthread_mutet *mptr) ;
