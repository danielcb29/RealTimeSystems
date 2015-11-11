#include <iostream>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include "funciones_time.h"
using namespace std;

typedef void (*func)(void *);
typedef struct {
	struct timespec periodo;
	int timepo_eje;
} info_time;

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

int execTime(func f, void* param, timespec *time){
	struct timespec first_time,end_time;
	clock_gettime(CLOCK_REALTIME, &first_time);
	f(param);
	clock_gettime(CLOCK_REALTIME, &end_time);
	MINUS(time,&end_time,&first_time);

}

void* funcion_hebra(void* param){
	info_time* i = (info_time*)param;
	struct timespec first_time,sig_time;
	clock_gettime(CLOCK_REALTIME, &first_time);
	timespec t = i->periodo;
	ADD(&sig_time,&first_time,&t);

	int c = i->timepo_eje;

	struct sched_param param_priority;
	int polity;
	pthread_getschedparam(pthread_self(), &polity,  &param_priority);

	while(true){
		printf("Ejecutando tarea con prioridad: %i \n",param_priority.__sched_priority);
		spin_m(&c);
		clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME ,&sig_time,NULL);
		ACUM(&sig_time,&t);
	}


}

int main() {
	int param = 1000;
	struct timespec time;
	execTime(spin_m,&param,&time);
	PRINT(&time);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	sched_param estructura_prioridades;
	int valor_prioridad = sched_get_priority_max(SCHED_FIFO);
	estructura_prioridades.__sched_priority = valor_prioridad;
	pthread_attr_setschedparam(&attr, &estructura_prioridades);

	info_time i;
	i.timepo_eje=120;
	struct timespec periodo_time;
	periodo_time.tv_sec = 0;
	periodo_time.tv_nsec = 500000000;
	i.periodo = periodo_time;
	pthread_t hilo_time;
	pthread_create(&hilo_time,&attr,funcion_hebra,&i);
	pthread_join(hilo_time,NULL);



    return 0;
}
