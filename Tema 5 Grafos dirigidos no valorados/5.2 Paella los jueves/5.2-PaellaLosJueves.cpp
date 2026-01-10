
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

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

void dfs(int v, Digrafo const& g, vector<bool>& visited) {
    visited[v] = true;
    for (int w : g.ady(v)) {
        if (!visited[w])
            dfs(w, g, visited);
    }
}


int resuelveRuta(Digrafo const & g, Digrafo const& gi, int origen, int destino) {
    vector<bool> desdeOrigen(g.V(), false);
    vector<bool> hastaDestino(g.V(), false);

    dfs(origen, g, desdeOrigen);

    if (!desdeOrigen[destino]) 
		return g.V() * 2; // IMPOSIBLE

    dfs(destino, gi, hastaDestino);

    int cont = 0;
    for (int v = 0; v < g.V(); v++) {
        if (v != origen && v != destino && desdeOrigen[v] && hastaDestino[v]) 
		{
            cont++;
        }
    }

    return cont;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	//nrestaurantes y naristas
	int N,A;
	cin >> N >> A;
	if (!std::cin)  // fin de la entrada
		return false;

	int v,w;
	Digrafo g(N+1);
	for (int i = 0; i<A; i++){
		cin >> v >> w;
		g.ponArista(v,w);
	}

	Digrafo gi = g.inverso();

	//Consultas
	int Q;
	cin >> Q;
	for (int i = 0; i<Q;i++){
		cin >> v >> w;
		int sol= resuelveRuta(g,gi,v,w);
		sol > N? cout << "IMPOSIBLE\n" : cout << to_string(sol) << "\n" ;
	}
	cout << "---" << "\n";
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
