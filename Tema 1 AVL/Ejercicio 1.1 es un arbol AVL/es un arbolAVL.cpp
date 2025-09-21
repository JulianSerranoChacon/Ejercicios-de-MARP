
/*@ <authors>
 * Julián Serrano Chacón MARP59
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>
#include "bintree.h"

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
template <typename T>
struct sol {
	bool avl;
	int altura;
	T menor, mayor;
};

// dado un árbol binario averigua si es AVL y calcula su altura
// y si es un ABB no vacío, cuáles son su menor y mayor claves
// O(número de nodos del árbol)
template <typename T>
sol<T> es_avl_rec(BinTree<T> const& arbol) {
	if (arbol.empty()) {
		// no tiene ni menor ni mayor clave
		return { true, 0, T(), T() };
	}
	else {

		// averiguamos toda la información de los hijos, de manera recursiva
		auto [avl_iz, alt_iz, menor_iz, mayor_iz] = es_avl_rec(arbol.left());
		auto [avl_dr, alt_dr, menor_dr, mayor_dr] = es_avl_rec(arbol.right());

		int alt = max(alt_iz, alt_dr) + 1;

		// cuidado si los hijos son vacíos
		T menor = arbol.left().empty() ? arbol.root() : menor_iz;
		T mayor = arbol.right().empty() ? arbol.root() : mayor_dr;

		bool ordenado = (arbol.left().empty() || mayor_iz < arbol.root()) &&
			(arbol.right().empty() || arbol.root() < menor_dr);

		return { ordenado && avl_iz && avl_dr && abs(alt_iz - alt_dr) < 2,
				alt, menor, mayor };
	}
}

template <typename T>
bool es_avl(BinTree<T> const& arbol) {
	return es_avl_rec(arbol).avl;
}

bool resuelveCaso() {
	char c;
	cin >> c;
	if (!cin) return false;
	if (c == 'N') {
		auto t = read_tree<int>(cin);
		if (es_avl(t))
			cout << "SI\n";
		else
			cout << "NO\n";
	}
	else {
		auto t = read_tree<string>(cin);
		if (es_avl(t))
			cout << "SI\n";
		else
			cout << "NO\n";
	}
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.txt");
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
