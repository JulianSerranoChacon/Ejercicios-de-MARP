
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <numeric>

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


using LL = long long;
const LL INF = numeric_limits<LL>::max();

// Dijkstra sobre un grafo valorado
vector<LL> dijkstra(DigrafoValorado<LL> const& g, int s) {
    int N = g.V();
    vector<LL> dist(N, INF);
    IndexPQ<LL, less<LL>> pq(N);

    dist[s] = 0;
    pq.push(s, 0);

    while (!pq.empty()) {
        auto top = pq.top();
        int u = top.elem;
        LL d = top.prioridad;
        pq.pop();

        if (d > dist[u]) continue; // si es una entrada antigua, la ignoramos

        for (auto const& a : g.ady(u)) {
            int v = a.hasta();
            LL w = a.valor();
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.update(v, dist[v]);
            }
        }
    }

    return dist;
}

bool resuelveCaso() {
    int N, M;
    if (!(cin >> N >> M)) return false;

    DigrafoValorado<LL> g(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        LL c;
        cin >> u >> v >> c;
        u--; v--; // si la entrada está indexada desde 1
        g.ponArista({u, v, c});
        g.ponArista({v, u, c}); // grafos no dirigidos
    }

    // Calcular distancias mínimas desde la planta norte (0) y sur (N-1)
    vector<LL> distNorte = dijkstra(g, 0);
    vector<LL> distSur   = dijkstra(g, N - 1);

    vector<LL> diff; // diferencia coste norte - sur
    vector<LL> costeNorte, costeSur;
    for (int i = 1; i < N - 1; i++) {
        costeNorte.push_back(distNorte[i] * 2); // ida y vuelta
        costeSur.push_back(distSur[i] * 2);
        diff.push_back(costeNorte.back() - costeSur.back());
    }

    // Ordenamos pueblos según la diferencia
    vector<int> indices(N - 2);
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int a, int b) { return diff[a] < diff[b]; });

    LL total = 0;
    int k = (N - 2) / 2;
    for (int i = 0; i < k; i++) total += costeNorte[indices[i]];
    for (int i = k; i < N - 2; i++) total += costeSur[indices[i]];

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
