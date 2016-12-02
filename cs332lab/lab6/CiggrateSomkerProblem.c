#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sem.h"

#define PERMS 0666
#define turn 10 

void *agent();
void *tobacco();
void *match();
void *paper();

int s_lock, s_agent, s_tobacco,s_paper, s_match; // for semaphore 

void main(){

	pthread_t agent_thread, paper_thread, tobacco_thread, match_thread;

	int a, b, c, d; // for pthread
		
	// create semaphore
	// semaphore creation
	 
	if((s_lock=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	 {
	   printf("\n can't create lock semaphore");
	   exit(1);
	 }

	if((s_agent=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	 {
	   printf("\n can't create agent semaphore");
	   exit(1);
	 }

	if((s_tobacco=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	 {
	   printf("\n can't create tobacco semaphore");
	   exit(1);
	 }

	if((s_paper=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	 {
	   printf("\n can't create paper semaphore");
	   exit(1);
	 }
	if((s_match=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	 {
	   printf("\n can't create match semaphore");
	   exit(1);
	 }

	// initialize all semaphore except lock to 0
	sem_create(s_match,0);
	sem_create(s_paper,0);
	sem_create(s_agent,0);
	sem_create(s_tobacco,0);
	sem_create(s_lock,1);
	// create thread
	a = pthread_create( &agent_thread, NULL, &agent,NULL);
	if(a)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",a);
		exit(EXIT_FAILURE);
	}

	b = pthread_create( &paper_thread, NULL, &paper,NULL);
	if(b)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",b);
		exit(EXIT_FAILURE);
	}

	c = pthread_create( &tobacco_thread, NULL, &tobacco,NULL);
	if(c)
	{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",c);
		exit(EXIT_FAILURE);
	}
	
	d = pthread_create( &match_thread, NULL, &match, NULL);
	if(d)
	{
		 fprintf(stderr,"Error - pthread_create() return code: %d\n",d);
		 exit(EXIT_FAILURE);
	}

	 pthread_join( agent_thread, NULL);
	 pthread_join( paper_thread, NULL);
	 pthread_join( tobacco_thread, NULL);
	 pthread_join( match_thread, NULL);	

	 exit(EXIT_SUCCESS);

}


void *agent(){
	int n =	turn; 
	while(n>0){
		n--;
		P(s_lock);
		int randnum = rand()%3+1;

		printf("agent round %d, random number is %d \n", turn-n,randnum);
		if (randnum == 1){
			printf("Put tobacco on table\n");
			printf("Put paper on table\n");

			V(s_match);

		}
		else if(randnum == 2){
			 printf("Put tobacco on table\n");
			 printf("Put match on table\n");
			V(s_paper);
		}

		else{
		
			printf(" Put match on table\n");
			printf("Put paper on table\n");
			V(s_tobacco);
		}
		// delete woken proc

			
		V(s_lock);
		P(s_agent);
	}
		printf("\n Clean UP\n");
	
		int i;
		for( i=10;i>0;--i){
			V(s_tobacco);
			V(s_paper);
			V(s_match);
		}

}
void *tobacco(){
	int n =	turn; 
	while(n>0){
		n--;
		//printf("tobacco waiting for tobacco\n");
		P(s_tobacco );  // Sleep right away
	//	printf("tobacco waiting for lock\n");
		P(s_lock );
		printf("Pick up match\n");
		printf("Pick up paper\n");
		V(s_agent );
		V(s_lock );
		printf("Smoke (but don't inhale)\n");
	}
}


void *match(){
	int n =	turn; 
	while(n>0){
		n--;
	//	printf("match waiting for match \n");
		P(s_match );  // Sleep right away
	//	printf("match waiting for lock\n");
		P(s_lock );
		printf("Pick up tobacco\n");
		printf("Pick up paper\n");
		V(s_agent );
		V(s_lock );
		printf("Smoke (but don't inhale)\n");
	}

}

void *paper(){
	int n =	turn; 
	while(n>0){
		n--;
	//	printf("paper waiting for paper \n");
		P(s_paper );  // Sleep right away
	//	printf("paper waiting for lock \n");
		P(s_lock );
		printf("Pick up match\n");
		printf("Pick up tobacco\n");
		V(s_agent );
		V(s_lock );
		printf("Smoke (but don't inhale)\n");
	}
}

