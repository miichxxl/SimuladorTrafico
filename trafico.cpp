#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>     // Para rand()
#include <iostream>

using namespace std;

// Estructura que representa un auto en la simulación de tráfico
struct Auto {
    int id;
    int tiempoEntrada;
};

// Clase para representar las dos calles
class Interseccion {
public:
    queue<Auto> calle50;           // Cola para autos de "Calle 50"
    queue<Auto> marbella;          // Cola para autos de "Marbella"
    int duracionLuzVerde;          // Duración del semáforo en verde 
    int duracionLuzRoja;           // Duración del semáforo en rojo 
    int autosPorCiclo;             // Máximo de autos que pueden pasar luz verde
    int tiempoTotal = 0;           // Tiempo total de simulación

    // Constructor
    Interseccion(int duracionLuzVerde, int duracionLuzRoja, int autosPorCiclo) 
        : duracionLuzVerde(duracionLuzVerde), duracionLuzRoja(duracionLuzRoja), autosPorCiclo(autosPorCiclo) {}

    // Simula el tráfico en la intersección
    void simularTrafico(int totalAutosCalle50, int totalAutosMarbella) {
        llenarCola(calle50, totalAutosCalle50);
        llenarCola(marbella, totalAutosMarbella);

        // Lanzar hilos para las dos calles
        thread t1(&Interseccion::manejarSemaforo, this, ref(calle50), "Calle 50", true);
        thread t2(&Interseccion::manejarSemaforo, this, ref(marbella), "Marbella", false);

        // Unir los hilos
        t1.join();
        t2.join();

        cout << "\nSimulación de tráfico completada.\n";
        cout << "⏱️ Tiempo total de simulación: " << tiempoTotal << " segundos.\n";
    }

private:
    // Llena la cola de autos en una calle con el número de autos especificado
    void llenarCola(queue<Auto>& calle, int numAutos) {
        for (int i = 1; i <= numAutos; ++i) {
            calle.push({i, 0});
        }
    }

    // Maneja el semáforo de una calle en un hilo
    void manejarSemaforo(queue<Auto>& calle, const string& nombreCalle, bool enVerde) {
        while (!calle.empty()) {
            int autosPasados = 0;

            if (enVerde) {
                cout << "\n🟢 [INICIO] Semáforo en VERDE para " << nombreCalle << " - Tiempo: " << duracionLuzVerde << " segundos\n";

                // Permite que pasen autos hasta alcanzar el máximo permitido en un ciclo
                for (int i = 0; i < duracionLuzVerde && autosPasados < autosPorCiclo && !calle.empty(); ++i) {
                    int autosEnEsteSegundo = min(rand() % autosPorCiclo + 1, autosPorCiclo - autosPasados); // Máximo de autos restantes permitidos en este ciclo
                    for (int j = 0; j < autosEnEsteSegundo && !calle.empty(); ++j) {
                        calle.pop();
                        autosPasados++;
                    }
//                   this_thread::sleep_for(chrono::seconds(1)); // Simula el paso en tiempo real
                }
                cout << "🚗 Pasaron " << autosPasados << " autos en " << nombreCalle << ".\n";
                tiempoTotal += duracionLuzVerde; // Suma el tiempo de luz verde al tiempo total
            } else {
                cout << "\n🔴 [INICIO] Semáforo en ROJO para " << nombreCalle << " - Tiempo: " << duracionLuzRoja << " segundos\n";
//                this_thread::sleep_for(chrono::seconds(duracionLuzRoja));
                tiempoTotal += duracionLuzRoja; // Suma el tiempo de luz roja al tiempo total
            }

            enVerde = !enVerde; // Cambia el semáforo
        }
        cout << "❌ No quedan autos en " << nombreCalle << ".\n";
    }
};

// MAIN
int main() {
 //   srand(time(0)); // Inicializa la semilla para números aleatorios

    int duracionLuzVerde = 18; // Duración de la luz verde
    int duracionLuzRoja = 25;  // Duración de la luz roja
    int autosPorCiclo = 25;    // Máximo de autos para cruzaer la luz verde

    // Crear la intersección con los parámetros especificados
    Interseccion interseccion(duracionLuzVerde, duracionLuzRoja, autosPorCiclo);

    // Simular el tráfico en la intersección, los 2500 son de Calle 50 y los 4000 de Marbella  
    interseccion.simularTrafico(1500, 2000);

    return 0;
}
