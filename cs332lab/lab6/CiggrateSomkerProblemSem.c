#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

#define PERMS 0666
#define turn 10 

void *agent();
void *tobacco();
void *match();
void *paper();

int s_lock, s_agent, s_tobacco,s_paper, s_match; // for semaphore 

void main(){


		
	// create semaphore for paper, tobacco, and match items
	// create lock mutex so that only one printf sets happen at once
	// agent semaphore for agent process
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
	
	// creatte processes	

	int pid1, pid2, pid3, pid4;

	// fork all 4 process
	pid1 = fork();
	if(pid1 ==-1){
	//fork failed!
		perror("fork");
		exit(1);
	}
	else if (pid1 == 0){
		agent();
		exit(1);
	}

	pid2 = fork();
	if(pid2 ==-1){
	//fork failed!
		perror("fork");
		exit(1);
	}
	else if (pid2 == 0){
		tobacco();
		exit(1);
	}
	
	pid3 = fork();
	if(pid3 ==-1){
	//fork failed!
		perror("fork");
		exit(1);
	}
	else if(pid3 == 0){
		match();
		exit(1);
	}
	
	pid4 = fork();
	if(pid4 ==-1){
	//fork failed!
		perror("fork");
		exit(1);
	}
	else if(pid4 == 0){
		paper();
		exit(1);
	}

}


void *agent(){
	int n =	turn; 
	while(n>0){ // do n loop of process
		n--;
		P(s_lock); // seek its turn for accessing table 
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

