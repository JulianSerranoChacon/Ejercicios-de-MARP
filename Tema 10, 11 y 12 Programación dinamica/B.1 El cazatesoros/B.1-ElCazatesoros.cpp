
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h" // propios o los de las estructuras de datos de clase

struct objeto
{
    /* data */
    int profundidad;
    int cantOro;

    objeto(int p, int o): profundidad(p), cantOro(o){}
};


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int recogeOroRec(int i, int j,const vector<objeto>& objetos,Matriz<int>& mat) {

    if (i == 0 || j == 0)
        return 0;

    if (mat[i][j] != -1)
        return mat[i][j];

    int coste = 3 * objetos[i-1].profundidad;

    if (coste > j)
        mat[i][j] = recogeOroRec(i-1, j, objetos, mat);
    else
        mat[i][j] = max(
            recogeOroRec(i-1, j, objetos, mat),
            recogeOroRec(i-1, j-coste, objetos, mat)
                + objetos[i-1].cantOro
        );

    return mat[i][j];
}

int reconstruyeSeleccionados(const vector<objeto>& objetos,int P,vector<bool>& seleccionados,Matriz<int>& mat) {
 int i = objetos.size();
    int j = P;
    int nsel = 0;

    while (i > 0) {

        int coste = 3 * objetos[i-1].profundidad;

        // Si no cabe → seguro NO está
        if (coste > j) {
            i--;
            continue;
        }

        int sin = mat[i-1][j];
        int con = mat[i-1][j-coste] + objetos[i-1].cantOro;

        if (con >= sin) {   // 👈 CLAVE (NO igualdad)
            seleccionados[i-1] = true;
            j -= coste;
            nsel++;
        }

        i--;
    }

    return nsel;
}

void recogeOro(int N,int P,const vector<objeto>& objetos,int& cantidadTotal,int& nsel, vector<bool>& seleccionados){
    Matriz<int> mat(N+1, P+1, -1);
    cantidadTotal = recogeOroRec(N, P, objetos, mat);
    nsel = reconstruyeSeleccionados(objetos,P,seleccionados,mat);
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int P, N;
    cin >> P >> N;

	if (!std::cin)  // fin de la entrada
		return false;

    vector<objeto> objetos;

    int prof, oro;
    for(int i = 0; i < N; i++){
        cin >> prof >> oro;
        objetos.push_back(objeto(prof,oro));
    }

	// resolver el caso posiblemente llamando a otras funciones

	// escribir la solución
    int cantidadTotal, nsel;
    vector<bool> seleccionados(N);
    recogeOro(N,P,objetos,cantidadTotal,nsel,seleccionados);
    
    cout << cantidadTotal << "\n" << nsel << "\n";

    for(int i = 0; i < N; i++)
        if(seleccionados[i])
            cout << objetos[i].profundidad << " " << objetos[i].cantOro << "\n";

    cout << "---" << "\n";
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
