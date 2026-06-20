
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "Matriz.h"

//#include   // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void reconstruir(int i, int j, const vector<string>& g1, const vector<string>& g2, const Matriz<int>& mat, vector<string>& sol) {
    if (i == 0 || j == 0) return;

    if (g1[i - 1] == g2[j - 1]) {
        // Si coinciden, la canción pertenece a la solución óptima (recursión hacia atrás)
        reconstruir(i - 1, j - 1, g1, g2, mat, sol);
        sol.push_back(g1[i - 1]);
    } else if (mat[i - 1][j] >= mat[i][j - 1]) {
        reconstruir(i - 1, j, g1, g2, mat, sol);
    } else {
        reconstruir(i, j - 1, g1, g2, mat, sol);
    }
}

void eligeCanciones(vector<string> const& g1, vector<string> const& g2, vector<string>& sol) {
    int n = g1.size();
    int m = g2.size();
    
    // Matriz de tamaño (n+1) x (m+1) inicializada a 0
    Matriz<int> mat(n + 1, m + 1, 0);

    // Enfoque Bottom-Up
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g1[i - 1] == g2[j - 1]) {
                mat[i][j] = mat[i - 1][j - 1] + 1;
            } else {
                mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
            }
        }
    }

    // Reconstruimos la solución recuperando los strings
    reconstruir(n, m, g1, g2, mat, sol);
}

/* si solo me pidieran el número de canciones posible se puede reducir a 1D
int longitudLCS(const vector<string>& g1, const vector<string>& g2) {
    int n = g1.size();
    int m = g2.size();
    
    // Un único vector de una dimensión inicializado a 0
    vector<int> v(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int diagonal_vieja = 0; // Guarda el estado de v[j-1] de la fila anterior
        
        for (int j = 1; j <= m; ++j) {
            int temp = v[j]; // Guardamos el valor de "arriba" antes de modificarlo
            
            if (g1[i - 1] == g2[j - 1]) {
                // Si coinciden, usamos la diagonal guardada en la iteración anterior
                v[j] = diagonal_vieja + 1;
            } else {
                // Si no coinciden, max entre "arriba" (v[j]) e "izquierda" (v[j-1])
                v[j] = max(v[j], v[j - 1]);
            }
            
            diagonal_vieja = temp; // El "arriba" de ahora será la diagonal del próximo paso
        }
    }

    return v[m]; // El resultado final queda en la última posición
}*/

bool resuelveCaso() {
	// leer los datos de la entrada
    vector<string> grupo1;
    vector<string> grupo2;

    string s;
    getline(cin, s, '\n');
    
    stringstream ss(s);

    while (getline(ss, s, ' ')) {
        grupo1.push_back(s);
    }

    string s2;
    getline(cin, s2, '\n');
    
    stringstream ss2(s2);

    while (getline(ss2, s2, ' ')) {
        grupo2.push_back(s2);
    }

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
    vector<string> sol;
    eligeCanciones(grupo1,grupo2,sol);
	// escribir la solución

    for(string str: sol)
        cout << str << ' ';

    cout << '\n';

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
