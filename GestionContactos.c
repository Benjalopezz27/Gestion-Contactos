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
void modificarContacto();
int compararContactos();
void ordenarContactos();

int main()
{
    int opcion;

    do
    {
        printf("---------- GESTION DE CONTACTOS ----------\n");
        printf("1 - Agregar contacto.\n");
        printf("2 - Mostrar contactos.\n");
        printf("3 - Eliminar contacto.\n");
        printf("4 - Modificar contacto.\n");
        printf("5 - Ordenar contactos.\n");
        printf("6 - Salir.\n");
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
            modificarContacto();
            break;
        case 5:
            ordenarContactos();
            break;
        case 6:
            printf("¿Está seguro que desea salir?\n");
            break;
        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 6);
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
        printf("----Nombre: %s --Telefono: %s --Mail: %s ---- \n", contacto.nombre, contacto.numero, contacto.mail);
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

    printf("Ingrese el nombre del contacto a eliminar: \n");
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

void modificarContacto()
{
    int opcion;
    char nombre[50];
    Contacto contacto;
    FILE *arch = fopen("contactos.dat", "rb");
    FILE *temporal = fopen("temporal.dat", "wb");
    if (!arch || !temporal)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    printf("Ingrese el nombre del contacto a modificar: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    int encontrado = 0;

    while (fread(&contacto, sizeof(contacto), 1, arch))
    {
        if (strcmp(nombre, contacto.nombre))
        {
            encontrado = 1;
            printf("Ingrese el numero correspondiente (1 - nombre, 2 - telefono, 3 - mail): ");
            scanf("%d", &opcion);
            getchar();

            switch (opcion)
            {
            case 1:
                printf("Ingrese el nuevo nombre: ");
                fgets(contacto.nombre, sizeof(contacto.nombre), stdin);
                contacto.nombre[strcspn(contacto.nombre, "\n")] = '\0';
                break;
            case 2:
                printf("Ingrese el nuevo telefono: ");
                fgets(contacto.numero, sizeof(contacto.numero), stdin);
                contacto.numero[strcspn(contacto.numero, "\n")] = '\0';
                break;
            case 3:
                printf("Ingrese el nuevo mail: ");
                fgets(contacto.mail, sizeof(contacto.mail), stdin);
                contacto.mail[strcspn(contacto.mail, "\n")] = '\0';
                break;
            default:
                printf("Opcion no valida\n");
                break;
            }
        }
        fwrite(&contacto, sizeof(contacto), 1, temporal);
    }

    fclose(arch);
    fclose(temporal);

    if (encontrado)
    {
        remove("contactos.dat");
        rename("temporal.dat", "contactos.dat");
        printf("Contacto modificado exitosamente.\n");
    }
    else
    {
        printf("Contacto no encontrado.\n");
        remove("temporal.dat");
    }
}
int compararContactos(const void *a, const void *b)
{
    Contacto *contactoA = (Contacto *)a;
    Contacto *contactoB = (Contacto *)b;
    return strcmp(contactoA->nombre, contactoB->nombre);
}
void ordenarContactos()
{

    FILE *arch = fopen("contactos.dat", "rb");
    if (!arch)
    {
        printf("No es posible abrir el archivo.\n");
        exit(1);
    }

    // Contar el número de contactos
    fseek(arch, 0, SEEK_END);
    long tamano = ftell(arch);
    int numContactos = tamano / sizeof(Contacto);
    fseek(arch, 0, SEEK_SET);

    // Crear un array para almacenar los contactos
    Contacto *contactos = malloc(numContactos * sizeof(Contacto));
    if (!contactos)
    {
        printf("Error al asignar memoria.\n");
        fclose(arch);
        exit(1);
    }

    // Leer todos los contactos del archivo
    fread(contactos, sizeof(Contacto), numContactos, arch);
    fclose(arch);

    // Ordenar los contactos
    qsort(contactos, numContactos, sizeof(Contacto), compararContactos);

    // Volver a escribir los contactos ordenados en el archivo
    arch = fopen("contactos.dat", "wb");
    if (!arch)
    {
        printf("No es posible abrir el archivo para escritura.\n");
        free(contactos);
        exit(1);
    }

    fwrite(contactos, sizeof(Contacto), numContactos, arch);
    fclose(arch);
    free(contactos);
}