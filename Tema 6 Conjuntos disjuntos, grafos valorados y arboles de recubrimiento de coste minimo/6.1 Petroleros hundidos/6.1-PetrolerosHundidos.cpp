
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>



int añadeMancha(ConjuntosDisjuntos &conj, vector<bool> &contaminado,
                 int F, int C, int fil, int col, int maxMancha) {

    int v = fil * C + col;
    contaminado[v] = true;

    // vecino superior
    if (fil > 0 && contaminado[(fil - 1) * C + col])
        conj.unir(v, (fil - 1) * C + col);

    // vecino inferior
    if (fil + 1 < F && contaminado[(fil + 1) * C + col])
        conj.unir(v, (fil + 1) * C + col);

    // vecino derecho
    if (col + 1 < C && contaminado[fil * C + (col + 1)])
        conj.unir(v, fil * C + (col + 1));

    // vecino izquierdo
    if (col > 0 && contaminado[fil * C + (col - 1)])
        conj.unir(v, fil * C + (col - 1));

    // diagonal superior izquierda
    if (fil > 0 && col > 0 && contaminado[(fil - 1) * C + (col - 1)])
        conj.unir(v, (fil - 1) * C + (col - 1));

    // diagonal inferior izquierda
    if (fil + 1 < F && col > 0 && contaminado[(fil + 1) * C + (col - 1)])
        conj.unir(v, (fil + 1) * C + (col - 1));

    // diagonal inferior derecha
    if (fil + 1 < F && col + 1 < C && contaminado[(fil + 1) * C + (col + 1)])
        conj.unir(v, (fil + 1) * C + (col + 1));

    // diagonal superior derecha
    if (fil > 0 && col + 1 < C && contaminado[(fil - 1) * C + (col + 1)])
        conj.unir(v, (fil - 1) * C + (col + 1));

    // actualizar tamaño máximo de la mancha
    int nuevoTam = conj.cardinal(v);
    return max(maxMancha, nuevoTam);
}


bool resuelveCaso() {
	// leer los datos de la entrada
    int F, C;
    cin >> F >> C;
	if (!std::cin)  // fin de la entrada
		return false;

    vector<vector<char>> matriz(F,vector<char>(C));
    char c;
    for (int i = 0; i<F; i++){
        for (int j = 0; j<C; j++)
        {
            cin >> c;
            matriz[i][j] = c;
        }
        
    }

    vector<bool> contaminado(F*C,false);
    ConjuntosDisjuntos conj(F*C);
    int maxMancha = 0;  // tamaño de la mayor mancha inicial
    for (int i = 0; i<F; i++)
    {
        for (int j = 0; j<C; j++)
        {
            if(matriz[i][j] != '#')
                continue;
            
            int v = i * C + j;
            contaminado[v] = true;
            //vecino de arriba
            if(i> 0 && matriz[i -1][j] == '#'){
                conj.unir(v, (i-1) * C + j);
            }

            //vecino de la izquierda
            if(j > 0 && matriz[i][j-1]== '#'){
                conj.unir(v, i*C + (j-1));
            }

            //vecino de la diagonal superior izquierda
            if(i> 0 && j > 0 && matriz[i -1][j - 1] == '#'){
                conj.unir(v, (i-1) * C + (j -1));
            }

            //vecino de la diagonal superior derecha
            if(i > 0 && j +1 < C && matriz[i - 1][j + 1] == '#'){
                conj.unir(v, (i-1) * C + (j + 1));
            }

            maxMancha = max(maxMancha, conj.cardinal(v));
        }
    }
	// resolver el caso posiblemente llamando a otras funciones
    int N, f, col;
    cin >> N;

    cout << maxMancha;
    for (int i = 0; i< N;i++){
 cin >> f >> col;
        maxMancha = añadeMancha(conj, contaminado, F, C, f - 1, col - 1, maxMancha);
        cout << " " << maxMancha;
    }

    cout << "\n";
	// escribir la solución

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
