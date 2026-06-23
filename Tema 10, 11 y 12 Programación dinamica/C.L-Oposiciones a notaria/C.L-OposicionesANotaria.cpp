
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
El problema se modela como la fusión óptima de archivos contiguos (problema del intervalo),
 * resolviéndose mediante Programación Dinámica Bottom-Up por diagonales.
 *
 * Se utiliza una matriz 'matrices' de tamaño n x n donde 'matrices[i][j]' almacena
 * el coste mínimo en segundos para fusionar los documentos desde el índice i hasta el j (indexado desde 0).
 * Para optimizar el cálculo del coste de fusión (suma de páginas del intervalo [i, j]), se 
 * utiliza un vector de sumas acumuladas 'acumulados', permitiendo obtener dicha suma en O(1).
 *
 * La ecuación de recurrencia evalúa todos los posibles puntos de corte 'k':
 * matrices[i][j] = Min { matrices[i][k] + matrices[k+1][j] } + Coste_Intervalo(i, j)
 * para todo k tal que i <= k < j.
 *
 * Los casos base son las fusiones de un único documento (i == j), cuyo coste es 0.
 *
 * Coste de la solución:
 * - Complejidad Temporal: O(n^3), donde n es el número de documentos. El algoritmo utiliza
 * tres bucles anidados: el primero recorre las diagonales, el segundo las celdas de la diagonal
 * y el tercero busca el punto de corte óptimo 'k'. Gracias al vector 'acumulados', la suma se 
 * obtiene en tiempo constante O(1), evitando elevar el coste a O(n^4).
 * - Complejidad Espacial: O(n^2) debido a la matriz necesaria para almacenar las soluciones
 * de los subintervalos.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

// Usamos un infinito lo suficientemente grande para long long
const long long int INF = 1e18;

long long int juntaDocumentos(vector<int> const& documentos) {
    int n = documentos.size();
    if (n <= 1) return 0;

    // 1. Calcular sumas acumuladas usando long long int
    vector<long long int> acumulados(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        acumulados[i + 1] = acumulados[i] + documentos[i];
    }

    // 2. Tabla de programación dinámica (n x n) con long long int
    vector<vector<long long int>> matrices(n, vector<long long int>(n, 0));

    // 3. Computación por diagonales
    for (int d = 1; d < n; ++d) { 
        for (int i = 0; i < n - d; ++i) { 
            int j = i + d;
            matrices[i][j] = INF;
            
            for (int k = i; k < j; ++k) {
                long long int coste_fusion = acumulados[j + 1] - acumulados[i];
                long long int temp = matrices[i][k] + matrices[k + 1][j] + coste_fusion;
                
                if (temp < matrices[i][j]) { 
                    matrices[i][j] = temp;
                }
            }
        }
    }
    
    return matrices[0][n - 1];
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;

	if (N == 0)
		return false;

    vector<int> documentos(N);

    for(int i = 0; i <N; i++)
        cin >> documentos[i];

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    cout << juntaDocumentos(documentos) << "\n";

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
