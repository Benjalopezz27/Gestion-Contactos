#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *archivo;
    char frase[100];

    printf("Ingresar una frase: ");
    fgets(frase, 100, stdin);

    int longitud = strlen(frase);
    for (int i = 0; i < longitud; i++)
    {
        frase[i] = toupper(frase[i]);
    }

    archivo = fopen("ejemplo.txt", "w");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.");
        return 1;
    }
    else
    {
        fputs(frase, archivo);
        fclose(archivo);
    }

    printf("Se ha escrito la frase en el archivo.\n");
    return 0;
}
