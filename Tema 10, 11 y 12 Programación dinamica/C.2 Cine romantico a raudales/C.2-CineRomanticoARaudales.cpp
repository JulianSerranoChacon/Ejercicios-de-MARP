
    /*@ <authors>
    *
    * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
    *
    *@ </authors> */

    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
#include <algorithm>
    using namespace std;

    //#include "..."  // propios o los de las estructuras de datos de clase

    /*@ <answer>    
Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 EXPLICACIÓN:
 Resolvemos el problema mediante Programación Dinámica con una estructura similar a la de 
 "Justificación de textos", donde evaluamos el problema desde el final hacia el principio.
 
 1. Ordenamos las películas por su tiempo de INICIO de forma ascendente.
 2. Definimos `siguiente[i]` como el índice de la primera película compatible que va después de `i` 
    (es decir, la primera cuyo `inicio` es >= `peliculas[i].fin + 10`). Para encontrarla de forma 
    eficiente, usamos una función de búsqueda binaria manual (`buscarSiguiente`).
 3. Definimos `dp[i]` como el máximo tiempo de películas que se puede ver considerando el subconjunto 
    de películas que van desde la película `i` hasta el final (`N-1`).
    Para cada película `i`, tenemos dos decisiones:
    - NO ver la película `i`: el resultado será el mismo que `dp[i + 1]`.
    - SÍ ver la película `i`: sumamos su duración y saltamos a su película compatible: 
      `peliculas[i].duracion + dp[siguiente[i]]`.
 4. El caso base es `dp[N] = 0`. El resultado final estará en `dp[0]`.
 
 COSTE:
 - Ordenación inicial: O(N log N).
 - Precomputar el vector 'siguiente' mediante búsqueda binaria manual: O(N log N).
 - Rellenar la tabla DP: O(N), ya que cada estado se calcula en O(1).
 Coste Temporal Total: O(N log N)
 Coste Espacial Total: O(N) para los vectores de películas y la tabla DP.
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct pelicula
{
    int inicio; // Tiempo absoluto de inicio en minutos
    int fin;    // Tiempo absoluto de fin en minutos
    int duracion;

    pelicula(std::istream & flujo) {
        int dia;
        string shora;
        flujo >> dia;
        flujo >> shora;
        int hora = stoi(shora.substr(0, 2));
        int minutos = stoi(shora.substr(3, 2));
        flujo >> duracion;

        // Convertir todo a minutos absolutos
        inicio = (dia - 1) * 24 * 60 + hora * 60 + minutos;
        fin = inicio + duracion;
    }
};

// Ordenamos por hora de inicio (esencial para la estructura de atrás hacia adelante)
bool ordenarPorInicio(pelicula const& a, pelicula const& b) {
    if (a.inicio != b.inicio)
        return a.inicio < b.inicio;
    return a.fin < b.fin;
}

// Búsqueda binaria manual para encontrar la primera película que empieza >= tiempoLimite
int buscarSiguiente(vector<pelicula> const& peliculas, int izq, int tiempoLimite) {
    int der = peliculas.size() - 1;
    int resultado = peliculas.size(); // Si no hay ninguna, devuelve N (fuera de rango)

    while (izq <= der) {
        int mitad = izq + (der - izq) / 2;
        if (peliculas[mitad].inicio >= tiempoLimite) {
            resultado = mitad;
            der = mitad - 1; // Intentar buscar una todavía más cercana a la izquierda
        } else {
            izq = mitad + 1;
        }
    }
    return resultado;
}

int eligePeliculas(vector<pelicula> & peliculas){
    int n = peliculas.size();
    if (n == 0) return 0;

    // 1. Ordenar por tiempo de inicio
    sort(peliculas.begin(), peliculas.end(), ordenarPorInicio);

    // `dp[i]` guarda el máximo tiempo que se puede obtener desde la película `i` hasta el final.
    // Tamaño n + 1 para tener el caso base dp[n] = 0 de forma segura.
    vector<int> sol(n + 1, 0);

    // Rellenamos el vector DP de atrás hacia adelante (como en justificación de textos)
    for (int i = n - 1; i >= 0; --i) {
        // Opción 1: No elegir la película `i`. Pasamos directamente a evaluar la siguiente.
        int opcionNoElegir = sol[i + 1];

        // Opción 2: Elegir la película `i`.
        // Buscamos cuál es la primera película compatible que empieza después de terminar la actual (+ 10 min).
        int tiempoLimite = peliculas[i].fin + 10;
        int sigComp = buscarSiguiente(peliculas, i + 1, tiempoLimite);
        
        int opcionElegir = peliculas[i].duracion + sol[sigComp];

        // Nos quedamos con la mejor decisión para el estado `i`
        sol[i] = max(opcionNoElegir, opcionElegir);
    }

    // El resultado final para todo el catálogo de películas empezando desde el principio está en dp[0]
    return sol[0];
}

    bool resuelveCaso() {
        // leer los datos de la entrada
        int N;
        cin >> N;

        if (N == 0)
            return false;

        vector<pelicula> peliculas;
        for(int i = 0; i<N; i++)
            peliculas.push_back(pelicula(cin));
            
        // resolver el caso posiblemente llamando a otras funciones

        // escribir la solución
        cout << eligePeliculas(peliculas) << "\n";

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
