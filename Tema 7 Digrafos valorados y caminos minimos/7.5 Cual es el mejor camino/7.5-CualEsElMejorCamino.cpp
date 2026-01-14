
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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
//@ <answer>void dijkstra(const DigrafoValorado<int>& g, int origen,
const int INF = numeric_limits<int>::max();

/* BFS: mínimo número de calles */
int bfs(const DigrafoValorado<int>& g, int origen, int destino) {
    vector<int> dist(g.V(), INF);
    queue<int> q;

    dist[origen] = 0;
    q.push(origen);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto a : g.ady(v)) {
            int w = a.hasta();
            if (dist[w] == INF) {
                dist[w] = dist[v] + 1;
                if (w == destino) return dist[w];
                q.push(w);
            }
        }
    }
    return dist[destino];
}

/* Dijkstra con doble criterio */
bool dijkstra(const DigrafoValorado<int>& g, int origen, int destino,
              int& distMin, int& edgesMin) {
    vector<int> dist(g.V(), INF);
    vector<int> edges(g.V(), INF);

    IndexPQ<int> pq(g.V());
    dist[origen] = 0;
    edges[origen] = 0;
    pq.push(origen, 0);

    while (!pq.empty()) {
        int v = pq.top().elem;
        int d = pq.top().prioridad;
        pq.pop();

        if (d > dist[v]) continue; // obsoleto

        for (auto a : g.ady(v)) {
            int w = a.hasta();
            int nd = dist[v] + a.valor();
            int ne = edges[v] + 1;

            if (nd < dist[w] || (nd == dist[w] && ne < edges[w])) {
                dist[w] = nd;
                edges[w] = ne;
                pq.update(w, dist[w]);
            }
        }
    }

    if (dist[destino] == INF) return false;
    distMin = dist[destino];
    edgesMin = edges[destino];
    return true;
}


bool resuelveCaso() {
	// leer los datos de la entrada
    int N , C;
    cin >> N >> C;
	if (!std::cin)  // fin de la entrada
		return false;
    
    DigrafoValorado<int> g(N+1);

    int v,w,x;
    for(int i = 0; i < C; i++){
        cin >> v >> w >> x;
        g.ponArista(AristaDirigida<int>(v, w, x)); // de v a w
        g.ponArista(AristaDirigida<int>(w, v, x)); // de w a v

    }

	// resolver el caso posiblemente llamando a otras funciones
    int K;
    cin >> K;
    for(int i = 0; i<K;i++){
        cin >> v >> w;
        int Emin = bfs(g, v, w);

        int distMin, edgesMin;
        if (!dijkstra(g, v, w, distMin, edgesMin)) 
        {
            cout << "SIN CAMINO\n";
        } else 
        {
            cout << distMin << " ";
            cout << (edgesMin == Emin ? "SI\n" : "NO\n");
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
