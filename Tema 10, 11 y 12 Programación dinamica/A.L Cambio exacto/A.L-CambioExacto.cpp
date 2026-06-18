
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


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

pair<int,EntInf> Pago(int N,int C, const vector<int> &M){
    int pago = 0; 
    EntInf nmonedas = 0;

    int MAX = 0;
    for (int x : M) MAX += x;
    
    vector<EntInf> sol(MAX + 1, Infinito);
    sol[0] = 0;

    for(int i = 0; i < N; i++){
        int curr = M[i];

        for(int s = MAX; s >= curr; s--){
            sol[s] = min(sol[s], sol[s - curr] + 1);
        }
    }

    // buscar mejor solución >= C
    for(int s = C; s <= MAX; s++){
        if(sol[s] != Infinito){
            pago = s;
            nmonedas = sol[s];
            break;
        }
    }

    return {pago, nmonedas};
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int C, N;
    cin >> C >> N;

	if (!std::cin)  // fin de la entrada
		return false;

    vector<int> M(N);
    for(int i = 0; i<N;i++){
        cin >> M[i]; 
    }

	// resolver el caso posiblemente llamando a otras funciones
    pair<int,EntInf> sol = Pago(N,C,M);
	// escribir la solución
    cout << sol.first << " " << sol.second << "\n";

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
