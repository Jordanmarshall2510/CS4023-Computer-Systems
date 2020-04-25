#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
 
int main(int argc, char* argv[]){
 
    float ref, tol;
    int r, c;
     
    struct tm *local;
    time_t start, end;

    // argv String to Float
    char *refString, *tolString;
	refString= tolString = NULL;
	int index;
	for (index= 1; index < argc; index++){
		if (strcmp(argv[index], "-r") == 0){ 
			refString = argv[index+1]; index++; 
		}
		if (strcmp(argv[index], "-t") == 0){ 
			tolString = argv[index+1]; index++; 
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
 
    //Nested For-Loop to Read Matrix
    for(int i = 0; i < rct; i++){
        for(int j = 0; j < cct; j++){
            fscanf(stdin, "%f", &rows[i][j]);
        }
    }
    
	time(&start);
    local = localtime(&start);
    printf("# Start time and date: %s", asctime(local));  

    //Printing
    int count = 0;
 
    for(r = 0; r < rct; r++){
        for(c = 0; c < cct; c++){
            if((approxEqual(rows[r][c], ref, tol))==1){
                printf("r=%d, c=%d: %.6f\n", r, c, rows[r][c]);
                count++;
            }
        }
    }
    fprintf(stdout, "Found %d approximate matches. \n", count);
     
    time(&end);
    local = localtime(&end);
    printf("# End time and date: %s", asctime(local));    
 
    exit(0);
}
