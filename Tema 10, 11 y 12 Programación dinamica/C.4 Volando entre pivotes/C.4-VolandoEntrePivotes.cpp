
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int INF = 100000000;

/*@ <answer>

/*@ <answer>
 *
 * El problema se modela como el cálculo de caminos en un grafo dirigido acíclico (DAG)
 * de estructura lineal, que representa una generalización de los números de Fibonacci 
 * de orden K (donde K = S + 1 es el tamaño máximo de avance real en posiciones).
 *
 * Para resolverlo de forma eficiente, se aplica una estrategia de Programación Dinámica 
 * Bottom-Up (Tabulación). Se define un vector 'sol' de tamaño N, donde cada posición 'sol[i]' 
 * almacena el número de formas distintas de alcanzar el pivote 'i' desde el pivote inicial (0).
 *
 * La ecuación de recurrencia que define la subestructura óptima es:
 * sol[i] = Suma(sol[i - j]) para 1 <= j <= S + 1, con i - j >= 0.
 *
 * El caso base se define como sol[0] = 1, ya que solo existe una forma de estar en el 
 * pivote de salida. Dado que los resultados pueden ser muy grandes, todas las sumas 
 * se realizan bajo aritmética modular aplicando el módulo 1.000.000.007.
 *
 * Coste de la solución:
 * - Complejidad Temporal: O(N * S). El bucle externo recorre los N pivotes secuencialmente, 
 * y el bucle interno realiza como máximo S + 1 iteraciones para consultar los estados 
 * anteriores. Dado que S <= 10, el coste es lineal respecto a N, resultando óptimo y 
 * eficiente para N = 100.000.
 * - Complejidad Espacial: O(N). Se requiere un vector de tamaño N para almacenar la 
 * tabla de programación dinámica.
 *
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int saltarPivotes(int N, int S) {
    // El salto real máximo en posiciones es S + 1
    int salto_maximo = S + 1;
    const int MOD = 1000000007;

    // sol[i] guardará las formas de llegar al pivote i
    vector<int> sol(N, 0);
    
    // Caso base: Hay 1 forma de estar en el primer pivote (empezar ahí)
    sol[0] = 1; 

    // Calculamos las formas para cada pivote desde el 1 hasta el N-1
    for (int i = 1; i < N; i++) {
        // Miramos hacia atrás hasta 'salto_maximo' posiciones
        for (int j = 1; j <= salto_maximo && (i - j) >= 0; j++) {
            sol[i] = (sol[i] + sol[i - j]) % MOD;
        }
    }

    return sol[N - 1];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N,S;
	cin >> N >> S;
	if (N == 0 && S== 0)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << saltarPivotes(N,S) << "\n";

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
