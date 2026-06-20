
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int aibofobiaRec(string const& cadena, int i, int j,  Matriz<int> & mat){
    int & res = mat[i][j]; 
    if (res == -1) 
    { 
        if (i > j) 
            res = 0; 
        else if (i == j) 
            res = 0; 
        else if (cadena[i] == cadena[j]) 
            res = aibofobiaRec(cadena, i+1, j-1, mat); 
        else {
            res = min(aibofobiaRec(cadena, i, j-1, mat), 
            aibofobiaRec(cadena, i+1, j, mat)) + 1; 
        }
    } 
    return res;
}

void reconstruir(string const& cadena, Matriz<int> const& mat, int i, int j, string& sol_izq, string& sol_der) { 
    // Caso base 1: No quedan caracteres por procesar
    if (i > j) return; 
    
    // Caso base 2: Queda un solo carácter en el centro (es el eje del palíndromo)
    if (i == j) {
        sol_izq += cadena[i];
        return;
    } 
    
    if (cadena[i] == cadena[j]) {
        // Los caracteres ya coinciden, van a ambos lados
        sol_izq += cadena[i];
        sol_der = cadena[j] + sol_der;
        reconstruir(cadena, mat, i + 1, j - 1, sol_izq, sol_der); 
    } 
    else if (mat[i][j] == mat[i + 1][j] + 1) { // Venimos de insertar el carácter cadena[i] al final
        sol_izq += cadena[i];
        sol_der = cadena[i] + sol_der; // Duplicamos en el extremo opuesto para hacer el palíndromo
        reconstruir(cadena, mat, i + 1, j, sol_izq, sol_der); 
    } 
    else { // Venimos de insertar el carácter cadena[j] al principio
        sol_izq += cadena[j]; // Duplicamos en el extremo opuesto
        sol_der = cadena[j] + sol_der;
        reconstruir(cadena, mat, i, j - 1, sol_izq, sol_der); 
    }
}


pair<int,string> aibofobia(string const& cadena){
    int n = cadena.length();
     Matriz<int> mat(n,n,-1);
    pair<int,string> ret(0,"");
    ret.first = aibofobiaRec(cadena,0,n-1,mat);
    string sol_izq = "";
    string sol_der = "";
    reconstruir(cadena,mat,0,n-1,sol_izq,sol_der);
    ret.second = sol_izq + sol_der;
    return ret;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    string cadena;
    cin >> cadena;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
    pair<int,string> sol = aibofobia(cadena);
	// escribir la solución
    cout << sol.first << " " << sol.second << "\n";
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
