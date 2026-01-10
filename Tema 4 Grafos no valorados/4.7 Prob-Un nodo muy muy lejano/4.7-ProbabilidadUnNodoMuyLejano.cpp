
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// BFS desde 'origen' considerando TTL, devuelve número de nodos alcanzables
int bfsTTL(int origen, int TTL, vector<vector<int>> const& adj) {
    int N = adj.size() - 1; // nodos numerados de 1 a N
    if (origen < 1 || origen > N) return 0; // nodo inexistente

    vector<int> dist(N + 1, -1);
    queue<int> q;

    dist[origen] = 0;
    q.push(origen);

    int alcanzados = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();

        if (dist[v] <= TTL)
            alcanzados++;

        for (int w : adj[v]) {
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                if (dist[w] <= TTL)
                    q.push(w);
            }
        }
    }

    return alcanzados;
}

// Leer las consultas y responderlas
void leerYResponderConsultas(vector<vector<int>> const& adj) {
    int K;
    cin >> K;
    int N = adj.size() - 1;
    for (int i = 0; i < K; i++) {
        int origen, TTL;
        cin >> origen >> TTL;

        int alcanzados = 0;
        if (origen >= 1 && origen <= N)
            alcanzados = bfsTTL(origen, TTL, adj);

        cout << N - alcanzados << "\n"; // nodos no alcanzables
    }
    cout << "---\n";
}

bool resuelveCaso() {
    int N, C;
    cin >> N;
    if (!cin) return false; // fin de entrada
    cin >> C;

    // Construir grafo
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < C; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Leer y responder consultas
    leerYResponderConsultas(adj);

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
