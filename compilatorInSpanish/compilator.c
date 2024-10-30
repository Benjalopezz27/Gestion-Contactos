#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char line[1024];
    char newLine[1024];
    FILE *filePointer;
    FILE *tempFile;

    filePointer = fopen("compilator.txt", "r");
    if (!filePointer)
    {
        printf("No se puede abrir el archivo.\n");
        exit(1);
    }

    tempFile = fopen("temp.txt", "w");
    if (!tempFile)
    {
        fclose(filePointer);
        printf("No se puede abrir el archivo temporal.\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), filePointer) != NULL)
    {
        strcpy(newLine, "");

        if (strstr(line, "#incluir") != NULL)
        {
            strcat(newLine, "#include <stdio.h>\n");
        }
        else if (strstr(line, "entero principal()") != NULL)
        {
            strcat(newLine, "int main()\n ");
        }
        else if (strstr(line, "entero") != NULL)
        {
            strcat(newLine, "int ");
            strcat(newLine, strchr(line, ' '));
        }
        else if (strstr(line, "imprimir") != NULL)
        {
            strcat(newLine, "printf");
            strcat(newLine, strchr(line, '('));
        }
        else if (strstr(line, "leer") != NULL)
        {
            strcat(newLine, "scanf");
            strcat(newLine, strchr(line, '('));
        }
        else if (strstr(line, "retornar") != NULL)
        {
            strcat(newLine, "return ");
            strcat(newLine, strchr(line, '0'));
        }
        else
        {
            strcpy(newLine, line);
        }

        fputs(newLine, tempFile);
    }

    fclose(filePointer);
    fclose(tempFile);

    remove("compilator.txt");
    rename("temp.txt", "compilator.txt");

    printf("La traducción se ha completado.\n");
    return 0;
}
