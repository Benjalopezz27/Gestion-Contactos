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
        getchar(); // Clear the newline character from the buffer

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
            char confirm;
            scanf(" %c", &confirm);
            if (confirm == 's' || confirm == 'S')
            {
                printf("Saliendo...\n");
            }
            else
            {
                opcion = 0; // Reset option to continue
            }
            break;
        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    } while (opcion != 4);

    return 0; // Return success
}

void agregarContacto()
{
    Contacto contacto;
    FILE *arch = fopen("contactos.txt", "a");
    if (arch == NULL)
    {
        perror("No se pudo abrir el archivo");
        return;
    }

    printf("Ingrese el nombre: ");
    fgets(contacto.nombre, sizeof(contacto.nombre), stdin);
    contacto.nombre[strcspn(contacto.nombre, "\n")] = 0; // Remove newline character

    printf("Ingrese el teléfono: ");
    fgets(contacto.numero, sizeof(contacto.numero), stdin);
    contacto.numero[strcspn(contacto.numero, "\n")] = 0;

    printf("Ingrese el mail: ");
    fgets(contacto.mail, sizeof(contacto.mail), stdin);
    contacto.mail[strcspn(contacto.mail, "\n")] = 0;

    fprintf(arch, "%s %s %s\n", contacto.nombre, contacto.numero, contacto.mail);
    fclose(arch);

    printf("Contacto agregado.\n");
}

void mostrarContactos()
{
    Contacto contacto;
    FILE *arch = fopen("contactos.txt", "r");
    if (arch == NULL)
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
    // Implementation for contact deletion can be added here.
    printf("Función de eliminar contacto no implementada aún.\n");
}
