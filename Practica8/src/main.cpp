#include <iostream>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "funciones_time.h"
using namespace std;

typedef void (*func)(void *);
typedef struct {
	struct timespec periodo;
	int timepo_eje;
	int prioridad;
	int id;
	struct timespec tcritico;

} marco_t;

int get_periodo(timespec p){
	int result = p.tv_sec * 1000 + p.tv_nsec/1000000;
	return result;
}

#define C_1MS 362700 /* Machine dependent */
#define DIM 100
void spin_m(void *p)
{
	int i,
	n = *((int *)p),
	limit = C_1MS * n;
	static int  a[DIM];
	for(i = 0; i < limit; i++)
	a[i%DIM] = i;
	return;
}

void* funcion_hebra(void* param){

	marco_t* i = (marco_t*)param;

	sched_param estructura_prioridades;
	int politica;
	pthread_getschedparam(pthread_self(),&politica,&estructura_prioridades);
	estructura_prioridades.__sched_priority = i->prioridad;

	pthread_setschedparam(pthread_self(),SCHED_FIFO,&estructura_prioridades);




	clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME ,&i->tcritico,NULL);


	struct timespec sig_time;
	ADD(&sig_time,&i->tcritico, &i->periodo);

	while(true){
		printf("Hilo de id: %i con prioridad: %i  inicia la accion periodica \n",i->id,i->prioridad);
		spin_m(&i->timepo_eje);
		printf("Hilo de id:%i  termina la accion periodica \n" ,i->id);
		clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME ,&sig_time,NULL);
		ACUM(&sig_time,&i->periodo);
	}


}


void* mostrar_tiempos(void* t_crit){
	timespec* tiempo_critico = (timespec*) t_crit;
	timespec const_time;
	const_time.tv_nsec = 10*1000000;
	const_time.tv_sec = 0;

	timespec sig_time;
	ADD(&sig_time, &const_time,tiempo_critico);


	clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME ,tiempo_critico,NULL);

	for(int i = 0; i<200; i++){
		printf ("******************************* %i ms ************************** \n",i*10);
		clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME ,&sig_time,NULL);
		ACUM(&sig_time,&const_time);

	}
}


int calcularR(marco_t* marco){
	int num_hebras = 3;
	int rant[num_hebras];
	int r[num_hebras];
	for(int n = 0;n<num_hebras;n++){
		rant[n] = marco[n].timepo_eje;
		r[n] = 0;
	}
	bool planificable = true;
	for(int i=0 ; i<num_hebras;i++){
		bool fin=false;
		while(!fin){
			int suma=0;
			for(int j=0;j<num_hebras;j++){
				if(marco[j].prioridad > marco[i].prioridad){
					float valor_w = 0;
					int periodo_j =  get_periodo(marco[j].periodo);
					valor_w = ceil(((float) rant[i] / periodo_j))*marco[j].timepo_eje;
					suma += valor_w;
				}
			}
			r[i] = suma + marco[i].timepo_eje;

			if (r[i] == rant[i] || r[i] > get_periodo(marco[i].periodo)){
				fin = true;
				if (r[i] > get_periodo(marco[i].periodo)){
					planificable = false;
				}
			}else{
				rant[i] = r[i];
				r[i] = 0;
			}
		}
		cout << "EL hilo de id: "<<marco[i].id << " tiene un tiempo de respuesta:" <<  r[i] << " ms y un plazo de" <<  get_periodo(marco[i].periodo) << " ms" << endl;
	}
	return planificable;
}

int main() {

	marco_t array_marco[3];
	struct timespec current_time;
	clock_gettime(CLOCK_REALTIME, &current_time);
	current_time.tv_sec += 1;
	array_marco[0].id = 1;
	array_marco[0].timepo_eje = 100;
	timespec tm1;
	tm1.tv_sec = 0;
	tm1.tv_nsec = 300*1000000;
	COPY(&array_marco[0].periodo,&tm1);
	array_marco[0].prioridad = 3;
	COPY(&array_marco[0].tcritico, &current_time);

	array_marco[1].id = 2;
	array_marco[1].timepo_eje = 120;
	timespec tm2;
	tm2.tv_sec = 0;
	tm2.tv_nsec = 400*1000000;
	COPY(&array_marco[1].periodo,&tm2);
	array_marco[1].prioridad = 2;
	COPY(&array_marco[1].tcritico, &current_time);

	array_marco[2].id = 3;
	array_marco[2].timepo_eje = 150;
	timespec tm3;
	tm3.tv_sec = 0;
	tm3.tv_nsec = 600*1000000;
	COPY(&array_marco[2].periodo,&tm3);
	array_marco[2].prioridad = 1;
	COPY(&array_marco[2].tcritico,&current_time);

	int result = calcularR(array_marco);
	cout << "Resultado planificacion: " << result << endl;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	sched_param estructura_prioridades;
	int valor_prioridad = sched_get_priority_max(SCHED_FIFO);
	estructura_prioridades.__sched_priority = valor_prioridad;
	pthread_attr_setschedparam(&attr, &estructura_prioridades);

	pthread_t hilo_showtime,hilo_marco1,hilo_marco2,hilo_marco3;
	pthread_create(&hilo_showtime,&attr,mostrar_tiempos,&current_time);
	pthread_create(&hilo_marco1,NULL,funcion_hebra,&array_marco[0]);
	pthread_create(&hilo_marco2,NULL,funcion_hebra,&array_marco[1]);
	pthread_create(&hilo_marco3,NULL,funcion_hebra,&array_marco[2]);
	pthread_join(hilo_showtime,NULL);


    return 0;
}
