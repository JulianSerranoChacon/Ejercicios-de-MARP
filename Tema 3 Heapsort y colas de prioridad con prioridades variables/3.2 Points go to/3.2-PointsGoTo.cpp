
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct land {
    string name;
    int points;

    land() {}
    land(string n, int p) : name(n), points(p) {}
};

// Comparador para IndexPQ: compara índices usando vector de lands
struct Comp {
    vector<land> &paises;  // referencia al vector de lands
    Comp(vector<land> &p) : paises(p) {}
    bool operator()(int a, int b) const {
        if (paises[a].points != paises[b].points)
            return paises[a].points > paises[b].points; // mayor puntos → más prioridad
        return paises[a].name < paises[b].name;         // menor nombre lex → más prioridad
    }
};

// ================================================================
// Función de actualización
// ================================================================
void updateLand(int idx, int delta, vector<land> &paises, IndexPQ<int, Comp> &pq) {
    paises[idx].points += delta;
    pq.update(idx, idx); // usamos idx como "prioridad ficticia"
}

// ================================================================
// Resolución de cada caso
// ================================================================
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;

    string read;
    int points;

    vector<land> paises;
    unordered_map<string,int> mapa; // nombre -> índice en paises
    IndexPQ<int, Comp> pq(N, Comp(paises));

    for (int i = 0; i < N; i++) {
        cin >> read;
        if (read == "?") {
            int top_idx = pq.top().elem;
            cout << paises[top_idx].name << " " << paises[top_idx].points << "\n";
        } else {
            cin >> points;
            if (mapa.count(read) == 0) {
                paises.push_back(land(read, points));
                int idx = paises.size() - 1;
                mapa[read] = idx;
                pq.push(idx, idx);
            } else {
                int idx = mapa[read];
                updateLand(idx, points, paises, pq);
            }
        }
    }

    cout << "---\n";
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
