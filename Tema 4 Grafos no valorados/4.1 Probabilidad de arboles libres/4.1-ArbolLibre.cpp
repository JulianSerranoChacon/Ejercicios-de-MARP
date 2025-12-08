
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool esLibreRec(const Grafo& g ,vector<bool>& v,int parent, int V, int & ac){
    if(v[V])
        return false;
          
    ++ac;
    v[V] = true; 

    bool sol = true;
    for(int i = 0;sol && i < g.ady(V).size(); i++){
        int next = g.ady(V)[i];
        if(next != parent)
            sol = esLibreRec(g,v,V,next,ac);
    }
    return sol;
}

bool esLibre(const Grafo& g ){
    int nVisited = 0;
    vector<bool> visited(g.V());
    return esLibreRec(g,visited,0,0,nVisited) && nVisited == g.V();
}

bool resuelveCaso() {
	// leer los datos de la entrada

    unsigned int V,A;
    cin >> V >> A;
	if (!std::cin)  // fin de la entrada
		return false;

    Grafo g(V);
    unsigned int v0, v1;
    for (int i = 0; i<A;i++){
        cin >> v0 >> v1;
        g.ponArista(v0,v1);
    }


	// resolver el caso posiblemente llamando a otras funciones
    bool result;
    result = esLibre(g);
	// escribir la solución
    result? cout << "SI\n" : cout << "NO\n";
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
