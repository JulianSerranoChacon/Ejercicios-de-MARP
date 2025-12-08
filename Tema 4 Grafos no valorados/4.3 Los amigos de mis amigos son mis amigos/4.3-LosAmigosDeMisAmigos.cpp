/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

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
void grupoMasGrandeRec(const Grafo & g,vector<bool>& visited, int V, int& ac){
    if(visited[V])
        return;

    ++ac;
    visited[V] = true;
    
    for(int i = 0; i < g.ady(V).size(); i++){
        int next = g.ady(V)[i];
        if(!visited[next])
            grupoMasGrandeRec(g,visited,next,ac);
    }
}

unsigned int grupoMasGrande(const Grafo & g){
    int max = 0;
    vector<bool>visited(g.V(),false);

    for(int i = 0; i < g.V(); i++){
        int ac = 0;
        grupoMasGrandeRec(g,visited,i,ac);
        max = std::max(max, ac);
    }

    return max;
}

void resuelveCaso() {
	// leer los datos de la entrada
    unsigned int n, m,a,b;

    cin >> n >> m;

    Grafo g(n+1);
    for(int j = 0; j < m; j++){
        cin >> a >> b;
        g.ponArista(a,b);
    }

    // resolver el caso posiblemente llamando a otras funciones
    unsigned int sol = grupoMasGrande(g);

    // escribir la solución
    cout << sol << "\n";
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
