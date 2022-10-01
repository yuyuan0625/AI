#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t max_buffer_full;
sem_t min_buffer_full;
sem_t max_buffer_mutex;
sem_t min_buffer_mutex;

int maximum = 0, minimum = 2147483647;
int BigBuffer[1024]={0};
int max_buffer[4] = {0};
int min_buffer[4] = {RAND_MAX};
int max_idx = 0, min_idx = 0;

void *producer(int number){
	int min = 2147483647, max = 0;
	for(int i = 0+ number*256; i < 255+ number*256; i++)
	{
		if(BigBuffer[i] > max)
		{
			max = BigBuffer[i];
		}
		
		if(BigBuffer[i] < min)
		{
			min = BigBuffer[i];
		}
	}
	printf("Producer: Temporary max=%d and min=%d\n",max,min);
	sem_wait(&max_buffer_mutex);
	sem_wait(&min_buffer_mutex);
	
	max_buffer[max_idx] = max;
	min_buffer[min_idx] = min;
	printf("Producer: Put %d into max-buffer at %d\n",max, max_idx);
	printf("Producer: Put %d into min-buffer at %d\n",min, min_idx);
	max_idx++;
	min_idx++;
	sem_post(&max_buffer_mutex);
	sem_post(&min_buffer_mutex);
	sem_post(&max_buffer_full);
	sem_post(&min_buffer_full);
	pthread_exit(NULL);
}

void *consumer_min(void){
	for(int i = 0; i < 4; i++)
	{
		sem_wait(&min_buffer_full);
		if(min_buffer[i] < minimum)
			minimum = min_buffer[i];
		printf("Updated! minimum=%d\n", minimum);
	}
	pthread_exit(NULL);
}

void *consumer_max(void){
	for(int i = 0; i < 4; i++)
	{
		sem_wait(&max_buffer_full);
		if(max_buffer[i] > maximum)
			maximum = max_buffer[i];
		printf("Updated! maximum=%d\n", maximum);
	}
	pthread_exit(NULL);
}

int main(int argc,char*argv[])
{
	sem_init(&max_buffer_full,0,0);
	sem_init(&min_buffer_full,0,0);
	sem_init(&max_buffer_mutex,0,1);
	sem_init(&min_buffer_mutex,0,1);
	
	for(int i = 0; i < 1024; i++)
	{
		BigBuffer[i] = rand();
	}
	pthread_t p1,p2,p3,p4,c1,c2;
	pthread_create(&p1,NULL,(void*)producer,0);
	pthread_create(&p2,NULL,(void*)producer,1);
	pthread_create(&p3,NULL,(void*)producer,2);
	pthread_create(&p4,NULL,(void*)producer,3);
	pthread_create(&c1,NULL,(void*)consumer_min,NULL);
	pthread_create(&c2,NULL,(void*)consumer_max,NULL);
	
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	pthread_join(c1,NULL);
	pthread_join(c2,NULL);
	printf("Success! maximum=%d and minimum=%d\n",maximum,minimum);
	return 0;
}
