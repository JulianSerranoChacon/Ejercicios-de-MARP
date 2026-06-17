#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>

El problema se resuelve mediante programación dinámica como un problema
de cambio de monedas con uso ilimitado de cada puntuación. Para cada
valor intermedio hasta el objetivo se almacena el mínimo número de
dardos necesarios.

Se utiliza un único vector de tamaño O(V), donde V es el valor objetivo,
y se recorre de forma ascendente para permitir el uso ilimitado de los
sectores. Además, se guarda información para reconstruir una solución
óptima.

El coste temporal del algoritmo es O(S·V), siendo S el número de sectores,
y el coste en memoria es O(V).

@ </answer> */

bool resuelveCaso() {
    int V, S;
    cin >> V >> S;
    if (!cin) return false;

    vector<int> puntos(S);
    for (int i = 0; i < S; ++i)
        cin >> puntos[i];

    vector<EntInf> dp(V + 1, Infinito);
    vector<int> prev(V + 1, -1);

    dp[0] = 0;

    for (int i = 0; i < S; ++i) {
        int p = puntos[i];
        for (int v = p; v <= V; ++v) {
            if (dp[v - p] + 1 < dp[v]) {
                dp[v] = dp[v - p] + 1;
                prev[v] = p;
            }
        }
    }

    if (dp[V] == Infinito) {
        cout << "Imposible\n";
        return true;
    }

    // Reconstrucción
    vector<int> sol;
    int v = V;
    while (v > 0) {
        sol.push_back(prev[v]);
        v -= prev[v];
    }

    cout << sol.size() << ":";
    for (int x : sol)
        cout << " " << x;
    cout << "\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("1.in");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
