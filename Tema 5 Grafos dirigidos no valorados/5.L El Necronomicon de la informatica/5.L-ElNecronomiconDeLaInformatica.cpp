
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

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

void dfs(int v, const Digrafo &g, vector<bool> &visit, vector<bool> &apilado, bool &hayCiclos) {
    visit[v] = true;
    apilado[v] = true;

    for (int w : g.ady(v)) {
        if (!visit[w])
            dfs(w, g, visit, apilado, hayCiclos);
        else if (apilado[w])
            hayCiclos = true; // ciclo detectado
    }

    apilado[v] = false;
}

string resuelvePrograma(const Digrafo &g) {
    int n = g.V() - 1; // último nodo "real" (el ficticio es L)
    vector<bool> visit(n+1, false);
    vector<bool> apilado(n+1, false);
    bool hayCiclos = false;

    dfs(0, g, visit, apilado, hayCiclos);

    if (!visit[n]) return "NUNCA";
    if (hayCiclos) return "A VECES";
    return "SIEMPRE";
}



bool resuelveCaso() {
	// leer los datos de la entrada
    int L;
    cin >> L;
	if (!std::cin)  // fin de la entrada
		return false;

    
    Digrafo g(L+1);
    char c;
    int s;
    for (int i = 0; i < L; i++){
        cin >> c;
        switch (c)
        {
        case 'A':
            g.ponArista(i,i+1);
            break;
        case 'J':
            cin >> s;
            g.ponArista(i,s-1);
            break;
        case 'C':
            cin >> s;
            g.ponArista(i,s-1);
            g.ponArista(i,i+1);
            break;
        default:
            break;
        }
    }

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
    cout << resuelvePrograma(g) << "\n";

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
