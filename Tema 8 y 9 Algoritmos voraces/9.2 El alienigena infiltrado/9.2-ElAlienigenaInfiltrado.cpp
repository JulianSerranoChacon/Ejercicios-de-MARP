
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

struct Comp{
    bool operator()( pair<long long, long long> const &a,pair<long long, long long> const &b) const{
            return a.first < b.first;
    }
};

bool resuelveCaso() {
	// leer los datos de la entrada
    long long C, F;
    int N;
    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)
        return false;  // fin de la entrada

    vector<pair<long long, long long>> trabajos(N);
    for (int i = 0; i < N; ++i) {
        cin >> trabajos[i].first >> trabajos[i].second;
    }

	// resolver el caso posiblemente llamando a otras funciones
    sort(trabajos.begin(), trabajos.end(),Comp());

    int contador = 0;
    long long actual = C;
    int i = 0;
    bool posible = true;

    while (actual < F) {
        long long maxFin = actual;
        // Buscamos intervalos que empiecen <= actual y seleccionamos el que más extienda la cobertura
        while (i < N && trabajos[i].first <= actual) {
            if (trabajos[i].second > maxFin) {
                maxFin = trabajos[i].second;
            }
            ++i;
        }

        if (maxFin == actual) {
            // No encontramos intervalos que extiendan la cobertura
            posible = false;
            break;
        }

        actual = maxFin;
        ++contador;
    }
	// escribir la solución

    if (posible) cout << contador << "\n";
    else cout << "Imposible\n";

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
