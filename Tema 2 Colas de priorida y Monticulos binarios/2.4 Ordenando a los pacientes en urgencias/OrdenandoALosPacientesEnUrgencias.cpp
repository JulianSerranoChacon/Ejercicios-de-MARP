
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
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

struct Paciente {
	int prio;
	string name;
	int nllegada;
	Paciente(int p, string n, int nl): prio(p), name(n), nllegada(nl){}
};

bool operator>(Paciente const&a, Paciente const& b){
	return b.prio > a.prio || (b.prio == a.prio && b.nllegada < a.nllegada);
}

string asistePacientePrioritario(priority_queue<Paciente, vector<Paciente>, greater<Paciente>>& pacientes) {
	string sol = pacientes.top().name;
	pacientes.pop();
	return sol;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)
		return false;

	int npacientes = 0;
	char action;
	string nombre;
	int prioridad;
	priority_queue<Paciente, vector<Paciente>, greater<Paciente>> pacientes;
	vector<string> respuestas;
	for (int i = 0; i < n; i++) {
		cin >> action;
		if (action == 'I') {
			cin >> nombre >> prioridad;
			pacientes.push(Paciente(prioridad, nombre, npacientes));
			npacientes++;
		}
		else
			respuestas.push_back(asistePacientePrioritario(pacientes));
	}


	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución
	for (string r : respuestas)
		cout << r << "\n";

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
