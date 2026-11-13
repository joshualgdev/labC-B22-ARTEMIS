#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

void configurar(Configuracion *config)
{
    Configuracion nueva;
    char confirmar;

    printf("Actual: altura %.2f km; masa %.2f kg.\n", config->altura_km, config->masa_kg);
    if (!leer_caracter("Usar valores de la consigna (192 km y 33000 kg)? s/n: ", &confirmar)) {
        return;
    }
    if (confirmar == 's') {
        nueva.altura_km = 192.0;
        nueva.masa_kg = 33000.0;
    } else {
        if (!leer_real("Altura LEO [160 a 2000 km]: ", 160.0, 2000.0, &nueva.altura_km) ||
            !leer_real("Masa [1 a 100000 kg]: ", 1.0, 100000.0, &nueva.masa_kg)) {
            return;
        }
    }
    /* Solo se cambia la configuracion cuando todos los datos son validos. */
    *config = nueva;
    puts("Configuracion guardada. El reporte anterior conserva sus resultados.");
}

void calcular_orbita(const Configuracion *config, Orbita *orbita)
{
    orbita->radio = RADIO_TIERRA + config->altura_km * 1000.0;
    orbita->velocidad = sqrt(G * MASA_TIERRA / orbita->radio);
    orbita->periodo = 2.0 * PI * orbita->radio / orbita->velocidad;
    orbita->aceleracion = orbita->velocidad * orbita->velocidad / orbita->radio;
    orbita->fuerza_gravitatoria = G * MASA_TIERRA * config->masa_kg /
                                (orbita->radio * orbita->radio);
    orbita->fuerza_centripeta = config->masa_kg * orbita->aceleracion;
}

void mostrar_orbita(const Configuracion *config, const Orbita *orbita)
{
    printf("\nAltura: %.2f km | Masa: %.2f kg\n", config->altura_km, config->masa_kg);
    printf("Radio desde el centro terrestre: %.2f m\n", orbita->radio);
    printf("Velocidad orbital: %.3f m/s (%.6f km/s)\n", orbita->velocidad, orbita->velocidad / 1000.0);
    printf("Periodo: %.3f s (%.3f min)\n", orbita->periodo, orbita->periodo / 60.0);
    printf("Aceleracion centripeta: %.6f m/s^2\n", orbita->aceleracion);
    printf("Fuerza gravitatoria: %.3f N\n", orbita->fuerza_gravitatoria);
    printf("Fuerza centripeta: %.3f N\n", orbita->fuerza_centripeta);
    puts("Fg = Fc: G*MT*m/r^2 = m*v^2/r; al cancelar m, v = sqrt(G*MT/r).");
    puts("La gravedad proporciona la fuerza centripeta; no son dos fuerzas que se suman.");
}

void calcular_pulso(double aceleracion, double duracion, Ensayo *ensayo)
{
    ensayo->aceleracion = aceleracion;
    ensayo->duracion = duracion;
    ensayo->delta_v = aceleracion * duracion;
    ensayo->desvio = 0.5 * aceleracion * duracion * duracion;
    ensayo->dentro_limite = ensayo->desvio <= LIMITE_DESVIO;
}

void simular(const Configuracion *config, Ensayo historial[], int *cantidad)
{
    Orbita orbita;
    double aceleracion;
    double duracion;
    int opcion;
    char confirmar;

    if (*cantidad > 0) {
        if (!leer_caracter("Se reemplazara el ultimo reporte. Continuar? s/n: ", &confirmar) ||
            confirmar == 'n') {
            return;
        }
    }
    *cantidad = 0;
    calcular_orbita(config, &orbita);
    mostrar_orbita(config, &orbita);
    puts("\nObjetivo: completar 3 ensayos con desvio local de hasta 100 m por ensayo.");
    puts("Es un limite didactico, no una condicion fisica de estabilidad orbital.");
    puts("Cada ensayo comienza de nuevo desde la orbita circular calculada.");
    puts("No se acumulan pulsos ni se propaga una orbita perturbada.");
    while (*cantidad < MAX_ENSAYOS) {
        printf("\nEnsayo %d de %d\n", *cantidad + 1, MAX_ENSAYOS);
        puts("1. Observar sin pulso\n2. Pulso de consigna (0.50 m/s^2, 10 s)");
        puts("3. Pulso personalizado\n0. Finalizar y ver reporte");
        if (!leer_entero("Decision: ", 0, 3, &opcion) || opcion == 0) {
            break;
        }
        aceleracion = 0.0;
        duracion = 0.0;
        if (opcion == 2) {
            aceleracion = 0.5;
            duracion = 10.0;
        } else if (opcion == 3) {
            if (!leer_real("Aceleracion lateral [0 a 2 m/s^2]: ", 0.0, 2.0, &aceleracion) ||
                !leer_real("Duracion [0 a 60 s]: ", 0.0, 60.0, &duracion)) {
                break;
            }
        }
        calcular_pulso(aceleracion, duracion, &historial[*cantidad]);
        printf("Delta v lateral: %.3f m/s | Desvio local: %.3f m\n",
               historial[*cantidad].delta_v, historial[*cantidad].desvio);
        if (historial[*cantidad].dentro_limite) {
            puts("Ensayo dentro del limite didactico.");
        } else {
            puts("Advertencia: ensayo fuera del limite didactico.");
        }
        if (aceleracion > 0.0 && duracion > 0.0) {
            puts("La trayectoria se perturba: ya no es el MCU original.");
            puts("El desvio es una aproximacion local respecto de la trayectoria sin pulso.");
        }
        (*cantidad)++;
    }
    mostrar_reporte(historial, *cantidad);
}

void mostrar_ayuda(void)
{
    puts("\nMODELO FISICO");
    puts("Tierra esferica, orbita circular ideal, sin rozamiento ni otros cuerpos.");
    puts("r = RT + h; v = sqrt(G*MT/r); T = 2*pi*r/v; ac = v^2/r.");
    puts("La masa de Orion cambia la fuerza, pero no v, T ni ac.");
    puts("Durante un pulso corto: delta_v = a*dt; desvio = a*dt^2/2.");
    puts("Se parte de velocidad lateral relativa nula. Para a=0.50 y dt=10: 5 m/s y 25 m.");
    puts("Se aproxima una direccion lateral fija perpendicular a la velocidad inicial.");
    puts("No se modela una aceleracion que se reorienta a cada instante.");
    puts("Durante el pulso la trayectoria se curva y deja de ser el circulo original.");
    puts("Despues sigue una trayectoria gravitatoria determinada por el impulso:");
    puts("segun su direccion, pueden cambiar el plano y/o los parametros orbitales.");
    puts("Este programa no calcula esa nueva orbita ni predice una caida.");
    puts("Rangos didacticos: altura 160-2000 km; masa 1-100000 kg; pulso 0-2 m/s^2, 0-60 s.");
    puts("A 192 km, ignorar el rozamiento solo es una idealizacion de corto plazo.");
    puts("Ingrese numeros sin separadores de miles; se acepta coma o punto decimal.");
    puts("El historial guarda hasta 3 ensayos en memoria y se pierde al salir.");
}
