#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/*
This program provides a possible solution for first readers writers problem using mutex and semaphore.
I have used 10 readers and 5 producers to demonstrate the solution. You can always play with these values.
*/

sem_t choco;
pthread_mutex_t mutex;
int cnt = 1;
int chocolatecount = 0;

void *chocolatemanufactured(void *cno)  //writer
{   
    sem_wait(&choco);
    cnt = cnt*3;
    printf("Packet %d Chocolate Produced  %d\n",(*((int *)cno)),cnt);
    sem_post(&choco);

}
void *chocolateprocess(void *processno)  // reader
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    chocolatecount++;
    if(chocolatecount == 1) {
        sem_wait(&choco); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("Box %d: Chocolate on process %d\n",*((int *)processno),cnt);

    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    chocolatecount--;
    if(chocolatecount == 0) {
        sem_post(&choco); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t chocolatein[8],chocolateout[4];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&choco,0,1);

    int a[8] = {1,2,3,4,5,6,7,8}; //Just used for numbering the producer and consumer

    for(int i = 0; i <8; i++) {
        pthread_create(&chocolatein[i], NULL, (void *)chocolateprocess, (void *)&a[i]);
    }
    for(int i = 0; i < 4; i++) {
        pthread_create(&chocolateout[i], NULL, (void *)chocolatemanufactured, (void *)&a[i]);
    }

    for(int i = 0; i < 8; i++) {
        pthread_join(chocolatein[i], NULL);
    }
    for(int i = 0; i < 4; i++) {
        pthread_join(chocolateout[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&choco);

    return 0;
    
}
