
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 El problema se resuelve modelando la base de datos cinematográfica como
 un grafo no dirigido en el que cada vértice representa a un actor o actriz
 y existe una arista entre dos vértices si ambos han trabajado juntos en
4.5-Los numeros de Bacon alguna película.

 Para construir el grafo se asigna un identificador entero a cada actor
 mediante una tabla hash. Cada película induce un clique entre todos sus
 actores, añadiendo las correspondientes aristas al grafo.

 Una vez construido el grafo, el número de Bacon de cada actor se obtiene
 calculando la distancia mínima desde el vértice correspondiente a
 Kevin Bacon mediante un recorrido en anchura (BFS), ya que el grafo es
 no ponderado.

 Si un actor no es alcanzable desde Kevin Bacon, su número de Bacon es INF.

 El coste de construir el grafo es O(A), siendo A el número total de
 apariciones de actores en películas. El recorrido BFS tiene coste
 O(V + E), donde V es el número de actores y E el número de relaciones
 entre ellos.

 @ </answer> */



// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>
int getId(const string& nombre,unordered_map<string, int>& idActor,vector<string>& nombreActor,int& nextId) 
{
    if(idActor.count(nombre))
        return idActor.at(nombre);

    int id = nextId++;
    idActor[nombre] = id;
    nombreActor.push_back(nombre);
    return id;
    
}

// BFS desde Kevin Bacon
vector<int> calcularBacon(Grafo const& g, int origen) {
    vector<int> dist(g.V(), -1);
    queue<int> q;

    dist[origen] = 0;
    q.push(origen);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : g.ady(v)) {
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;
                q.push(w);
            }
        }
    }
    return dist;
}

// Leer consultas y mostrar resultados
void leerYResponderConsultas(unordered_map<string, int> const& idActor,vector<int> const& dist) {

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string nombre;
        cin >> nombre;
        int id = idActor.at(nombre);

        if (dist[id] == -1)
            cout << nombre << " INF\n";
        else
            cout << nombre << " " << dist[id] / 2 << "\n"; // distancia / 2
    }
    cout << "---\n";
}



bool resuelveCaso() {
	// leer los datos de la entrada
    int P;
    cin >> P;

	if (!std::cin)  // fin de la entrada
		return false;

     unordered_map<string, int> idActor;
    vector<string> nombreActor;
    vector<vector<int>> peliculas(P);
    int nextId = 0; // ID de actores

    // Leer películas y actores
    for (int i = 0; i < P; i++) {
        string titulo;
        int k;
        cin >> titulo >> k;

        for (int j = 0; j < k; j++) {
            string nombre;
            cin >> nombre;
            peliculas[i].push_back(getId(nombre, idActor, nombreActor, nextId));
        }
    }

    int numActores = nextId;
    int numVertices = numActores + P;
    Grafo g(numVertices);

    // Construir grafo bipartito: actor ↔ película
    for (int i = 0; i < P; i++) {
        int idPelicula = numActores + i;
        for (int idActor : peliculas[i]) {
            g.ponArista(idActor, idPelicula);
        }
    }

    // BFS desde Kevin Bacon
    vector<int> dist;
    if (idActor.count("KevinBacon")) {
        int origen = idActor.at("KevinBacon");
        dist = calcularBacon(g, origen);
    } else {
        dist.assign(numActores + P, -1);
    }


	// escribir la solución.
    leerYResponderConsultas(idActor, dist);

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
