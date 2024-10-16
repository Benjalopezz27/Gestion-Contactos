#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *filePointer;
    filePointer = fopen("hello-world.txt", "r");

    char line[1024];

    printf("La frase es: ");
    fgets(line, 1024, filePointer);
    printf("%s", line);
    fclose(filePointer);
}