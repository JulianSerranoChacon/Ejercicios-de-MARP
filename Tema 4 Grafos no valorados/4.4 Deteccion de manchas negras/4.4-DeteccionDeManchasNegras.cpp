
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

void grupoMasGrandeRec(const Grafo & g,vector<bool>& visited, int V, int& ac){
    if(visited[V])
        return;

    ++ac;
    visited[V] = true;
    
    for(int i = 0; i < g.ady(V).size(); i++){
        int next = g.ady(V)[i];
        if(!visited[next])
            grupoMasGrandeRec(g,visited,next,ac);
    }
}

pair<int,int> grupoMasGrande(const Grafo & g, const vector<bool> &esNegro){
    int max = 0;
	int nGroups = 0;
    vector<bool>visited(g.V(),false);

    for(int i = 0; i < g.V(); i++){
		if (!esNegro[i] || visited[i]) continue; // Solo píxeles negros no visitados
			
        int ac = 0;
        grupoMasGrandeRec(g,visited,i,ac);
        max = std::max(max, ac);
		nGroups++;
    }

    return pair<int,int>(nGroups,max);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int F, C;
	cin >> F >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	char c;
	vector<vector<char>> bitmap(F,vector<char>(C));
	for (int i = 0; i < F;i++){
		for (int j = 0; j < C; j++)
		{
			cin >> c;
			bitmap[i][j] = c;
		}
	}

	vector<bool> esNegro(F*C,false);
	Grafo g(F*C);
	for (int i = 0; i < F;i++){
		for (int j = 0; j < C; j++)
		{
			if(bitmap[i][j] != '#') 
				continue;
			
			int v = i * C + j;
            // Vecino de arriba
            if (i > 0 && bitmap[i-1][j] == '#') {
                g.ponArista(v, (i-1)*C + j);
            }
            // Vecino de la izquierda
            if (j > 0 && bitmap[i][j-1] == '#') {
                g.ponArista(v, i*C + (j-1));
            }
			esNegro[v] = true;
			
		}
	}

	// resolver el caso posiblemente llamando a otras funciones
	pair<int,int> result = grupoMasGrande(g,esNegro);
	// escribir la solución
	cout << result.first << " " << result.second << "\n";
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
