#include<stdio.h>
#include<semaphore.h>

#define N 5
#define thinking 0
#define hungry 1
#define eating 2

sem_t S[N],mutex;   //S[i] → private semaphore for philosopher i
int state[N];       //Stores current state of each philosopher

int left(int i){
    return (i+N-1)%N;   
}
int right(int i){
    return (i+1)%N;
}
void test(int i){
    //Checks whether philosopher i can start eating.
    if(state[i]==hungry&& state[left(i)]!=eating&&state[right(i)]!=eating){
        state[i]=eating;
        sem_post(&S[i]);
    }
}

void take_fork(int i){
    sem_wait(&mutex);
    state[i]=hungry;
    printf("Philosopher %d is hungry\n",i);
    test(i);
    sem_post(&mutex); //unlock
    sem_wait(&S[i]); //If forks unavailable, philosopher blocks here.
}

void put_fork(int i){
    sem_wait(&mutex);
    state[i]=thinking;
    printf("philosopher %d is thinking\n",i);
    test(left(i));
    test(right(i));
    sem_post(&mutex);
}

void philosopher(int i){
    printf("philosopher %d is thinking\n",i);
    take_fork(i);     //Try to get forks
    printf("philosopher %d is eating\n",i);
    put_fork(i);     //Return forks
    
}

int main(){
    sem_init(&mutex,0,1);
    for(int i=0;i<N;i++){
        sem_init(&S[i],0,0);
        state[i]=thinking;
    }
    for(int i=0;i<N;i++){
        philosopher(i);
    }
}
