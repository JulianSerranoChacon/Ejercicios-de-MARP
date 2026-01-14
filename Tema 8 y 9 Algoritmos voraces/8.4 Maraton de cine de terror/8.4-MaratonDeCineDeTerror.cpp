
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

El problema consiste en seleccionar el mayor número posible de películas
que Deborah pueda ver completas, teniendo en cuenta que no pueden solaparse
y que entre una película y la siguiente deben transcurrir al menos 10 minutos.

Cada película se transforma en un intervalo de tiempo expresado en minutos
absolutos desde el inicio del día 1. Para ello se convierte el día, la hora
y los minutos a un único valor numérico. El final del intervalo se obtiene
sumando la duración de la película.

La estrategia utilizada es voraz: se seleccionan siempre primero las
películas que terminan antes. Para ello se introducen todas las películas
en una cola de prioridad ordenada por su instante de finalización.
A continuación se van extrayendo en ese orden y se elige una película
si su hora de inicio es posterior o igual al final de la última película
vista, teniendo en cuenta los 10 minutos de descanso.

Este algoritmo es óptimo para el problema de selección de intervalos.

El coste temporal es O(N log N), debido a las inserciones y extracciones
de la cola de prioridad, y el coste en memoria es O(N).

@ </answer> */


struct Pelicula {
    long long inicio;
    long long fin;

    Pelicula() {}
    Pelicula(int ini, int f): inicio(ini),fin(f) {}
};

bool operator<(Pelicula const& a, Pelicula const& b) {
    return a.fin < b.fin;
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N;
    cin >> N;
	if (N == 0)  // fin de la entrada
		return false;

    PriorityQueue<Pelicula,less<Pelicula>> pelis;
    int dia, hora, minutos,duracion,fecha;
    string h;
    for (int i = 0; i<N;i++){
        cin >> dia >> h >> duracion;

        hora = stoi(h.substr(0, 2));
        minutos = stoi(h.substr(3, 2));

        fecha = (dia * 60 * 24) + (hora * 60) + minutos;
        pelis.push(Pelicula(fecha, fecha + duracion));
    }
    long long finUltima = -1;
    int contador = 0;
    Pelicula p;

    while (!pelis.empty())
    {
        p = pelis.top();
        pelis.pop();

        if (p.inicio >= finUltima) {
            contador++;
            finUltima = p.fin + 10;  // 10 minutos de descanso
        }
    }

	// resolver el caso posiblemente llamando a otras funciones
    cout << contador << "\n";

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
