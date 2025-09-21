
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
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
// metodo de debug
void pintaCola(const priority_queue<long, vector<long>, greater<long>>& cola) {
	priority_queue<long, vector<long>, greater<long>> colaAux = cola;
	while (!colaAux.empty())
	{
		cout << colaAux.top() << " ";
		colaAux.pop();
	}
	cout << "\n";
}

long calculaELCostoDeSumar(priority_queue<long, vector<long>, greater<long>>& cola) {
	long coste = 0;
	long sum1, sum2;
	vector<long> costes;
	
	while (cola.size() > 1)
	{
		sum1 = cola.top();
		cola.pop();
		sum2 = cola.top();
		cola.pop();
		coste = sum1 + sum2;
		costes.push_back(coste);
		cola.push(coste);
	}
	coste = 0;
	for (long c : costes)
		coste += c;

	return coste;
}


bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<long, vector<long>, greater<long>> cola;
	int num;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		cola.push(num);
	}

	//pintaCola(cola);

	cout << calculaELCostoDeSumar(cola) << "\n";
	//pintaCola(cola);

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
