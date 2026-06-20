
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int comerCubosRec(const vector<int>& cubos, int i, int j, Matriz<int>& mat) {
    if (i > j) return 0;
    if (i == j) return cubos[i];
    if (mat[i][j] != -1) return mat[i][j];
    
    // Opción Izquierda
    int ni = i + 1, nj = j;
    if (ni <= nj) {
        if (cubos[ni] > cubos[nj]) ni++;
        else nj--;
    }
    int izq = cubos[i] + comerCubosRec(cubos, ni, nj, mat);
    
    // Opción Derecha
    ni = i; nj = j - 1;
    if (ni <= nj) {
        if (cubos[ni] > cubos[nj]) ni++;
        else nj--;
    }
    int der = cubos[j] + comerCubosRec(cubos, ni, nj, mat);
    
    return mat[i][j] = max(izq, der);
}

int comerCubos(const vector<int>& cubos, int N) {
    Matriz<int> mat(N, N, -1);
    return comerCubosRec(cubos, 0, N - 1, mat);
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;
	if (N == 0)
		return false;

    vector<int> cubos(N);

    for(int i = 0; i<N; i++)
        cin >> cubos[i];
    
	// resolver el caso posiblemente llamando a otras funciones
    int sol = comerCubos(cubos,N);
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
