#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edificio {
    long long W, E;
};

// Ordenamos por extremo derecho creciente
bool compararPorE(const Edificio& a, const Edificio& b) {
    return a.E < b.E;
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    vector<Edificio> edificios(N);
    for (int i = 0; i < N; ++i)
        cin >> edificios[i].W >> edificios[i].E;

    sort(edificios.begin(), edificios.end(), compararPorE);

    int tuneles = 0;
    long long ultimoTunel = -1; // posición del último túnel

    for (const auto& ed : edificios) {
        if (ultimoTunel <= ed.W) { 
            // Si el último túnel no está dentro del edificio
            ultimoTunel = ed.E; // colocamos túnel en extremo derecho del edificio
            ++tuneles;
        }
        // Si ultimoTunel >= ed.W, ya está cubierto
    }

    cout << tuneles << "\n";
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
