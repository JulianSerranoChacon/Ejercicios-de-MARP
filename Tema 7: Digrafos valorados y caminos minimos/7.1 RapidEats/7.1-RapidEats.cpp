
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
              vector<int>& dist, vector<int>& prev) {

    dist.assign(g.V(), INF);
    prev.assign(g.V(), -1);

    IndexPQ<int> pq(g.V());

    dist[origen] = 0;
    pq.push(origen, 0);

    while (!pq.empty()) {
        int v = pq.top().elem;
        pq.pop();

        for (auto a : g.ady(v)) {
            int w = a.hasta();
            if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor();
                prev[w] = v;
                pq.update(w, dist[w]);  // 👈 clave
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
    int N, C;
    cin >> N >> C;
    if (!cin) return false;

    DigrafoValorado<int> g(N + 1);

    for (int i = 0; i < C; i++) {
        int v, w, t;
        cin >> v >> w >> t;
        g.ponArista({v, w, t});
        g.ponArista({w, v, t}); // calles bidireccionales
    }

    int K;
    cin >> K;

    vector<int> dist, prev;

    for (int i = 0; i < K; i++) {
        int origen, destino;
        cin >> origen >> destino;

        dijkstra(g, origen, dist, prev);
        auto camino = reconstruirCamino(origen, destino, prev);

        if (camino.empty()) {
            cout << "NO LLEGA\n";
        } else {
            cout << dist[destino] << ": ";
            for (int j = 0; j < camino.size(); j++) {
                if (j > 0) cout << " -> ";
                cout << camino[j];
            }
            cout << "\n";
        }
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
