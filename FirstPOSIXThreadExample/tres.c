//
// Created by Daniel Correa on 5/10/15.
//

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
dos(int *n) {
    for (;;)
        printf("%d", *n);
}
tres() {
    int i;
    for (i=0; i < 15000;i++)
        printf("3");
}
main()
{
    pthread_t dosId, tresId;
    int i, param_dos = 2, param_tres = 3;
    pthread_create(&dosId, NULL, (void *)dos, &param_dos);
    pthread_create(&tresId, NULL, (void *)tres, NULL);
    for (i =0; i<10000; i++)
    printf("1");
    pthread_kill(dosId, SIGKILL);
    pthread_join(tresId, NULL);
}