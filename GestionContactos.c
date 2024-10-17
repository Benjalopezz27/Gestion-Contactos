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
            printf("¿Está seguro que desea salir?\n");
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
    FILE *arch = fopen("contactos.dat", "ab");
    if (!arch)
    {
        printf("No se pudo abrir el archivo");
        return;
    }

    printf("Ingrese el nombre: ");
    fgets(contacto.nombre, sizeof(contacto.nombre), stdin);
    contacto.nombre[strcspn(contacto.nombre, "\n")] = '\0';

    printf("Ingrese el teléfono: ");
    fgets(contacto.numero, sizeof(contacto.numero), stdin);
    contacto.numero[strcspn(contacto.numero, "\n")] = '\0';

    printf("Ingrese el mail: ");
    fgets(contacto.mail, sizeof(contacto.mail), stdin);
    contacto.mail[strcspn(contacto.mail, "\n")] = '\0';

    fwrite(&contacto, sizeof(contacto), 1, arch);

    fclose(arch);

    printf("Contacto agregado.\n");
}

void mostrarContactos()
{
    Contacto contacto;
    FILE *arch = fopen("contactos.dat", "rb");
    if (!arch)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    printf("---- Lista de Contactos ----\n");
    while (fread(&contacto, sizeof(contacto), 1, arch))
    {
        printf("--Nombre: %s--Telefono: %s--Mail: %s--\n", contacto.nombre, contacto.numero, contacto.mail);
    }
    fclose(arch);
}

void eliminarContacto()
{
    FILE *arch = fopen("contactos.dat", "rb");
    if (!arch)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    FILE *archTemp = fopen("temporal.dat", "wb");
    if (!archTemp)
    {
        fclose(arch);
        printf("No se pudo crear el archivo temporal.\n");
        return;
    }

    int encontrado = 0;
    char nombre[50];
    Contacto contacto;

    printf("Ingrese el nombre del contacto a eliminar:\n");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    while (fread(&contacto, sizeof(Contacto), 1, arch))
    {
        if (strcmp(nombre, contacto.nombre) != 0)
        {
            fwrite(&contacto, sizeof(Contacto), 1, archTemp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arch);
    fclose(archTemp);

    remove("contactos.dat");
    rename("temporal.dat", "contactos.dat");

    if (encontrado)
    {
        printf("Contacto eliminado.\n");
    }
    else
    {
        printf("Contacto no encontrado.\n");
    }
}
