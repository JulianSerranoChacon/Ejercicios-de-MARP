
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Conf {
    long long ini, fin;
    int idx; // índice original
	Conf(){}
	Conf(long long i, long long f, int id):ini(i), fin(f), idx(id) {}
};

// Ordenamos por hora de inicio
bool operator<(Conf const& a, Conf const& b) {
    return a.ini < b.ini;
}

// Para la cola de salas: menor fin primero
struct Sala {
    long long fin;
    int id;
    Sala() {}
    Sala(long long f, int i) : fin(f), id(i) {}
};

bool operator<(Sala const& a, Sala const& b) {
    return a.fin < b.fin;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;
	if (N == 0)  // fin de la entrada
		return false;


	PriorityQueue<Conf,less<Conf>> conferencias;
	int ini, fin;
	for(int i = 0; i<N; i++){
		cin >> ini >> fin;
		conferencias.push(Conf(ini,fin,i));
	}
	

	// resolver el caso posiblemente llamando a otras funciones
	 PriorityQueue<Sala, less<Sala>> salas;
    vector<int> sol(N);

    int numSalas = 0;

    while (!conferencias.empty()) {
        Conf c = conferencias.top();
        conferencias.pop();

        if (!salas.empty() && salas.top().fin <= c.ini) {
            // Reutilizar sala
            Sala s = salas.top();
            salas.pop();

            sol[c.idx] = s.id;
            salas.push(Sala(c.fin, s.id));
        }
        else {
            // Nueva sala
            numSalas++;
            sol[c.idx] = numSalas;
            salas.push(Sala(c.fin, numSalas));
        }
    }
	// escribir la solución
	

    cout << numSalas << "\n";
    for (int i = 0; i < N; ++i) {
        cout << sol[i] << (i + 1 < N ? ' ' : '\n');
    }
	

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
