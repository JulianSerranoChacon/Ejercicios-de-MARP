
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

#include "Matriz.h" // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

EntInf BuscarMenor( Matriz<EntInf> const& G){
int V = G.numfils();
    Matriz<EntInf> C = G;

    // Algoritmo de Floyd-Warshall con control de Infinito
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // Solo sumamos si ambos caminos intermedios existen (no son Infinito)
                if (C[i][k] != Infinito && C[k][j] != Infinito) {
                    auto temp = C[i][k] + C[k][j];
                    if (temp < C[i][j]) {
                        C[i][j] = temp;
                    }
                }
            }
        }
    }

    // Buscamos el grado de separación máximo
    EntInf maxDist = 0;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                if (C[i][j] == Infinito) {
                    return Infinito; 
                }
                if (C[i][j] > maxDist) {
                    maxDist = C[i][j];
                }
            }
        }
    }

    return maxDist;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, A;
    cin >> N >> A;
	if (!std::cin)  // fin de la entrada
		return false;

    Matriz<EntInf> G(N,N,Infinito);

    string desde, hasta;
    unordered_map<string,int> nombres;
    int id = 0;
    for(int i = 0; i < A; ++i){
        cin >> desde >> hasta;
        if(!nombres.count(desde)){
            nombres.emplace(desde,id);
            ++id;
        }
        if(!nombres.count(hasta)){
            nombres.emplace(hasta,id);
            ++id;
        }

        G[nombres[desde]][nombres[hasta]] = 1;
        G[nombres[hasta]][nombres[desde]] = 1;
    }
	// resolver el caso posiblemente llamando a otras funciones
    EntInf sol = BuscarMenor(G);
	// escribir la solución
    sol == Infinito ? cout << "DESCONECTADA\n" : cout << sol << "\n";
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
