# Simulador Artemis - Escenario 2

Trabajo Final Integrador de Laboratorio de C, Algoritmos y Estructuras de Datos.
UTN - Facultad Regional Resistencia.

## Grupo B22 - Comisión K1.2

- Juan Pablo LENAIN
- Joshua David LEZCANO GENES
- Alejandro Manassero
- Ignacio Ojeda
- Martin Gabriel RIVAS

## Descripción y reglas

El programa simula por consola ensayos de la nave Orion en una órbita terrestre
baja. Parte de una altura de 192 km y una masa de 33000 kg. Permite cambiar esos
datos y calcular la velocidad orbital, el período, la aceleración centrípeta
y la fuerza gravitatoria, que actúa como fuerza centrípeta.

Desde el menú se puede configurar la órbita, ver los cálculos, iniciar ensayos,
consultar el reporte y mostrar las fórmulas.

Cada ciclo tiene hasta tres ensayos. En cada uno se puede observar sin pulso,
aplicar el pulso de la consigna o ingresar otra aceleración y duración.
El objetivo es completar los tres con un desvío de hasta 100 m por ensayo.
Ese límite es una regla del juego, no una condición real de estabilidad orbital.
Cada ensayo comienza desde la misma órbita; los pulsos no se acumulan.

El pulso calcula un desvío local aproximado, tomando una dirección perpendicular
a la velocidad inicial. Con 0,5 m/s² durante 10 s da 25 m de desvío y 5 m/s
de cambio lateral de velocidad. No se calcula la nueva órbita completa.

El reporte muestra los resultados y cuántos ensayos quedaron dentro del límite.
Se puede finalizar antes de completar los tres. Los datos se conservan solamente
mientras el programa está abierto. Si una entrada es incorrecta, se vuelve a pedir.

## Compilación y ejecución

Necesitamos GCC instalado. Abrimos una terminal en la carpeta del proyecto.

En Linux:

```sh
make
./artemis
```

Si no tenemos Make:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c artemis.c validaciones.c -o artemis -lm
./artemis
```

En Windows, con GCC de MinGW-w64 instalado, desde PowerShell:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c artemis.c validaciones.c -o artemis.exe -lm
.\artemis.exe
```

La versión fue probada en Linux. `make clean` borra el ejecutable en ese sistema.

## Organización

- `main.c`: menú y comienzo del programa.
- `artemis.h`: constantes, estructuras y declaraciones de funciones.
- `artemis.c`: cálculos, ensayos y reporte.
- `validaciones.c` y `validaciones.h`: ingreso y validación de datos.

## Uso de inteligencia artificial

Usamos ChatGPT/Codex/Claude como apoyo para analizar la consigna, obtener una propuesta
inicial de código y documentación, y preparar casos de prueba. Pedimos una
solución de nivel inicial y una división de los aportes entre los cinco.

Nuestras consultas fueron sobre cómo resolver el escenario 2 con funciones y
arreglos sencillos, comprobar los requisitos y simplificar la compilación
y la documentación.

La versión preparada con esa asistencia está separada en módulos, usa un arreglo
fijo y no necesita memoria dinámica. Cuenta con comprobaciones de compilación,
cálculos, entradas inválidas y reportes.

## Revisión del equipo

Nos repartimos las siguientes comprobaciones.

- [x] Juan Pablo: comparar radio, velocidad y período con los cálculos de la consigna.
- [x] Joshua: probar letras, valores fuera de rango y coma decimal.
- [x] Alejandro: comprobar el pulso de 0,5 m/s² durante 10 s: 25 m y 5 m/s.
- [x] Ignacio: revisar el menú y los reportes vacíos, parciales y completos.
- [x] Martin: compilar desde una copia limpia y comprobar estas instrucciones.

## Video

Enlace al Google Drive: https://drive.google.com/drive/folders/1E4Tpw2opAdiH0vOtSvOII4WJQtQ_p2TE?usp=sharing
Link al Repositorio: https://github.com/joshualgdev/labC-B22-ARTEMIS
