
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <stack>
#include <limits>

using namespace std;

#include "PriorityQueue.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct comicStack{
public:
    stack<int> pila;
    comicStack():pila(){}
};

struct Comp {
    bool operator()(comicStack const& a, comicStack const& b) const {
        return a.pila.top() < b.pila.top(); // max-heap
    }
};

int encuentraPuesto(PriorityQueue<comicStack,Comp> pq, int wanted){
    int sol = 1;
    while (pq.top().pila.top() != wanted)
    {
        comicStack t = pq.top();
        pq.pop();
        t.pila.pop();
        if(!t.pila.empty())
            pq.push(t);
        sol++;
    }
    

    return sol;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;

    int wanted = numeric_limits<int>::max();
    PriorityQueue<comicStack,Comp> pq;
    int P , id;
    for(int i = 0; i<N; i++){
        cin >> P;
        struct comicStack c;
        for (int j = 0; j < P; j++){
            cin >> id;
            wanted = min(wanted,id);
            c.pila.push(id);
        }
        pq.push(c);
    }

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    cout << to_string(encuentraPuesto(pq, wanted)) << "\n";

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
