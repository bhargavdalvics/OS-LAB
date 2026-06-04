#include<stdio.h>
#include<semaphore.h>
#define SIZE 3
int buffer[SIZE];
int in =0,out =0;
sem_t full,empty,mutex;
void produce(int item){
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[in]=item;
    in=(in+1)%SIZE;
    printf("%d produced",item);
    sem_post(&mutex);
    sem_post(&full);

}

void consume(){
    sem_wait(&full);
    sem_wait(&mutex);
    printf("%d consumed",buffer[out]);
    out=(out+1) %SIZE;
    sem_post(&mutex);
    sem_post(&empty);
}

int main(){
    sem_init(&empty,0,SIZE);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    produce(1);
    produce(2);
    produce(3);
}
