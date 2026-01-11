
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

// Devuelve los vecinos de x según las operaciones
Adys generaAdyacentes(int x, const vector<int>& a, const vector<int>& b, int M) {
    Adys res;
    for (int i = 0; i < a.size(); i++)
        res.push_back((a[i] * x + b[i]) % M);
    return res;
}

// BFS para mínimo número de jugadas usando vecinos implícitos
int bfs(Digrafo& g, int S, int T, const vector<int>& a, const vector<int>& b, int M) {
    vector<int> dist(M, -1);
    queue<int> q;

    dist[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (v == T) return dist[v];

        // Generar vecinos en este momento
        Adys ady = generaAdyacentes(v, a, b, M);

        for (int w : ady) {
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                g.ponArista(v, w); // Añadimos la arista al Digrafo
                q.push(w);
            }
        }
    }
    return -1;
}
bool resuelveCaso() {
	// leer los datos de la entrada
    int M, S, T;
    cin >> M >> S >> T;
	if (!std::cin)  // fin de la entrada
		return false;
    
    int N;
    cin >> N;

    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i];
    }

	// resolver el caso posiblemente llamando a otras funciones
    Digrafo g(M); // Grafo de M vértices
    cout << bfs(g,S, T, a, b, M) << "\n";
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
