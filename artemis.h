#ifndef ARTEMIS_H
#define ARTEMIS_H

#define G 6.674e-11
#define MASA_TIERRA 5.972e24
#define RADIO_TIERRA 6371000.0
#define PI 3.14159265358979323846
#define MAX_ENSAYOS 3
#define LIMITE_DESVIO 100.0

typedef struct {
    double altura_km;
    double masa_kg;
} Configuracion;

typedef struct {
    double radio;
    double velocidad;
    double periodo;
    double aceleracion;
    double fuerza_gravitatoria;
    double fuerza_centripeta;
} Orbita;

typedef struct {
    double aceleracion;
    double duracion;
    double delta_v;
    double desvio;
    int dentro_limite;
} Ensayo;

void configurar(Configuracion *config);
void calcular_orbita(const Configuracion *config, Orbita *orbita);
void mostrar_orbita(const Configuracion *config, const Orbita *orbita);
void calcular_pulso(double aceleracion, double duracion, Ensayo *ensayo);
void simular(const Configuracion *config, Ensayo historial[], int *cantidad);
void mostrar_reporte(const Ensayo historial[], int cantidad);
void mostrar_ayuda(void);

#endif
