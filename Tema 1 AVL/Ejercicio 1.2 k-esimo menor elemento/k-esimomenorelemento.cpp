
/*@ <authors>
 * Julian Serrano Chacon (MARP59)
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>*/

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0)
		return false;

	Set<int> tree;
	int caso;
	for (int i = 0; i < n; ++i)
	{
		// leer cada caso
		cin >> caso;
		tree.insert(caso);
	}

	// numero de consultas
	int m;
	cin >> m;
	vector<int> consultas;
	for (int i = 0; i < m; ++i)
	{
		// leer cada caso
		cin >> caso;
		consultas.push_back(caso);
	}

	//tree.printTam_i(tree.getRaiz());
	// resolver el caso posiblemente llamando a otras funciones
	for (int consulta : consultas) {
		try
		{
			cout << tree.kesimo(consulta) << "\n";
		}
		catch (const std::exception&)
		{
			cout << "??\n";
		}

	}
	// escribir la solución
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
