
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <algorithm>

#include "IndexPQ.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

Esta solución calcula el canal más visto durante cada minuto de una franja horaria usando dos colas de prioridad indexadas (`IndexPQ`):

1. `pq` mantiene la audiencia actual de cada canal, permitiendo identificar rápidamente el canal líder en cualquier momento usando `top()`.
2. `sol` acumula los minutos durante los cuales cada canal ha sido líder. Cada vez que se procesa un cambio de audiencia (una actualización), se calcula el intervalo de tiempo desde la actualización anterior y se suma al canal que estaba liderando en ese intervalo.

El algoritmo procede así:
- Se leen los datos iniciales de audiencia y se insertan en ambas colas.
- Para cada actualización, se determina el canal líder antes de aplicar la actualización y se acumulan los minutos de liderazgo.
- Se actualizan las audiencias indicadas en la línea de actualización.
- Después de procesar todas las actualizaciones, se suma el tiempo restante desde la última actualización hasta el final de la franja al canal líder en ese último intervalo.
- Finalmente, se imprime cada canal que haya sido líder al menos un minuto, ordenando por minutos de liderazgo (de mayor a menor) y en caso de empate por número de canal (menor a mayor), usando la propia `IndexPQ` con un comparador personalizado.

Complejidad:
- Cada actualización y cada operación sobre `IndexPQ` es O(log C), donde C es el número de canales.
- Por tanto, el coste total del algoritmo es O((C + N) log C), siendo N el número de actualizaciones. Esto es eficiente incluso para el máximo tamaño de los casos de prueba (C ~ 10^6, N <= D).

Ventajas:
- Se asegura que nunca se pierda un minuto de liderazgo.
- Se respeta el orden de salida requerido sin necesidad de un sort adicional fuera de la `IndexPQ`.
- Es robusto frente a cualquier número de actualizaciones y audiencias, siempre que los datos cumplan las restricciones del problema.

@ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Comp
{
    bool operator()(pair<int,int> const& a, pair<int,int> const& b) const {
        return a.second > b.second || ((a.second == b.second) && a.first < b.first); // max-heap
    }
};


bool resuelveCaso() {
	// leer los datos de la entrada
    int D, C, N;
    cin >> D >> C >> N;
	if (!std::cin)  // fin de la entrada
		return false;

    IndexPQ<pair<int,int>,Comp> sol(C);
    IndexPQ<int,greater<int>> pq(C);
    int audiencia;
    //creamos los canales en la cola con valores iniciales
    for(int i = 0; i<C;i++){
        cin >> audiencia;
        pq.push(i,audiencia);
        sol.push(i,pair<int,int>(i,0));
    }

    //resolvemmos las actualizaciones
    long canal, tiempoactual, tiempoAnterior, franja, top, ant;
    tiempoAnterior = 0;
    for(int i = 0; i < N; i++){
        cin >> tiempoactual;
        cin >> canal;
        franja = tiempoactual - tiempoAnterior;
        tiempoAnterior = tiempoactual;

        top = pq.top().elem;

        ant = sol.priority(top).second;
        sol.update(top, pair<int,int>(top,ant+franja));
        
        while (canal != -1)
        {
            cin >> audiencia;
            pq.update(canal - 1,audiencia);
            cin >> canal;
        }
    }

    franja = D - tiempoAnterior;
    top = pq.top().elem;
    ant = sol.priority(top).second;
    sol.update(top, pair<int,int>(top,ant+franja));
    
    while (!sol.empty())
    {
        pair<int,int> final = sol.top().prioridad;
        sol.pop();
        if(final.second != 0)
            cout << to_string(final.first + 1) << " " << to_string(final.second) << "\n";
    }
    
    cout << "---\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
