
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

/*@ <answer>

 Esta solución usa un enfoque de dos punteros tras ordenar los pesos de los usuarios.
 Se colocan siempre juntos el más ligero (inicio) y el más pesado (final) si su suma no
 excede el límite de la silla. Si no se pueden sentar juntos, el más pesado ocupa una
 silla solo. Avanzamos los punteros según corresponda y contamos una silla por cada
 intento. Así se minimiza el número de sillas necesarias.

 El coste de la solución es O(N log N) por la ordenación y O(N) por el recorrido con
 dos punteros, siendo N el número de usuarios.

 @ </answer> */

// ================================================================
// Código completo
// ================================================================

bool resuelveCaso() {
    int maxPeso, numUsuarios;
    if (!(cin >> maxPeso >> numUsuarios)) return false; // fin de entrada

    vector<int> pesos(numUsuarios);
    for (int i = 0; i < numUsuarios; ++i)
        cin >> pesos[i];

    sort(pesos.begin(), pesos.end());

    int i = 0;               // puntero al usuario más ligero
    int j = numUsuarios - 1; // puntero al usuario más pesado
    int sillas = 0;

    while (i <= j) {
        if (pesos[i] + pesos[j] <= maxPeso) {
            // pueden ir juntos en la misma silla
            i++;
            j--;
        } else {
            // el más pesado va solo
            j--;
        }
        sillas++; // contamos una silla usada
    }

    cout << sillas << "\n";
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
