#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PERMS 0666
#define turn 10 

void *agent();
void *tobacco();
void *match();
void *paper();

pthread_mutex_t s_lock, s_agent, s_tobacco,s_paper, s_match; // for cuncurrency

void main(){

	// create thread variables for splitting process
	pthread_t agent_thread, paper_thread, tobacco_thread, match_thread;

	int a, b, c, d; // for pthread return
	

	pthread_mutex_init(&s_lock, NULL);
	pthread_mutex_init(&s_match, NULL);
	pthread_mutex_init(&s_agent, NULL);
	pthread_mutex_init(&s_paper, NULL);
	pthread_mutex_init(&s_tobacco, NULL);

	pthread_mutex_lock(&s_match);
	pthread_mutex_lock(&s_agent);
	pthread_mutex_lock(&s_paper);
	pthread_mutex_lock(&s_tobacco);
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
	
	// end the threads
	 pthread_join( agent_thread, NULL);
	 pthread_join( paper_thread, NULL);
	 pthread_join( tobacco_thread, NULL);
	 pthread_join( match_thread, NULL);	

	pthread_mutex_destroy(&s_lock);
	pthread_mutex_destroy(&s_match);
	pthread_mutex_destroy(&s_agent);
	pthread_mutex_destroy(&s_paper);
	pthread_mutex_destroy(&s_tobacco);

	 exit(EXIT_SUCCESS);

}


void *agent(){
	int n =	turn; 
	while(n>0){ // do n loop of process
		n--;
		pthread_mutex_lock(&s_lock); // seek its turn for 
		int randnum = rand()%3+1;

		printf("agent round %d, random number is %d \n", turn-n,randnum);
		if (randnum == 1){
			printf("Put tobacco on table\n");
			printf("Put paper on table\n");

			pthread_mutex_unlock(&s_match);

		}
		else if(randnum == 2){
			 printf("Put tobacco on table\n");
			 printf("Put match on table\n");
			pthread_mutex_unlock(&s_paper);
		}

		else{
		
			printf(" Put match on table\n");
			printf("Put paper on table\n");
			pthread_mutex_unlock(&s_tobacco);
		}
		// delete woken proc

			
		pthread_mutex_unlock(&s_lock);
		pthread_mutex_lock(&s_agent);
	}

}
void *tobacco(){
	int n =	turn; 
	while(n>0){
		n--;
		//printf("tobacco waiting for tobacco\n");
		pthread_mutex_lock(&s_tobacco );  // Sleep right away
	//	printf("tobacco waiting for lock\n");
		pthread_mutex_lock(&s_lock );
		printf("Pick up match\n");
		printf("Pick up paper\n");
		pthread_mutex_unlock(&s_agent );
		pthread_mutex_unlock(&s_lock );
		printf("Smoke (but don't inhale)\n");
	}
}


void *match(){
	int n =	turn; 
	while(n>0){
		n--;
	//	printf("match waiting for match \n");
		pthread_mutex_lock(&s_match );  // Sleep right away
	//	printf("match waiting for lock\n");
		pthread_mutex_lock(&s_lock );
		printf("Pick up tobacco\n");
		printf("Pick up paper\n");
		pthread_mutex_unlock(&s_agent );
		pthread_mutex_unlock(&s_lock );
		printf("Smoke (but don't inhale)\n");
	}

}

void *paper(){
	int n =	turn; 
	while(n>0){
		n--;
	//	printf("paper waiting for paper \n");
		pthread_mutex_lock(&s_paper );  // Sleep right away
	//	printf("paper waiting for lock \n");
		pthread_mutex_lock(&s_lock );
		printf("Pick up match\n");
		printf("Pick up tobacco\n");
		pthread_mutex_unlock(&s_agent );
		pthread_mutex_unlock(&s_lock );
		printf("Smoke (but don't inhale)\n");
	}
}

