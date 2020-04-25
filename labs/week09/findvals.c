#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "utils.h"
 
int main(int argc, char* argv[]){
 
    float ref, tol;
    int r, c;
     
    struct timeval tim;
    struct tm *local;
    time_t start;

    // argv String to Float
    char *refString, *tolString, *hitString;
	float v = 0;
	refString= tolString = hitString = NULL;
	int index;
	for (index= 1; index < argc; index++){
		if (strcmp(argv[index], "-r") == 0){ 
			refString = argv[index+1]; index++; 
		}
		if (strcmp(argv[index], "-t") == 0){ 
			tolString = argv[index+1]; index++; 
		}
		if (strcmp(argv[index], "-v") == 0){ 
			v=1; 
		}
	}
	if (refString == NULL || tolString == NULL){
			fprintf(stderr, "Usage: %s -r ref -t tol\n", argv[0]);
			exit(1);
	}
    ref = strtof(refString, 0);
    tol = strtof(tolString, 0);
     
    int rct, cct;
    fscanf(stdin,"%d", &rct);
    fscanf(stdin,"%d", &cct);
     
    // Allocating space for the matrix
    float** rows = (float **) malloc(rct * sizeof(float *));
    if (rows == 0){
        fprintf(stderr, "Couldn’t alocate sufficient space.\n");
        exit(1);
    }   
    int i;
    for (i = 0; i < rct; i++){
        float* row = (float *) malloc(cct * sizeof(float));
        if (row == 0){
            fprintf(stderr, "Couldn’t alocate sufficient row space.\n");
            exit(1);
        }
        rows[i] = row;
    }
 
    //Nested For-Loop read-in matrix
    for(int i = 0; i < rct; i++){
        for(int j = 0; j < cct; j++){
            fscanf(stdin, "%f", &rows[i][j]);
        }
    }
    
	time(&start);
  	local = localtime(&start);
   	gettimeofday(&tim,NULL);
    	double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
    	printf("# Start time and date: %s", asctime(local));  

    //Printing
    int count = 0;

 	#pragma omp parallel for collapse(2)
    for(r = 0; r < rct; r++){
        for(c = 0; c < cct; c++){
            if((approxEqual(rows[r][c], ref, tol))==1){
		if (v==1){
			fprintf(stdout, "r=%d, c=%d: %.6f \n",r, c, rows[r][c]);	
		}
		if (v){
			fprintf(stdout, "r=%d, cc=%d: %.6f (thread= %d)\n",r, c, rows[r][c], omp_get_thread_num());	
		}
		#pragma omp atomic
		count++;
            }
        }
    }

   
    gettimeofday(&tim, NULL);
    double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
    fprintf(stdout, "Found %d approximate matches. \n", count);
    printf("Search time: %f(s) \n", t2 -t1);     
 
    exit(0);
}
