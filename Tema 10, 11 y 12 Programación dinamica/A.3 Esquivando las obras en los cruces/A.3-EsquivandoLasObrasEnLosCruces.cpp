
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
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

EntInf devolverNCaminos(int N, int M, const Matriz<char>& Mat){
    vector<EntInf> sol(M, 0);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){

            if(Mat[i][j] == 'X') {
                sol[j] = 0;   // no hay caminos aquí
            }
            else if(i == 0 && j == 0) {
                sol[j] = 1;   // inicio
            }
            else if(i == 0) {
                sol[j] = sol[j-1];  // primera fila
            }
            else if(j == 0) {
                sol[j] = sol[j];     // primera columna (se mantiene o 0 si bloqueado)
            }
            else {
                sol[j] = sol[j] + sol[j-1];
            }
        }
    }

    return sol[M-1];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N,M;
	cin >> N >> M;

	Matriz<char> Mat(N,M);
	if (!std::cin)  // fin de la entrada
		return false;

		
	char c;
	for(int i = 0; i < N; i++){
		for(int j= 0; j < M; j++){
			cin >> c;
			Mat[i][j] = c;
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	EntInf sol = devolverNCaminos(N,M,Mat);
	sol = (sol != Infinito) ? sol : 0;
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
