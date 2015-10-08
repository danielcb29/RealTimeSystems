#include <iostream>
#include "barrera.h"
using namespace std;

void* interfaz_barrera(void *b){
    barrera_t* b_puntero = (barrera_t*)b;
    barrera(b_puntero);
}

void crear_hilos(barrera_t *b){
    pthread_t hilos[10];
    for(int i=0;i<10;i++){
        pthread_create(&hilos[i],NULL,interfaz_barrera,&b);
    }

    for(int j=0;j<10;j++){
        pthread_join(hilos[j], NULL);
    }
}

int main() {
    barrera_t estructura;
    crea(&estructura,10);
    crear_hilos(&estructura);
    destruye(&estructura);
    return 0;
}

