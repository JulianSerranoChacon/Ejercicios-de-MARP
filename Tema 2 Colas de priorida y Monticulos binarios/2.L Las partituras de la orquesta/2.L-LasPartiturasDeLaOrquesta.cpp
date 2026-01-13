
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

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

struct Instrumento {
    int musicos;
    int partituras;

    Instrumento(): musicos(0), partituras(0){}
    Instrumento(int m, int p): musicos(m), partituras(p){ }

    int valor() const {
        return (musicos + partituras - 1) / partituras; // ceil
    }
};

struct Comp {
    bool operator()(Instrumento const& a, Instrumento const& b) const {
        return a.valor() > b.valor(); // max-heap
    }
};


void procesaAtril( PriorityQueue<Instrumento, Comp>&pq){
        Instrumento x = pq.top(); pq.pop();
        x.partituras++;
        pq.push(x);
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int P, N;
    cin >> P >>N;
	if (!std::cin)  // fin de la entrada
		return false;

    PriorityQueue<Instrumento, Comp> pq;
    int read;
    for(int i = 0; i < N; i++){
        cin >> read;
        pq.push(Instrumento(read,1));
    }

	// resolver el caso posiblemente llamando a otras funciones
    for(int i = 0; i < P - N; i++){
        procesaAtril(pq);
    }
	// escribir la solución
    cout << to_string(pq.top().valor()) << "\n";

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
