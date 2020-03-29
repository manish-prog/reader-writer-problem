#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t mutex, wrt;
int shareVariable, count = 0;


void *reader(void *value){
        pthread_mutex_lock(&mutex);
        count++;
        if(count==1){
                pthread_mutex_lock(&wrt);
        }
        pthread_mutex_unlock(&mutex);
        int n = rand() % 10;
        int d = (int)value;
        printf("r%d waiting for random time b/w 0 to 10 = %d\n", d, n);
        sleep(n);
        printf("enter the no of time r%d want to read:\n", d);
        int i;
        scanf("%d", &i);
        printf(" r%d \n", d);
        int j;
        for(j=0; j<i; j++){
                printf("R%d read the shared value = %d\n", d, shareVariable);
        }
        printf("no of reader = %d\n", count);
        pthread_mutex_lock(&mutex);
        count--;
        if(count==0){
                pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex);
}
void *writer(void *value){
        pthread_mutex_lock(&wrt);
        int n = rand() % 10;
        int d = (int)value;
        printf("w%d waiting for random time b/w 0 to 10 = %d\n", d, n);
        sleep(n);
        printf("enter the time w%d want to write:\n", d);
        int i;
        scanf("%d", &i);
        printf(" w%d \n", d);
        int j;
        for(j=0; j<i; j++){
                printf("enter the %dth integer value you want to write:\n", (j+1));
                int u;
                scanf("%d", &u);
                shareVariable+= u;
        }
        printf("updating value of shared variables = %d \n", shareVariable);
        pthread_mutex_unlock(&wrt);
}

void main(){
        printf("enter the initial value of shared variables \n");
        scanf("%d", &shareVariable);
        int read=5;
        int write=5;
	 int i;
        pthread_t r[read], w[write];
        pthread_mutex_init(&wrt, NULL);
        pthread_mutex_init(&mutex, NULL);
        if(write==read){
                for(i=0; i<write; i++){
                        pthread_create(&w[i], NULL, &reader, (int *)i);
                        pthread_create(&r[i], NULL, &writer, (int *)i);
                }
                for(i=0; i<write; i++){
                        pthread_join(w[i], NULL);
                        pthread_join(r[i], NULL);
                }
        }
        
        printf("After joining the thread final value of share variable = %d\n", shareVariable);
}


