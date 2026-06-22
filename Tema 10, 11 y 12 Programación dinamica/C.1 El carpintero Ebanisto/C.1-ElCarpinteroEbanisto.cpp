
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#include <vector>
#include <algorithm>

using namespace std;

int cortaMaderas(vector<int> const& cortes_orig, int L) {
    // 1. Creamos un nuevo vector incluyendo los extremos 0 y L
    vector<int> cortes;
    cortes.push_back(0);
    for (int c : cortes_orig) {
        cortes.push_back(c);
    }
    cortes.push_back(L);
    
    int n = cortes.size(); // n ahora es N + 2
    
    // matrices[i][j] guardará el coste mínimo para hacer todos los cortes entre i y j
    // Inicializado a 0 (los casos base donde j = i + 1 no requieren cortes y valen 0)
    vector<vector<int>> matrices(n, vector<int>(n, 0));
    int INF = 1e9; // Un valor lo suficientemente grande

    // d es la distancia entre los índices i y j
    for (int d = 2; d < n; ++d) { 
        for (int i = 0; i < n - d; ++i) { 
            int j = i + d;
            matrices[i][j] = INF;
            
            // Probamos todos los posibles cortes intermedios k entre i y j
            for (int k = i + 1; k < j; ++k) {
                int coste_actual = matrices[i][k] + matrices[k][j] + 2 * (cortes[j] - cortes[i]);
                if (coste_actual < matrices[i][j]) {
                    matrices[i][j] = coste_actual;
                }
            }
        }
    }
    
    // El resultado final está en la celda que representa desde el extremo 0 al extremo L
    return matrices[0][n - 1];
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int L, N;
    cin >> L >> N;  
    
	if (L==N && L==0)
		return false;

    vector<int> cortes(N);

    for(int i = 0; i<N; i++)
        cin >> cortes[i];

    
	// resolver el caso posiblemente llamando a otras funciones
    int sol = cortaMaderas(cortes,L);
	// escribir la solución
    cout << sol << "\n";
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
