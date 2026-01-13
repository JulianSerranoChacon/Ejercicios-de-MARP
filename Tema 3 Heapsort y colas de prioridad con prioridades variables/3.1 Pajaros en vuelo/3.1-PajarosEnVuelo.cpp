
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "PriorityQueue.h" propios o los de las estructuras de datos de clase


/*@ <answer>

 Mantenemos la mediana de las edades usando dos colas con prioridad:
 una max-heap para la mitad inferior y una min-heap para la superior.
 Tras cada inserción de una pareja se reequilibran ambas estructuras
 y la edad del pájaro que ocupa la punta de la bandada es siempre
 el máximo de la mitad inferior.

 El coste es O(P log P), siendo P el número de parejas.

 @ </answer> */


// ================================================================
// Código de la solución
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int edadInicial, P;
    cin >> edadInicial >> P;
    if (edadInicial == 0 && P == 0) return false;

    PriorityQueue<int, greater<int>> izq;                 // max-heap
    PriorityQueue<int> der;   // min-heap

    // Insertamos el primer pájaro
    izq.push(edadInicial);

    for (int i = 0; i < P; i++) {
        int a, b;
        cin >> a >> b;

        // insertar a
        if (a <= izq.top()) izq.push(a);
        else der.push(a);

        // insertar b
        if (b <= izq.top()) izq.push(b);
        else der.push(b);

        // reequilibrar
        while (izq.size() > der.size() + 1) {
            der.push(izq.top());
            izq.pop();
        }
        while (der.size() > izq.size()) {
            izq.push(der.top());
            der.pop();
        }

        // salida tras cada pareja
        cout << izq.top();
        if (i + 1 < P) cout << " ";
    }
    cout << "\n";

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
