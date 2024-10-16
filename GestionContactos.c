#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nombre[50];
    char numero[50];
    char mail[50];
} Contacto;

void agregarContacto(FILE *archivo);
void mostrarContacto(FILE *archivo);
void eliminarContacto(FILE *archivo);

void main()
{

    FILE *archivo;
    int numero;
    do
    {
        printf("---------- GESTION DE CONTACTOS ----------\n");
        printf("1 - Agregar contacto. \n");
        printf("2 - Mostrar contactos.\n");
        printf("3 - Eliminar contacto.\n");
        printf("4 - Salir.\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &numero);
        getchar();

        switch (numero)
        {
        case 1:
            agregarContacto(archivo);
            break;
        case 2:
            mostrarContacto(archivo);
            break;
        case 3:
            eliminarContacto(archivo);
            break;
        case 4:
            printf("¿Está seguro que desea salir?");
            break;

        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    } while (numero != 4);
}

void agregarContacto(FILE *archivo)
{
    Contacto contacto;
    FILE *arch = fopen("contactos.txt", "a");
    if (!arch)
    {
        printf("No se pudo abrir el archivo");
        return;
    }
    printf("Ingrese el nombre: ");
    fgets(contacto.nombre, sizeof(contacto.nombre), stdin);
    fputs(contacto.nombre, arch);

    printf("Ingrese el teléfono: ");
    fgets(contacto.numero, sizeof(contacto.numero), stdin);
    fputs(contacto.numero, arch);

    printf("Ingrese el mail: ");
    fgets(contacto.mail, sizeof(contacto.mail), stdin);
    fputs(contacto.mail, arch);

    fclose(arch);
}
void mostrarContacto(FILE *archivo)
{
    Contacto contacto;
    FILE *arch = fopen("contactos.txt", "r");
    if (!arch)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fgets(contacto.nombre, sizeof(contacto.nombre), arch) != NULL)
    {
        printf("--Nombre: %s--Teléfono: %s--Mail: %s--\n", contacto.nombre, contacto.numero, contacto.mail);
        printf("-------------------------------------------------------------------------------------------------");
    }
    fclose(arch);
}

void eliminarContacto(FILE *archivo) {}