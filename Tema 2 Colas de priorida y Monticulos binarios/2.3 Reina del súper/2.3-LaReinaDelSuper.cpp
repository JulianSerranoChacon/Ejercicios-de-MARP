
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
//la caja es un par con el numero de caja y el tiempo

struct caja
{
	int num;
	int tc;
	caja(int n, int t) : num(n), tc(t) {};
};

bool operator<(caja const& c1, caja const& c2) {
	return c2.tc < c1.tc || (c2.tc == c1.tc && c2.num < c1.num);
}

//debug
void escribeCola(priority_queue<caja, vector<caja>, less<caja>> cola){
	while (!cola.empty())
	{
		cout << cola.top().tc << "\n";
		cola.pop();
	}
	cout << "\n";
}
int pasaPorCaja(priority_queue<caja, vector<caja>, less<caja>>& cola,const vector<int>& clientes) {
	for (int c : clientes) {
		cola.push(caja(cola.top().num, cola.top().tc + c));
		cola.pop();
	}
	return cola.top().num;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, c;
	cin >> n >> c;
	if (n == 0 && c == 0)
		return false;

	priority_queue<caja, vector<caja>, less<caja>> cola;
	for (int i = 0; i < n; i++) {
		cola.push(caja(i+1,0));
	}

	vector<int> clientes;
	int cl;
	for (size_t i = 0; i < c; i++)
	{
		cin >> cl;
		clientes.push_back(cl);
	}

	// resolver el caso posiblemente llamando a otras funciones
	int sol;
	sol = pasaPorCaja(cola, clientes);
	// escribir la solución
	cout << sol << "\n";
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
