
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool puedePasar(int origen, int destino, int ancho, const GrafoValorado<int>& g) {
    int V = g.V();
    vector<bool> visitado(V, false);
    vector<int> pila;
    pila.push_back(origen);
    visitado[origen] = true;

    while (!pila.empty()) {
        int v = pila.back(); pila.pop_back();
        if (v == destino) return true;

        for (auto ar : g.ady(v)) {
            int w = ar.otro(v);
            if (!visitado[w] && ar.valor() >= ancho) {
                visitado[w] = true;
                pila.push_back(w);
            }
        }
    }
    return false;
}

// dfs devuelve true si puede llegar a destino respetando el umbral
bool dfs(const GrafoValorado<int>& G, int v, int destino, int umbral, vector<bool>& visit) {
    if (v == destino) return true;  // alcanzamos el destino, terminamos

    visit[v] = true;

    for (auto a : G.ady(v)) {
        int w = a.otro(v);
        if (!visit[w] && a.valor() >= umbral) {
            if (dfs(G, w, destino, umbral, visit)) {
                return true;  // si encontramos el destino en la recursión, salimos
            }
        }
    }

    return false; // no se pudo llegar desde este vértice
}


bool resuelveCaso() {
	// leer los datos de la entrada
    int V, E;
    cin >> V >> E;
	if (!std::cin)  // fin de la entrada
		return false;

    GrafoValorado<int> g(V+1);
    int ini, fin, val;
    for(int i = 0; i < E; i++){
        cin >> ini >> fin >> val;
        g.ponArista(Arista<int>(ini,fin,val));
    }

    int K;
    cin >> K;

    for (int i = 0; i < K; i++) {
    int origen, destino, ancho;
    cin >> origen >> destino >> ancho;
    /*if (puedePasar(origen, destino, ancho, g))
        cout << "SI\n";
    else
        cout << "NO\n";*/
    vector<bool> visited(g.V(),false);
    if(dfs(g,origen,destino,ancho,visited))
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
