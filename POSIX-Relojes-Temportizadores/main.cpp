#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
using namespace std;
void* wait_sigint(void* cont){
	printf("d");
	sigset_t set;
	int sig;
	int *counter = (int*) cont;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGRTMIN);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	for(int i=0;i<10;i++){
		if(sigwait(&set,&sig) != 0) pthread_exit((void*)-1);
			if(sig==SIGINT){
				if(*counter < 10){
					(*counter)++;
				}else{

					pthread_exit(0);
				}
			}
	}
	printf("Haz tecleado ctr+C 10 veces!");

}
void* count_wait_sigint(void* counter){
	int signum;
	sigset_t set;
	struct sigevent sig;
	timer_t timer;
	struct itimerspec required;
	struct timespec first,period;

	sig.sigev_notify = SIGEV_SIGNAL;
	sig.sigev_signo = SIGRTMIN;
	if (clock_gettime(CLOCK_REALTIME,&first));
	period.tv_sec =2;
	period.tv_nsec = 0;
	required.it_value = first;
	required.it_interval = period;
	int r_cr = 0;
	r_cr = timer_create(CLOCK_REALTIME,&sig,&timer);
	sigemptyset(&set);
	sigaddset(&set,SIGRTMIN);
	sigaddset(&set,SIGINT);
	int r_sr =0;
	r_sr = timer_settime(timer,TIMER_ABSTIME,&required,NULL);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	int *c = (int*) counter;
	while(1){
		if(sigwait(&set,&signum));
		printf("Numero de veces que a sido tecleado ctrl+c en los ultimos 2 segundos \n");
		cout << *c << endl;
	}



}
void* print_time(void*){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGRTMIN);
	pthread_sigmask(SIG_BLOCK,&set,NULL);

	struct timespec cur_time;
	clock_gettime(CLOCK_REALTIME, &cur_time);
	time_t segundos = cur_time.tv_sec;
	long nano_seg_actuales_rt = cur_time.tv_nsec;
	struct tm* estru;
	estru = localtime(&segundos);
	int segundos_actuales_rt = estru->tm_sec;
	int minutos_actuales_rt = estru->tm_min;
	int horas_actuales_rt = estru->tm_hour;
	int dias_actuales_rt = estru->tm_mday;
	printf("TIEMPO DE RELOG REALTIME \n");
	cout << "Nano segundos RT: " << nano_seg_actuales_rt << endl;
	cout << "Segundos RT: " << segundos_actuales_rt << endl;
	cout << "Minutos RT: " << minutos_actuales_rt << endl;
	cout << "Horas RT: " << horas_actuales_rt << endl;
	cout << "Dias RT: " << dias_actuales_rt << endl;

	struct timespec cur_time_mn;
	clock_gettime(CLOCK_MONOTONIC, &cur_time_mn);
	time_t segundos_mn = cur_time_mn.tv_sec;
	long nano_seg_actuales_mn = cur_time_mn.tv_nsec;
	struct tm* estru_mn;
	estru_mn = localtime(&segundos_mn);
	int segundos_actuales_mn = estru_mn->tm_sec;
	int minutos_actuales_mn = estru_mn->tm_min;
	int horas_actuales_mn = estru_mn->tm_hour;
	int dias_actuales_mn = estru_mn->tm_mday;
	printf("TIEMPO DE RELOG MONOTONIC \n");
	cout << "Nano segundos MN: " << nano_seg_actuales_mn << endl;
	cout << "Segundos MN: " << segundos_actuales_mn << endl;
	cout << "Minutos MN: " << minutos_actuales_mn << endl;
	cout << "Horas MN: " << horas_actuales_mn << endl;
	cout << "Dias MN: " << dias_actuales_mn << endl;

	struct timespec cur_time_th;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &cur_time_th);
	time_t segundos_th = cur_time_th.tv_sec;
	long nano_seg_actuales_th = cur_time_th.tv_nsec;
	struct tm* estru_th;
	estru_th = localtime(&segundos_th);
	int segundos_actuales_th = estru_th->tm_sec;
	int minutos_actuales_th = estru_th->tm_min;
	int horas_actuales_th = estru_th->tm_hour;
	int dias_actuales_th = estru_th->tm_mday;
	printf("TIEMPO DE RELOG THREAD_CPU_TIME_ID \n");
	cout << "Nano segundos TH: " << nano_seg_actuales_th << endl;
	cout << "Segundos TH: " << segundos_actuales_th << endl;
	cout << "Minutos TH: " << minutos_actuales_th << endl;
	cout << "Horas TH: " << horas_actuales_th << endl;
	cout << "Dias TH: " << dias_actuales_th << endl;

	for(int i=1;i<100000000;i++);
}
int main() {
	sigset_t set;
	pthread_t hilo_reloj,hilo_sigint,hilo_sigrt;
	int contador = 0;
	pthread_create(&hilo_reloj,NULL,print_time,NULL);
	pthread_create(&hilo_sigint,NULL,wait_sigint,&contador);
	pthread_create(&hilo_sigrt,NULL,count_wait_sigint,&contador);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGRTMIN);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	pthread_join(hilo_sigint, NULL);

    return 0;
}
