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

 Esta solución ordena los voltajes de las pilas y usa dos punteros para emparejarlas:
 el puntero `i` comienza en el principio (pila más pequeña) y el puntero `j` en el final
 (pila más grande). Si la suma de voltajes `pilas[i] + pilas[j]` es al menos V,
 formamos un coche con estas dos pilas y avanzamos ambos punteros. Si no, descartamos
 la pila más pequeña (i++) porque no puede emparejarse con la más grande para alcanzar
 el mínimo V. Así maximizamos el número de coches.

 Si no se puede formar ningún par que cumpla la condición, se imprime "Imposible".

 El coste de la solución es O(N log N) por la ordenación y O(N) por el recorrido con
 dos punteros, siendo N el número de pilas.

 @ </answer> */

void resuelveCaso() {
    int N;
    long long V;
    cin >> N >> V;  // lee N y V

    vector<long long> pilas(N);
    for (int i = 0; i < N; ++i)
        cin >> pilas[i];

    sort(pilas.begin(), pilas.end());

    int i = 0, j = N - 1;
    int coches = 0;

    while (i < j) {
        if (pilas[i] + pilas[j] >= V) {
            coches++;
            i++;
            j--;
        } else {
            i++;
        }
    }

    cout << coches << "\n";
}

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
