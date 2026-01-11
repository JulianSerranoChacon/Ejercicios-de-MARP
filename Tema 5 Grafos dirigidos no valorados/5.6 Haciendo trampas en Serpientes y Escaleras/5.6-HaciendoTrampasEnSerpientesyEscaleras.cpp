
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void añadeTirada(Digrafo const& g,std::vector<bool> &visit,std::queue<int> &q, int k, int v){
    for (int i = 0; i<k; i++){
        int casilla = v+i;
        if(casilla < g.V() && !visit[casilla]){
            q.push(casilla);
            visit[casilla] = true;
        }
    }
}


void bfs(int origen, int destino, Digrafo const& g, int K, std::vector<int> &dist) {
    std::queue<int> q;
    dist[origen] = 0;
    q.push(origen);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (v == destino) return; // parar cuando llegamos a destino

        // Movimientos con el dado
        for (int d = 1; d <= K; ++d) {
            int w = v + d;
            if (w >= g.V()) w = g.V() - 1; // no pasarse del final
            // aplicamos serpiente/escalera si existe
            if (!g.ady(w).empty()) w = g.ady(w)[0]; // cada vértice solo tiene un extremo
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                q.push(w);
            }
        }
    }
}

int resuelveTablero(Digrafo const& g, int K) {
    std::vector<int> dist(g.V(), -1); // dist[v] = mínimo número de movimientos a v
    bfs(1, g.V() - 1, g, K, dist);
    return dist[g.V() - 1];
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, K, S, E;
    cin >> N >> K >> S >> E;
	if (N == 0 && K == 0 && S == 0 && E == 0)
		return false;

    Digrafo g((N * N)+1);
    int v, w;
    for (int i = 0; i < S+E;i++){
        cin >> v >> w;
        g.ponArista(v,w);
    }

	// resolver el caso posiblemente llamando a otras funciones
    int sol = resuelveTablero(g,K);
	// escribir la solución
    cout << to_string(sol) << "\n";

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
