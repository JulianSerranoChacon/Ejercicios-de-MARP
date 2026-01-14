
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h" // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int ARM_Kruskal(GrafoValorado<int> const& g, int &coste, int aviones){
coste = 0;
    PriorityQueue<Arista<int>> pq;

    // Solo considerar aristas más baratas que un aeropuerto
    for (auto ar : g.aristas()) {
        if (ar.valor() < aviones) pq.push(ar);
    }

    ConjuntosDisjuntos cjtos(g.V());
    int numAristasUsadas = 0;

    while (!pq.empty()) {
        auto a = pq.top(); pq.pop();
        int v = a.uno(), w = a.otro(v);
        if (!cjtos.unidos(v, w)) {
            cjtos.unir(v, w);
            coste += a.valor();
            numAristasUsadas++;
        }
    }

    // Cada componente desconectada necesita un aeropuerto
    int aeropuertos = cjtos.num_cjtos() - 1; // 0 es índice “fantasma”
    coste += aeropuertos * aviones;

    return aeropuertos;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, M , A;
    cin >> N >> M >> A;
	if (!std::cin)  // fin de la entrada
		return false;

    GrafoValorado<int> g(N + 1);
    int ini, fin, precio;
    for(int i = 0; i < M; i++){
        cin >> ini >> fin >> precio;
        g.ponArista(Arista<int>(ini,fin,precio));
    }


	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    int coste;
    int aeropuertos = ARM_Kruskal(g,coste,A);
    cout << to_string(coste) << " " << to_string(aeropuertos) << "\n";

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
