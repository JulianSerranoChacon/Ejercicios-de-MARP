
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#include "Grafo.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// BFS para calcular distancias mínimas desde un nodo origen
void bfsDist(int origen, Grafo const& g, vector<int>& dist) {
    int N = g.V();
    dist.assign(N, -1); // -1 indica no alcanzable
    queue<int> q;
    dist[origen] = 0;
    q.push(origen);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : g.ady(v)) {
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                q.push(w);
            }
        }
    }
}

// Calcula el mínimo gasto total desde las casas de Alex y Lucas al trabajo
int minimoGasto(Grafo const& g, int casaA, int casaL, int trabajo) {
    vector<int> distA, distL, distT;

    bfsDist(casaA, g, distA);
    bfsDist(casaL, g, distL);
    bfsDist(trabajo, g, distT);

    int minGasto = g.V() * 3; // inicial grande
    for (int v = 0; v < g.V(); v++) {
        if (distA[v] != -1 && distL[v] != -1 && distT[v] != -1) {
            int gasto = distA[v] + distL[v] + distT[v];
            minGasto = min(minGasto, gasto);
        }
    }
    return minGasto;
}


bool resuelveCaso() {
	// leer los datos de la entrada
    int N, C, A, L, T;
    cin >> N >> C >> A >> L >> T;
	if (!std::cin)  // fin de la entrada
		return false;
    // Crear grafo y leer aristas
    Grafo g(N);
    for (int i = 0; i < C; i++) {
        int u, v;
        cin >> u >> v;
        g.ponArista(u - 1, v - 1); // restamos 1 para usar indices 0-based
    }
	// resolver el caso posiblemente llamando a otras funciones
    int gasto = minimoGasto(g, A - 1, L - 1, T - 1); // indices 0-based
	// escribir la solución
    cout << gasto << "\n";

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
