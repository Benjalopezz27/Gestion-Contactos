#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[50];
    char numero[50];
    char mail[50];
} Contacto;

void agregarContacto();
void mostrarContactos();
void eliminarContacto();

int main()
{
    int opcion;

    do
    {
        printf("---------- GESTION DE CONTACTOS ----------\n");
        printf("1 - Agregar contacto.\n");
        printf("2 - Mostrar contactos.\n");
        printf("3 - Eliminar contacto.\n");
        printf("4 - Salir.\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            agregarContacto();
            break;
        case 2:
            mostrarContactos();
            break;
        case 3:
            eliminarContacto();
            break;
        case 4:
            printf("¿Está seguro que desea salir? (s/n): ");
            break;
        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 4);
}

void agregarContacto()
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

    printf("Ingrese el teléfono: ");
    fgets(contacto.numero, sizeof(contacto.numero), stdin);

    printf("Ingrese el mail: ");
    fgets(contacto.mail, sizeof(contacto.mail), stdin);

    fprintf(arch, "%s %s %s\n", contacto.nombre, contacto.numero, contacto.mail);
    fclose(arch);

    printf("Contacto agregado.\n");
}

void mostrarContactos()
{
    Contacto contacto;
    FILE *arch = fopen("contactos.txt", "r");
    if (!arch)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while (fscanf(arch, "%49s %49s %49s", contacto.nombre, contacto.numero, contacto.mail) == 3)
    {
        printf("--Nombre: %s--Telefono: %s--Mail: %s--\n", contacto.nombre, contacto.numero, contacto.mail);
    }
    fclose(arch);
}

void eliminarContacto()
{
}
