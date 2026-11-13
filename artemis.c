#include <stdio.h>
#include <math.h>
#include "artemis.h"

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
