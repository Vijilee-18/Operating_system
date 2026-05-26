#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#define size 5

sem_t empty;
sem_t full;
sem_t mutex;

int count=0;
int buffer[size];
int in=0;
int out=0;

void produce(int item)
{
    if(count==size)
    {
        printf("Buffer is Full . Cannot Produce !");
        return ;
    }
    else
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in]=item;
        in=(in+1)%size;
        count++;
        printf("Produced %d Item . No of Items in the Buffer :%d .", item,count);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void consume()
{
    if(count==0)
    {
        printf("Buffer is Empty.");
        return ;
    }
    else
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int item=buffer[out];
        out=(out+1)%size;
        count--;
        printf("Consumed %d Item . No of Items in the Buffer :%d .", item,count);
        sem_post(&mutex);
        sem_post(&empty);
    }

}

int main()
{
    int choice , item;
    sem_init(&empty,0,size);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);

    while(1)
    {
        printf("\n1. To Produce\n2. To Consume \n3. Exit");
        printf("\nChoose an Option :");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter an Item to Produce :");
                scanf("%d",&item);
                produce(item);
                break;
            case 2:
                consume();
                break;
            case 3:
                printf("Exiting the Producer Consumer Problem.");
                sem_destroy(&empty);
                sem_destroy(&full);
                sem_destroy(&mutex);
                exit(0);
            default:
                printf("Invalid Input");
        }
    }
    return 0;
}