
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
/*CON BFS 
#include <queue>

int bfsComponente(int origen, Grafo const& g, int N, vector<bool>& visited, vector<int> &compSize) {
    queue<int> q;
    q.push(origen);
    visited[origen] = true;

    int size = 0;
    vector<int> nodosComponente;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        // Contamos solo nodos usuario (<= N)
        if (v <= N) size++;

        nodosComponente.push_back(v);

        for (int w : g.ady(v)) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
    }

    // Asignamos tamaño total a todos los nodos de la componente
    for (int nodo : nodosComponente) {
        compSize[nodo] = size;
    }

    return size;
}

void obtenSolucion(vector<int> &sol, int N, Grafo const& g) {
    vector<bool> visited(g.V(), false);

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            bfsComponente(i, g, N, visited, sol);
        }
    }
}
*/

int dfsComponente(int v, Grafo const& g, int N, vector<bool>& visited, vector<int> &compSize, vector<int>& nodosComponente) {
    visited[v] = true;

    // Contamos solo los nodos de usuarios, no los nodos grupo
    int size = (v <= N) ? 1 : 0;

    nodosComponente.push_back(v);

    for (int w : g.ady(v)) {
        if (!visited[w]) {
            size += dfsComponente(w, g, N, visited, compSize, nodosComponente);
        }
    }

    return size;
}

void obtenSolucion(vector<int> &sol, int N, Grafo const& g) {
    vector<bool> visited(g.V(), false);

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            vector<int> nodosComponente;   // nodos de la componente actual
            int size = dfsComponente(i, g, N, visited, sol, nodosComponente);
            // Asignar el tamaño total a todos los nodos de la componente
            for (int nodo : nodosComponente) {
                sol[nodo] = size;
            }
        }
    }
}

bool resuelveCaso() {
	// leer los datos de la entrada

    int N, M;
    cin >> N >> M;
	if (!std::cin)  // fin de la entrada
		return false;

    Grafo grafo(N+M+1);
    //Los grupos empiezan en el vertice N+1 y tienen como adyacentes a los usuarios, los usuarios están en los vertices de sus propios ids
    for (int i = 0 ; i < M; i++){
        int groupID = N + 1 + i;
        int nusers;
        cin >> nusers;
        for (int j = 0; j< nusers; j ++)
        {
            int user;
            cin >> user;
            grafo.ponArista(user,groupID);
        }
        
    }
    //grafo.print();
	// resolver el caso posiblemente llamando a otras funciones
    vector<int> sol(grafo.V(),0);
    obtenSolucion(sol,N,grafo);
	// escribir la solución
    for(int i = 1; i<=N;i++){
        cout << to_string(sol[i]) << " ";
    }
    cout << "\n";
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
