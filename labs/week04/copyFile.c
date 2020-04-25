#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"



int main(int argc, char* argv[]){

	int flipping = strcmp(argv[1], "-f") == 0;

	char c;
	FILE *from;
	FILE *go;

	if(argc == 3 || (flipping == 1 && argc == 4)){
		int argNum = 1;
		if(flipping == 1){
			argNum = 2;
		}
		from = fopen(argv[argNum], "r");
		
		if (from == NULL){
			perror(argv[1]);
			exit(1);
		}

		go = fopen(argv[argNum+1], "w");
		
		if (go == NULL){
			perror(argv[argNum+1]);
			exit(1);
		}
   
    
  		/* file exists, so start reading */
  
 	 	while ((c = getc(from)) != EOF){

		    if (flipping){
		      putc(flipChar(c), go);
		    }else{
		      putc(c,go);
		    }
		 }

  fclose(from);
  fclose(go);
  }

exit(0);    
}
