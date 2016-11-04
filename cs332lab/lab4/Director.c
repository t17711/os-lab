
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void getaverage(int ** grades, int x, int y, int gap){
	int i =0;
	int avgt = 0;
	int pos  = x*gap + y;// in line  
	for(i=0;i<10;++i){
		avgt+=grades[i][pos];
		//printf("%d",avgt);
	}

	printf("The average of chapter %d and hw %d is %f\n",x+1,y+1,(float)avgt/10.0);
}


int main(int argc, char ** args){

	if (argc <4) {
		printf("need filename and both x (chapter number) and y hw number\n");
		return 0;
	}	
	int x = atoi(args[2]);
	int y = atoi(args[3]);
	int line = x*y;
	int gap = y;

	// read 10 lines as 2d array
	int **grades;
	grades =  malloc(10*sizeof(int*));// 10 rows of pointer of arrays
	
	static float ** avg; // it is chapter hw [x][y]
	avg = malloc (x*sizeof(float*));

	// initialize storage
	int i=0;
	printf("x : %d, y: %d \n", x, y);
	for(i=0;i<10;++i){
		grades[i] = malloc(line*sizeof(int));
	}

	// grades avg 
	for(i=0;i<x;++i){
		avg[i] = malloc(y*sizeof(float));
	}

	// read file
	FILE * file = fopen(args[1], "r");

	int j =0;
	// scan one grade at a tieme
	for(i=0;i<10;++i){
		for(j=0;j<line;++j){
			fscanf(file, "%d", &grades[i][j]);
		}
	}

	// now create children
	pid_t * m = malloc(x*sizeof(pid_t));	
	
	int p1=0,p2=0;

	// create manager first who create worker;
	for(i=0;i<x;++i){
		pid_t manager = fork(); // fork for manager i
		if (manager == 0){
			
			pid_t * w = malloc(y*sizeof(pid_t));	
			
			for(j =0;j<y;++j){ // fork workers
			
				pid_t worker = fork();
				if (worker== 0){ // get average for each worker
					getaverage(grades, i , j, y);
					exit(0);
				}

				else if (worker== -1) {
					printf("Fork failed\n"); 
					exit(0);
				}
				else{
					w[p2++] = worker;
				}
			}
			int k,st;
			for(k=0;k<y;++k) {
				int stat;
				waitpid(w[k],&stat,0);
			}
			exit(0);
		}
		else if (manager == -1) {
			printf("Fork failed\n"); 
			exit(0);
		}
		else{
			m[p1++] = manager;
		}
	}

	int k, st;
	for(k=0;k<x;++k){
		int sta;
		waitpid(m[k],&sta,0);
	}
	
	fclose(file);

	return 1;
}
