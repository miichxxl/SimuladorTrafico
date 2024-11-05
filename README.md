# Simulación de Tráfico en una Intersección

Este proyecto es una simulación de tráfico en una intersección entre dos calles (Calle 50 y Marbella). El programa utiliza hilos para simular el comportamiento de semáforos en una intersección, controlando el flujo de vehículos en ambas calles en función del tiempo de luz verde y roja, y de la cantidad de autos que pueden pasar por segundo.

## Requisitos

- Compilador de C++: Este programa requiere un compilador de C++ compatible con la biblioteca estándar (`std`) y el manejo de hilos.
- Rand Function: La simulación utiliza la función `rand()` para simular el número aleatorio de autos que pueden pasar por segundo.
- Compilación y Ejecución: Asegúrate de tener un compilador como `g++` instalado para compilar y ejecutar el programa.

## Configuración del Proyecto

Los siguientes parámetros de configuración están definidos en el programa:

- duracionLuzVerde: Tiempo (en segundos) durante el cual la luz permanece en verde para una calle.
- duracionLuzRoja: Tiempo (en segundos) durante el cual la luz permanece en rojo para una calle.
- autosPorSegundo: Número máximo de autos que pueden cruzar por segundo cuando el semáforo está en verde.

En este ejemplo, estos valores están definidos en el `main` como:
<

int duracionLuzVerde = 18; // Duración de la luz verde
int duracionLuzRoja = 25;  // Duración de la luz roja
int autosPorSegundo = 30;  // Cantidad de autos que pueden cruzar

>

## Estructura del Código

### Clases y Estructuras

- Auto: Representa un automóvil con un identificador único y un tiempo de entrada.
- Interseccion: Clase principal que maneja la simulación de la intersección. Tiene dos colas de autos (una para cada calle) y métodos para simular el comportamiento del semáforo.

### Métodos Principales

- llenarCola: Llena la cola de autos en una calle con una cantidad específica de autos.
- manejarSemaforo: Maneja el cambio de semáforo de una calle en un hilo separado, permitiendo a los autos pasar cuando el semáforo está en verde y deteniéndolos en rojo.
- simularTrafico: Configura y lanza los hilos para manejar ambas calles y realiza la simulación completa.

## Ejecución del Programa

1. **Compilar** el programa con el siguiente comando:

    g++ -o simulacion_trafico simulacion_trafico.cpp -pthread
  
2. **Ejecutar** el programa:

    ./simulacion_trafico

## Ejemplo de Salida

Durante la ejecución, el programa muestra el estado del semáforo y la cantidad de autos que pasan en cada cambio de luz. La simulación continuará hasta que no queden autos en ninguna de las colas.

🟢 [INICIO] Semáforo en VERDE para Calle 50 - Tiempo: 18 segundos
🚗 Pasaron 20 autos en Calle 50.

🔴 [INICIO] Semáforo en ROJO para Calle 50 - Tiempo: 25 segundos

❌ No quedan autos en Calle 50.

## Notas

- Este programa utiliza números aleatorios para simular la cantidad de autos que cruzan por segundo. Si deseas modificar el número de autos, ajusta el parámetro `autosPorSegundo`.
- El tiempo de luz verde y roja también se puede ajustar directamente en el código en el `main`.

## Mejoras Posibles

Algunas posibles mejoras al programa podrían incluir:

- Ajuste dinámico de los tiempos de semáforo en función del tráfico.
- Visualización gráfica del flujo de autos en la intersección.
- Implementación de una interfaz de usuario para configurar los parámetros.