#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

int main(void)
{
    Configuracion config = {192.0, 33000.0};
    Orbita orbita;
    Ensayo historial[MAX_ENSAYOS];
    int cantidad = 0;
    int opcion = -1;

    puts("ARTEMIS - Escenario 2 - Grupo B22");
    while (opcion != 0) {
        puts("\n1. Configurar orbita\n2. Calcular orbita circular\n3. Iniciar ensayos por turnos");
        puts("4. Ver ultimo reporte\n5. Ayuda y formulas\n0. Salir");
        if (!leer_entero("Opcion: ", 0, 5, &opcion)) {
            opcion = 0;
        }
        switch (opcion) {
            case 1:
                configurar(&config);
                break;
            case 2:
                calcular_orbita(&config, &orbita);
                mostrar_orbita(&config, &orbita);
                break;
            case 3:
                simular(&config, historial, &cantidad);
                break;
            case 4:
                mostrar_reporte(historial, cantidad);
                break;
            case 5:
                mostrar_ayuda();
                break;
            case 0:
                puts("Fin del simulador.");
                break;
        }
    }
    return 0;
}
