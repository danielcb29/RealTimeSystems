//
// Created by Daniel Correa on 7/10/15.
//

#include "barrera.h"
#include <stdio.h>
void crea(barrera_t *b, int N){
    //Inicializamos el mutex, la variable de condicion y la cantidad de hilos que van corriendo
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->nesimaebra,NULL);
    b->cantidadhilos = N;
}

void destruye(barrera_t *b){
    //Se destruye el mutex y la variable de condicion
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->nesimaebra);
    printf("El mutex y la variable de condiciona han sido desturidas \n");
}
void barrera (barrera_t *b){
    //Se verifica la barrera
    pthread_mutex_lock(&b->mutex);
        b->cantidadhilos--;
        if (b->cantidadhilos != 0){
            printf("Entrando a la barrera hilo %d \n",b->cantidadhilos);
            pthread_cond_wait(&b->nesimaebra,&b->mutex);
            printf("Saliendo de la barrera hilo \n");
        }else{
            pthread_cond_broadcast(&b->nesimaebra);

        }
    pthread_mutex_unlock(&b->mutex);
}
