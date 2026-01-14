
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

#include "DigrafoValorado.h" // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
/*@ <answer>
 
Optimización:  
En lugar de ejecutar Dijkstra para cada paquete, se ejecuta **una vez desde la oficina**
para obtener la ida a todas las casas y otra vez en el **grafo inverso** para obtener
la vuelta desde todas las casas a la oficina.

Coste: O((N + C) log N) por Dijkstra, total O(2 * (N + C) log N), mucho mejor
que ejecutar 2*P veces Dijkstra para P paquetes.

@ </answer> */

const int INF = numeric_limits<int>::max();

vector<int> DijkstraTodo(DigrafoValorado<int> const& g, int origen) {
    vector<int> dist(g.V(), INF);
    IndexPQ<int> pq(g.V());
    dist[origen] = 0;
    pq.update(origen, 0);

    while (!pq.empty()) {
        int v = pq.top().elem;
        int d = pq.top().prioridad;
        pq.pop();

        if (d > dist[v]) continue;

        for (auto a : g.ady(v)) {
            int w = a.hasta();
            int nuevo = dist[v] + a.valor();
            if (nuevo < dist[w]) {
                dist[w] = nuevo;
                pq.update(w, nuevo);
            }
        }
    }

    return dist;
}

bool resuelveCaso() {
    int N, C;
    cin >> N >> C;
    if (!cin) return false;

    DigrafoValorado<int> g(N);
    DigrafoValorado<int> gInv(N); // grafo invertido para calcular vuelta

    for (int i = 0; i < C; i++) {
        int v, w, x;
        cin >> v >> w >> x;
        v--; w--; // ajustar a 0-index
        g.ponArista(AristaDirigida<int>(v, w, x));
        gInv.ponArista(AristaDirigida<int>(w, v, x)); // invertir arista
    }

    int O, P;
    cin >> O >> P;
    O--; // oficina a 0-index

    vector<int> paquetes(P);
    for (int i = 0; i < P; i++) {
        cin >> paquetes[i];
        paquetes[i]--; // ajustar a 0-index
    }

    // Dijkstra desde la oficina en el grafo original -> ida
    vector<int> distIda = DijkstraTodo(g, O);

    // Dijkstra desde la oficina en el grafo invertido -> vuelta
    vector<int> distVuelta = DijkstraTodo(gInv, O);

    int total = 0;
    for (int destino : paquetes) {
        if (distIda[destino] == INF || distVuelta[destino] == INF) {
            cout << "Imposible\n";
            return true;
        }
        total += distIda[destino] + distVuelta[destino];
    }

    cout << total << "\n";
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
