
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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
//usaré paciente como un par de uints que guarda la id y su tiempo de espera en ese orden

struct paciente{
	int momento;
	unsigned int id;
	int periodo;
	paciente(int m, int i, int p): momento(m),id(i), periodo(p) {};
};

bool operator<(paciente const& p1, paciente const& p2) {
	return p2.momento < p1.momento || (p2.momento == p1.momento && p2.id < p1.id);
}

void llamamiento(priority_queue<paciente, vector<paciente>, less<paciente>>& cola, vector<unsigned int>& sol, int k) {
	int periodo;
	for (int i = 0; i < k; i++) {
		sol.push_back(cola.top().id);
		periodo = cola.top().periodo;
		cola.push(paciente(cola.top().momento + periodo, cola.top().id,periodo));
		cola.pop();
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)
		return false;

	priority_queue<paciente,vector<paciente>,less<paciente>> cola;
	int periodo, id;
	for (int i = 0; i < n; i++) {
		cin >> id;
		cin >> periodo;
		cola.push(paciente(periodo, id, periodo));
	}

	// resolver el caso posiblemente llamando a otras funciones
	int k;
	cin >> k;
	vector<unsigned int> sol;
	llamamiento(cola, sol, k);

	// escribir la solución
	for (unsigned int s : sol)
		cout << s << "\n";

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
