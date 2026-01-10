
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void deteccionDeCiclos(int origen, Digrafo const& g,std::vector<int> &ant, std::vector<bool> &apilado, std::vector<bool> &visited,vector<int> &sol,bool &hayCiclo){
    apilado[origen] = true;
    visited[origen] = true;
    for (int w : g.ady(origen)) 
    {
        if (hayCiclo) // si hemos encontrado un ciclo terminamos
            return;
        if (!visited[w])  // encontrado un nuevo vértice, seguimos
        {
            ant[w] = origen; 
            deteccionDeCiclos(w,g, ant,apilado,visited,sol,hayCiclo);
        } 
        else if (apilado[w])
        { // hemos detectado un ciclo
            hayCiclo = true;
        }
    }

    apilado[origen] = false;
    sol.push_back(origen);
}

bool hayCicloenAsignaciones(Digrafo const& g, vector<int> &sol){
    std::vector<int> ant(g.V()); // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado(g.V()); 
    std::vector<bool> visited(g.V());
    bool hayCilclo = false;
    for(int i = 1; i<g.V();i++)
        if(!hayCilclo && !visited[i])
            deteccionDeCiclos(i,g,ant,apilado,visited,sol,hayCilclo);

    return hayCilclo;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, M; //tareas y relacciones
    cin >> N >> M;
	if (!std::cin)  // fin de la entrada
		return false;

    Digrafo g(N + 1);
    int v,w;
    for (int i = 0; i<M;i++){
        cin >> v >> w;
        g.ponArista(v,w);
    }

	// resolver el caso posiblemente llamando a otras funciones
    vector<int> soluciones;
    if(!hayCicloenAsignaciones(g.inverso(),soluciones)){
        for(int i = 0; i<soluciones.size();i++){
            cout << to_string(soluciones[i]) << " ";
        }
        cout << "\n";
    }
    else{
        cout << "IMPOSIBLE\n";
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
