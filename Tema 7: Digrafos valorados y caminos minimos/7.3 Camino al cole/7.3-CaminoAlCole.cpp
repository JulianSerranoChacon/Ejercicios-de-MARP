
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
const int INF = std::numeric_limits<int>::max();

int Dijkstra(DigrafoValorado<int> const& g, int origen, int destino)
{
    int N = g.V();
    vector<int> dist(N, INF);
    vector<int> ways(N, 0);  // caminos mínimos hacia cada nodo
    IndexPQ<int> pq(N);

    dist[origen] = 0;
    ways[origen] = 1;
    pq.push(origen, 0);

    while (!pq.empty())
    {
        int v = pq.top().elem;
        int d = pq.top().prioridad;
        pq.pop();

        if (d > dist[v]) continue; // nodo obsoleto

        for (auto a : g.ady(v))
        {
            int w = a.hasta();
            int nuevo = dist[v] + a.valor();

            if (dist[w] > nuevo)
            {
                dist[w] = nuevo;
                ways[w] = ways[v];
                pq.update(w, dist[w]);
            }
            else if (dist[w] == nuevo)
            {
                ways[w] += ways[v];
            }
        }
    }

    return ways[destino];
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int N,C;
	cin >> N >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	DigrafoValorado<int> g(N+1);
	int v,w,d;
	for(int i = 0; i<C; i++){
		cin >> v >> w >> d;
		g.ponArista(AristaDirigida<int>(v,w,d));
		g.ponArista(AristaDirigida<int>(w,v,d));
	}

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << Dijkstra(g, 1, N) << "\n";

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
