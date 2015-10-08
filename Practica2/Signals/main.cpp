#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
using namespace std;
void* wait_sigint(void*){
	sigset_t set;
	int sig;
	int counter = 0;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	for(int i=0;i<10;i++){
		if(sigwait(&set,&sig) != 0) pthread_exit((void*)-1);
			if(sig==SIGINT){
				if(counter < 10){
					counter++;
				}else{

					pthread_exit(0);
				}
			}
	}
	printf("Haz tecleado ctr+C 10 veces!");

}

int main() {
	sigset_t set;
	pthread_t hilo;
	pthread_create(&hilo,NULL,wait_sigint,NULL);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	pthread_join(hilo, NULL);

    return 0;
}
