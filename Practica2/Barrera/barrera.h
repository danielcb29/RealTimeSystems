//
// Created by Daniel Correa on 7/10/15.
//

#ifndef PRACTICA2_BARRERA_H
#define PRACTICA2_BARRERA_H
#include "pthread.h"

typedef struct {
    int cantidadhilos;
    pthread_mutex_t mutex;
    pthread_cond_t nesimaebra;
} barrera_t;
void crea(barrera_t *b, int N);
void destruye(barrera_t *b);
void barrera (barrera_t *b);

#endif //PRACTICA2_BARRERA_H
