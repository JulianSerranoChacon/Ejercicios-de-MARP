
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, L;
    cin >> N >> L;
	if (!std::cin)  // fin de la entrada
		return false;

    PriorityQueue pq;
    int pos;
    for(int i = 0; i<N ; i++){
        cin >> pos;
        pq.push(pos);
    }

	// resolver el caso posiblemente llamando a otras funciones
    int act, sol, top;
    act = 0;
    sol = 0;
    while (!pq.empty())
    {
        top = pq.top();
        pq.pop();

        if(act == 0 || L < top - act){
            act = top;
            sol ++;
        }
    }
    cout << to_string(sol) << "\n";

	// escribir la solución

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
