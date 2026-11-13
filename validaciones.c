#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "validaciones.h"

/* Leer la linea completa evita que una letra deje trabado el menu. */
static int leer_linea(const char *mensaje, char linea[], int capacidad)
{
    int caracter;
    int completa;

    while (1) {
        printf("%s", mensaje);
        fflush(stdout);
        if (fgets(linea, capacidad, stdin) == NULL) {
            printf("\nEntrada cerrada. Se vuelve al menu o se termina.\n");
            return 0;
        }
        if (strchr(linea, '\n') != NULL || feof(stdin)) {
            return 1;
        }
        /* Descarta todo el resto, no solo el primer caracter sobrante. */
        completa = 0;
        while (!completa) {
            caracter = getchar();
            if (caracter == '\n' || caracter == EOF) {
                completa = 1;
            }
        }
        puts("Entrada demasiado larga. Intente nuevamente.");
    }
}

static int solo_espacios(const char *texto)
{
    while (*texto != '\0') {
        if (!isspace((unsigned char)*texto)) {
            return 0;
        }
        texto++;
    }
    return 1;
}

int leer_entero(const char *mensaje, int minimo, int maximo, int *valor)
{
    char linea[128];
    char *fin;
    long numero;

    while (leer_linea(mensaje, linea, sizeof(linea))) {
        errno = 0;
        numero = strtol(linea, &fin, 10);
        if (fin != linea && solo_espacios(fin) && errno != ERANGE &&
            numero >= minimo && numero <= maximo) {
            *valor = (int)numero;
            return 1;
        }
        printf("Ingrese un entero entre %d y %d, sin texto adicional.\n", minimo, maximo);
    }
    return 0;
}

int leer_real(const char *mensaje, double minimo, double maximo, double *valor)
{
    char linea[128];
    char *fin;
    double numero;
    int i;

    while (leer_linea(mensaje, linea, sizeof(linea))) {
        /* Se admite tanto 0,5 como 0.5, sin separadores de miles. */
        for (i = 0; linea[i] != '\0'; i++) {
            if (linea[i] == ',') {
                linea[i] = '.';
            }
        }
        errno = 0;
        numero = strtod(linea, &fin);
        if (fin != linea && solo_espacios(fin) && errno != ERANGE &&
            isfinite(numero) && numero >= minimo && numero <= maximo) {
            *valor = numero;
            return 1;
        }
        printf("Ingrese un numero finito entre %.2f y %.2f, sin texto adicional.\n",
               minimo, maximo);
    }
    return 0;
}

int leer_caracter(const char *mensaje, char *valor)
{
    char linea[128];
    int i;
    char letra;

    while (leer_linea(mensaje, linea, sizeof(linea))) {
        i = 0;
        while (isspace((unsigned char)linea[i])) {
            i++;
        }
        letra = (char)tolower((unsigned char)linea[i]);
        if ((letra == 's' || letra == 'n') && solo_espacios(&linea[i + 1])) {
            *valor = letra;
            return 1;
        }
        puts("Ingrese solamente s o n.");
    }
    return 0;
}
