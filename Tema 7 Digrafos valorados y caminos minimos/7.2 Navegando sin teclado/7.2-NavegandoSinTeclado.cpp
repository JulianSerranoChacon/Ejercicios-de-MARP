
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

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

const int INF = numeric_limits<int>::max();

void dijkstra(const DigrafoValorado<int>& g, int origen,
              vector<int>& dist, vector<int>& prev, vector<int> const& time) {

    dist.assign(g.V(), INF);
    prev.assign(g.V(), -1);

    IndexPQ<int> pq(g.V());

    dist[origen] = time[origen - 1];
    pq.push(origen, dist[origen]);


    while (!pq.empty()) {
        int v = pq.top().elem;
        pq.pop();

        for (auto a : g.ady(v)) {
            int w = a.hasta();
            int nuevo = dist[v] + a.valor() + time[w - 1];
            if (dist[w] > nuevo) 
            {
                dist[w] = nuevo;
                prev[w] = v;
                pq.update(w, dist[w]);
            }
        }
    }
}

vector<int> reconstruirCamino(int origen, int destino, const vector<int>& prev) {
    vector<int> camino;
    for (int v = destino; v != -1; v = prev[v])
        camino.push_back(v);

    reverse(camino.begin(), camino.end());

    if (camino.empty() || camino[0] != origen)
        camino.clear();

    return camino;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;
	if (N == 0)
		return false;

    DigrafoValorado<int> g(N+1);
    vector<int> time;
    int t;
    for(int i = 0; i < N; i++){
        cin >> t;
        time.push_back(t);
    }

    int M;
    cin >> M;
    int v, w;
    for(int i = 0; i < M; i++){
        cin >> v >> w >> t;
        g.ponArista(AristaDirigida(v,w,t));
    }


    vector<int> dist, prev;
	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    dijkstra(g, 1, dist, prev, time);
        auto camino = reconstruirCamino(1, N, prev);

        if (camino.empty()) {
            cout << "IMPOSIBLE\n";
        } else {
            cout << dist[N] << "\n";
        }

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
