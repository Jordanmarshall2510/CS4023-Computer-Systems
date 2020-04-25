#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c;
  FILE *from;
  FILE *go;

  from = fopen("file.txt", "r");
  if (from == NULL)
  {
    perror("file.txt");
    exit(1);
  }

  go = fopen("copy.txt", "w");
  if (go == NULL)
    {
      perror("copy.txt");
      exit(1);
    }
  
    
  /* file exists, so start reading */
  while ((c = getc(from)) != EOF)
    putc(c, go);

  fclose(from);
  fclose(go);

  exit(0);
}
