
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "IndexPQ.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Tarea
{
public:
    int inicio;
    int final;
    int periodo;

    Tarea(){}
    Tarea(int ini, int fin,int per):inicio(ini), final(fin), periodo(per) {}
};

struct Comp{
    bool operator()(Tarea const&a, Tarea const&b) const{
        return a.inicio < b.inicio;
    }
};


bool resuelveCaso() {
	// leer los datos de la entrada
    int N, M, T;
    cin >> N >> M >> T;

	if (!std::cin)  // fin de la entrada
		return false;
    
    IndexPQ<Tarea,Comp> pq(N+M);
    int x , y , z;
    for(int i = 0; i < N; i++){
        cin >> x >> y;
        pq.push(i,Tarea(x,y,-1));
    }

    for(int i = 0; i <M;i++){
         cin >> x >> y >> z;
        pq.push(i + N,Tarea(x,y,z));
    }

	// resolver el caso posiblemente llamando a otras funciones
    string sol = "NO\n";
    int nt = 0;
    while (!pq.empty() && sol == "NO\n")
    {
        int e = pq.top().elem;
        Tarea task = pq.top().prioridad;
        int ini, fin, per;
        ini = task.inicio;
        if (ini >= T) 
            break;
        fin = task.final;
        per = task.periodo;
        if(ini < nt){
            sol = "SI\n";
            break;
        }

        nt = max(nt, ini) + (fin - ini);
        
        if(per >= 0 && ini + per <= T){
            pq.update(e,Tarea(ini+per,fin+per,per));
        }
        else{
            pq.pop();
        }
    }
    
	// escribir la solución
    cout << sol;
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
