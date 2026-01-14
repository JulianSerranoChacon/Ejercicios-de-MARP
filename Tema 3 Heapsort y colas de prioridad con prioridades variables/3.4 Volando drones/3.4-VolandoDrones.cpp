/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "IndexPQ.h" propios o los de las estructuras de datos de clase

/*@ <answer>

Usamos dos colas de prioridad máxima para gestionar las pilas de 9 V y
las de 1.5 V. Cada sábado se asignan como máximo N drones, tomando
siempre las pilas más cargadas de cada tipo. El tiempo de vuelo de cada
dron es el mínimo entre las dos pilas usadas. Los restos de pilas no
agotadas se almacenan temporalmente y se reinsertan en las colas al
finalizar el sábado. El proceso se repite hasta que no se pueda volar
ningún dron.

El coste total es O((A + B) log(A + B)).

@ </answer> */

// ================================================================
// Código de la solución
// ================================================================

bool resuelveCaso() {
    int N, A, B;
    cin >> N >> A >> B;
    if (!cin) return false;

    IndexPQ<int, greater<int>> pq9(A + 1);
    IndexPQ<int, greater<int>> pq15(B + 1);

    int x;
    for (int i = 0; i < A; i++) {
        cin >> x;
        if (x > 0) pq9.push(i, x);
    }

    for (int i = 0; i < B; i++) {
        cin >> x;
        if (x > 0) pq15.push(i, x);
    }

    while (!pq9.empty() && !pq15.empty()) {
        long long total = 0;
        int drones = 0;

        vector<pair<int,int>> rest9;
        vector<pair<int,int>> rest15;

        while (drones < N && !pq9.empty() && !pq15.empty()) {
            int e9 = pq9.top().elem;
            int p9 = pq9.top().prioridad;
            pq9.pop();

            int e15 = pq15.top().elem;
            int p15 = pq15.top().prioridad;
            pq15.pop();

            int vuelo = min(p9, p15);
            total += vuelo;

            if (p9 > vuelo)
                rest9.push_back({e9, p9 - vuelo});
            if (p15 > vuelo)
                rest15.push_back({e15, p15 - vuelo});

            drones++;
        }

        if (total == 0) break;

        cout << total << " ";

        for (auto &p : rest9)
            pq9.push(p.first, p.second);

        for (auto &p : rest15)
            pq15.push(p.first, p.second);
    }

    cout << "\n";
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
