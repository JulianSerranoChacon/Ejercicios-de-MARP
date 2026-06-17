#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>

El problema se resuelve mediante programación dinámica modelándolo como
una mochila 0/1. Para cada longitud posible hasta L se almacenan tres
valores: el número de formas de obtenerla, el mínimo número de cordeles
necesarios y el coste mínimo.

La transición se realiza para cada cordel recorriendo las longitudes
de forma descendente, lo que garantiza que cada cordel se utilice como
máximo una vez. De esta forma se reduce el uso de memoria a O(L).

El coste temporal del algoritmo es O(N·L) y el coste en memoria es O(L).

@ </answer> */

bool resuelveCaso() {
    int N, L;
    cin >> N >> L;
    if (!cin) return false;

    vector<int> len(N), cost(N);
    for (int i = 0; i < N; ++i) {
        cin >> len[i] >> cost[i];
    }

    vector<unsigned long long> formas(L + 1, 0);
    vector<EntInf> minCuerdas(L + 1, Infinito);
    vector<EntInf> minCoste(L + 1, Infinito);

    formas[0] = 1;
    minCuerdas[0] = 0;
    minCoste[0] = 0;

    for (int i = 0; i < N; ++i) {
        for (int l = L; l >= len[i]; --l) {
            if (formas[l - len[i]] > 0) {
                formas[l] += formas[l - len[i]];
                minCuerdas[l] = min(minCuerdas[l],
                                     minCuerdas[l - len[i]] + 1);
                minCoste[l] = min(minCoste[l],
                                   minCoste[l - len[i]] + cost[i]);
            }
        }
    }

    if (formas[L] == 0) {
        cout << "NO\n";
    } else {
        cout << "SI "
             << formas[L] << " "
             << minCuerdas[L] << " "
             << minCoste[L] << "\n";
    }

    return true;
}

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

