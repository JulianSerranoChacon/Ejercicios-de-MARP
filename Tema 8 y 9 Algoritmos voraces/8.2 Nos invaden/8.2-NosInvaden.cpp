
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

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
    int N;
    cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
    
    PriorityQueue <int,less<int>> enemy;
    PriorityQueue <int,less<int>> defense;
    int unidades;
    for(int i = 0; i<N;i++){
        cin >> unidades;
        enemy.push(unidades);
    }

    for(int i = 0; i<N;i++){
        cin >> unidades;
        defense.push(unidades);
    }

	// resolver el caso posiblemente llamando a otras funciones
    int d,e,sol;
    sol = 0;
    while (!defense.empty() && !enemy.empty())
    {
        d = defense.top();
        e = enemy.top();
        
        if(d >= e){
            sol++;
            defense.pop();
            enemy.pop();
        }
        else{
            defense.pop();
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
