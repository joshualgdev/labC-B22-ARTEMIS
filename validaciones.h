#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Devuelven 1 si se obtuvo un dato y 0 si se cerro la entrada (EOF). */
int leer_entero(const char *mensaje, int minimo, int maximo, int *valor);
int leer_real(const char *mensaje, double minimo, double maximo, double *valor);
int leer_caracter(const char *mensaje, char *valor);

#endif
