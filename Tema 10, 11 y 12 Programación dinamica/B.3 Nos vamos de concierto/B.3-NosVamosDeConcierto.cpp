
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct concierto
{
    int ngrupos;
    int precio;

    concierto(int g, int p): ngrupos(g), precio(p) {}
};

int visitaMaximos(vector<concierto> const& conciertos, int P){
    vector<int> sol(P + 1, 0);
    
    for (concierto const& c : conciertos) {
        for (int j = P; j >= c.precio; --j) {
            sol[j] = max(sol[j],
                        sol[j - c.precio] + c.ngrupos);
        }
    }

    return sol[P];
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int P, N;
    cin >> P >> N;

	if (!std::cin)  // fin de la entrada
		return false;

    int ngrupos, precio;
    vector<concierto> conciertos;
    for(int i = 0; i < N ;i++){
        cin >> ngrupos >> precio;
        conciertos.push_back(concierto(ngrupos,precio));
    }

	// resolver el caso posiblemente llamando a otras funciones
    int sol = visitaMaximos(conciertos,P);
	// escribir la solución
    cout << sol << "\n";
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
