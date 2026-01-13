
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

Para resolver el problema se modela el laberinto como un grafo dirigido y ponderado,
donde las celdas son los vértices y los pasadizos aristas con peso igual al tiempo de
recorrido. Como todos los ratones siguen el camino mínimo hasta la salida, en lugar
de ejecutar un algoritmo de caminos mínimos desde cada celda, se invierten las aristas
del grafo y se aplica el algoritmo de Dijkstra una única vez desde la celda de salida S.
De este modo se obtiene, para cada celda, el tiempo mínimo necesario para llegar a la
salida. Finalmente, se cuentan aquellas celdas cuyo tiempo mínimo es menor o igual
que el límite T.

El coste temporal del algoritmo es O((N + P) · log N), donde N es el número de celdas
y P el número de pasadizos, debido al uso de una cola de prioridad indexada en Dijkstra.
El coste en memoria es O(N + P) para almacenar el grafo y las estructuras auxiliares.

@ </answer> */



// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
const int INF = numeric_limits<int>::max();

int contarRatones(const DigrafoValorado<int>& g, int S, int T) {
    vector<int> dist(g.V(), INF);
    IndexPQ<int> pq(g.V());
    vector<bool> contado(g.V(), false);
    int ratones = 0;

    dist[S] = 0;
    pq.push(S, 0);

    while (!pq.empty()) {
        int v = pq.top().elem;
        int time = pq.top().prioridad;
        pq.pop();

        if (time != dist[v]) 
            continue;
            
        if(time > T) 
            break;


        if (dist[v] <= T && !contado[v] && v != S) 
        {
            ratones++;
            contado[v] = true;
        }

        for (auto a : g.ady(v)) {
            int w = a.hasta();
            if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor();
                pq.update(w, dist[w]);
            }
        }
    }
    return ratones;
}


bool resuelveCaso() {
	// leer los datos de la entrada
    int N, S, T, P;
    cin >> N >> S >> T >> P;
	if (!std::cin)  // fin de la entrada
		return false;

    DigrafoValorado<int> g(N+1);
    int v, w, x; 
    for (int i = 0; i < P; i++){
        cin >> v >> w >> x;
        g.ponArista(AristaDirigida<int>(v,w,x));
    }

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    cout << contarRatones(g.inverso(), S, T) << "\n";

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
