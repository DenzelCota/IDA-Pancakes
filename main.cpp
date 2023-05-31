#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <stack>
#include <climits>
#include <vector>
using namespace std;

// Heurística
int calcularDesorden(std::string secuencia) {
    int contador = 0;
    if (secuencia[0] != 'a' && secuencia[0] != 'b')
        contador = 1;
    for (int i = 0; i < secuencia.size() - 1; i++)
        if (std::abs(secuencia[i] - secuencia[i + 1]) > 1)
            contador++;
    return contador;
}

// Función para invertir elementos
void invertir(std::string& str, int i) {
    std::reverse(str.begin(), str.begin() + i + 1);
}

std::string ida_estrella(std::string inicio, std::string fin, int limite_profundidad, int& contador, int limite_f) {
    int siguiente_limite_f = INT_MAX;
    std::set<std::string> visitados;
    std::vector<std::string> camino;
    std::stack<std::string> pila_dfs;
    pila_dfs.push(inicio);
    camino.push_back(inicio);
    visitados.insert(inicio);
    contador++;

    while (!pila_dfs.empty()) {
        std::string actual = pila_dfs.top();
        pila_dfs.pop();
        camino.pop_back();

        if (actual == fin)
            return actual;

        if (camino.size() >= limite_profundidad)
            continue;

        for (int i = 1; i < actual.size(); i++) {
            std::string siguiente = actual;
            invertir(siguiente, i);
            if (visitados.count(siguiente) == 0 && calcularDesorden(siguiente) + camino.size() + 1 <= limite_f) {
                visitados.insert(siguiente);
                pila_dfs.push(siguiente);
                camino.push_back(siguiente);
                contador++;
            }
            else if (calcularDesorden(siguiente) + camino.size() + 1 < siguiente_limite_f) {
                siguiente_limite_f = calcularDesorden(siguiente) + camino.size() + 1;
            }
        }
    }

    return "";
}

int main() {
    int longitud;
    std::cout << "Introduzca la longitud de la cadena a ordenar (maximo 26): ";
    std::cin >> longitud;
    longitud = std::min(longitud, 26); // limitamos a 26

    std::string abc = "abcdefghijklmnopqrstuvwxyz";
    std::string panqueques = abc.substr(0, longitud);
    std::string panquequesOrdenados = panqueques;
    std::random_shuffle(panqueques.begin(), panqueques.end());

    std::cout << "Panqueques desordenados: " << panqueques << "\n\n";

    int contador = 0;
    int limite_profundidad = 1;
    std::string resultado;
    int limite_f = calcularDesorden(panqueques);

    while (resultado == "") {
        resultado = ida_estrella(panqueques, panquequesOrdenados, limite_profundidad, contador, limite_f);
        if (resultado == "")
            limite_f = limite_profundidad;
        limite_profundidad++;
    }
 std::cout << "Panqueques ordenados: " << panquequesOrdenados << "\n\n";
    if (resultado != "") {
        std::cout << "Panqueques resueltos: " << resultado << std::endl;
    }
    else {
        std::cout << "No se encontro una solucion" << std::endl;
    }
    std::cout << "Nodos visitados: " << contador << std::endl;
    return 0;
}
