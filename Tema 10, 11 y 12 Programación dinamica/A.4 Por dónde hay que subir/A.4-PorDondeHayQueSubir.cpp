
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

pair<int,int> subida(int N, const Matriz<int>& Mat){
    vector<int> sol(N);
    vector<int> prev(N);

    int izq = 0,der = 0;
    for(int i = 0; i < N;i++){
        for(int j = 0; j < N; j++){
            if(i == 0){
                sol[j] = Mat[0][j];
            }
            else if(i< N){
                if(j == 0){
                    izq = 0;
                    der = prev[j+1];
                }
                else if(j == N-1){
                    izq = prev[j-1];
                    der = 0;
                }
                else{
                    izq = prev[j-1];
                    der = prev[j+1];
                }

                sol[j] = Mat[i][j] + max(izq,max(prev[j],der));
            }
        }
        prev = sol;
    }

    int max = 0, inicio = 0,i = 0;

    while (i < sol.size())
    {
        if(sol[i] > max){
            max = sol[i];
            inicio = i;
        }
        i++;
    }
    

    return pair<int,int>(max,inicio + 1);
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;

	if (!std::cin)  // fin de la entrada
		return false;

    int n;
    Matriz<int> Mat(N,N);
    for(int i = 0; i < N ;i++){
        for(int j = 0; j < N; j++){
            cin >> n;
            Mat[i][j] = n;
        }
    }
	// resolver el caso posiblemente llamando a otras funciones
    pair<int,int> sol = subida(N,Mat);
	// escribir la solución
    cout << sol.first << " " << sol.second << endl;

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
