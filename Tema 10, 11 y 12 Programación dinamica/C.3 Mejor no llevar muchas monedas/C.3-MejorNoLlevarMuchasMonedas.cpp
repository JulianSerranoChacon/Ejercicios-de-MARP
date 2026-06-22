
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 1000000;
/*@ <answer>

El problema se resuelve mediante Programación Dinámica aplicando el enfoque del 
 problema del cambio de monedas con unidades limitadas. Para optimizar el coste temporal
 y evitar una tercera dimensión, se utiliza la descomposición binaria de las cantidades 
 de cada tipo de moneda. De este modo, cada tipo de moneda se divide en "paquetes" de 
 tamaños 1, 2, 4, 8... junto con el residuo. 
 
 Se utiliza un vector `dp` unidimensional donde `dp[j]` representa el número mínimo 
 de monedas necesarias para obtener el valor exacto `j`.
 
 Coste Temporal: O(N * log(Cantidad) * P), donde N es el número de tipos de monedas,
 Cantidad es el número máximo de monedas de un tipo, y P es el precio del coche.
 Coste Espacial: O(P), ya que solo necesitamos una fila para la transición de estados.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int cogerMonedas(int n, int P, vector<int> const& valores, vector<int> const& cantidades) {
    // dp[j] guardará el mínimo número de monedas para sumar exactamente 'j'
    vector<int> sol(P + 1, INF);
    sol[0] = 0; // Para sumar 0 necesitamos 0 monedas

    // Procesamos cada tipo de moneda
    for (int i = 0; i < n; ++i) {
        int c = cantidades[i];
        int v = valores[i];
        
        // Descomposición binaria de la cantidad disponible
        for (int k = 1; c > 0; k *= 2) {
            int tomado = min(k, c);
            c -= tomado;
            
            int valor_paquete = tomado * v;
            int monedas_paquete = tomado;
            
            // Recorremos de derecha a izquierda para evitar usar el mismo paquete más de una vez
            for (int j = P; j >= valor_paquete; --j) {
                if (sol[j - valor_paquete] != INF) {
                    sol[j] = min(sol[j], sol[j - valor_paquete] + monedas_paquete);
                }
            }
        }
    }

    return sol[P];
}

bool resuelveCaso() {
	// leer los datos de la entrada
    int N, P;
    cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;

    vector<int> valores(N);
    for(int i = 0; i <N; i++)
        cin >> valores[i];
    
    vector<int> cantidades(N);
    for(int i = 0; i <N; i++)
        cin >> cantidades[i];
    
    cin >> P;
	// resolver el caso posiblemente llamando a otras funciones
    int sol = cogerMonedas(N,P,valores,cantidades);
	// escribir la solución
    sol == INF? cout << "NO": cout << "SI " << sol;
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
