#include <string.h>
#include <stdio.h>

void main(int argc, char *argv[]) {
  char buffer[512];

  printf("argv[1]:%s",argv[1]);

  if (argc > 1)
    strcpy(buffer,argv[1]);
}

