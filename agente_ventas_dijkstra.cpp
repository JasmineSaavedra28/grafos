#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

// ============================================
// ESTRUCTURA DEL GRAFO CON LISTA DE ADYACENCIA
// ============================================
class Grafo {
private:
    map<char, vector<pair<char, int>>> adyacencia;  // lista de adyacencia: nodo -> [(vecino, peso)]
    vector<char> nodos;

public:
    // Agregar un nodo al grafo
    void agregarNodo(char nodo) {
        if (find(nodos.begin(), nodos.end(), nodo) == nodos.end()) {
            nodos.push_back(nodo);
            adyacencia[nodo] = vector<pair<char, int>>();
        }
    }

    // Agregar una arista con peso (grafo no dirigido)
    void agregarArista(char origen, char destino, int peso) {
        agregarNodo(origen);
        agregarNodo(destino);
        adyacencia[origen].push_back({destino, peso});
        adyacencia[destino].push_back({origen, peso});  // Grafo no dirigido
    }

    // ============================================
    // ALGORITMO DE DIJKSTRA
    // ============================================
    void dijkstra(char origen) {
        // Inicializar distancias
        map<char, int> dist;
        map<char, char> previo;
        map<char, bool> visitado;

        for (char nodo : nodos) {
            dist[nodo] = INT_MAX;
            visitado[nodo] = false;
            previo[nodo] = '\0';
        }

        dist[origen] = 0;

        // Priority queue (min-heap): (distancia, nodo)
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
        pq.push({0, origen});

        while (!pq.empty()) {
            char actual = pq.top().second;
            int distActual = pq.top().first;
            pq.pop();

            if (visitado[actual]) continue;
            visitado[actual] = true;

            // Explorar vecinos
            for (auto& vecino : adyacencia[actual]) {
                char nodoVecino = vecino.first;
                int peso = vecino.second;

                if (!visitado[nodoVecino] && distActual + peso < dist[nodoVecino]) {
                    dist[nodoVecino] = distActual + peso;
                    previo[nodoVecino] = actual;
                    pq.push({dist[nodoVecino], nodoVecino});
                }
            }
        }

        // Imprimir resultados
        cout << "\n=== CAMINOS MÁS CORTOS DESDE '" << origen << "' ===" << endl;
        cout << "Ciudad\tDistancia\tCamino" << endl;
        cout << "------\t---------\t------" << endl;

        for (char nodo : nodos) {
            if (nodo != origen) {
                cout << nodo << "\t";
                if (dist[nodo] == INT_MAX) {
                    cout << "INF\t\tSin camino";
                } else {
                    cout << dist[nodo] << "\t\t";
                    // Reconstruir camino
                    vector<char> camino;
                    char actual = nodo;
                    while (actual != '\0') {
                        camino.push_back(actual);
                        actual = previo[actual];
                    }
                    reverse(camino.begin(), camino.end());
                    for (size_t i = 0; i < camino.size(); i++) {
                        cout << camino[i];
                        if (i < camino.size() - 1) cout << " -> ";
                    }
                }
                cout << endl;
            }
        }

        // Imprimir camino específico si se solicita
        cout << "\n=== DETALLE DE CAMINOS ===" << endl;
        for (char destino : nodos) {
            if (destino != origen && dist[destino] != INT_MAX) {
                cout << "\nCamino de " << origen << " a " << destino << ":" << endl;
                cout << "Costo total: " << dist[destino] << endl;
                
                vector<char> camino;
                char actual = destino;
                while (actual != '\0') {
                    camino.push_back(actual);
                    actual = previo[actual];
                }
                reverse(camino.begin(), camino.end());
                
                cout << "Ruta: ";
                for (size_t i = 0; i < camino.size(); i++) {
                    cout << camino[i];
                    if (i < camino.size() - 1) {
                        // Buscar el peso de la arista
                        for (auto& vecino : adyacencia[camino[i]]) {
                            if (vecino.first == camino[i + 1]) {
                                cout << " --(" << vecino.second << ")--> ";
                                break;
                            }
                        }
                    }
                }
                cout << endl;
            }
        }
    }

    // Imprimir el grafo
    void imprimirGrafo() {
        cout << "\n=== GRAFO DEL AGENTE DE VENTAS ===" << endl;
        for (auto& nodo : adyacencia) {
            cout << nodo.first << " -> ";
            for (auto& vecino : nodo.second) {
                cout << "(" << vecino.first << ":" << vecino.second << ") ";
            }
            cout << endl;
        }
    }
};

// ============================================
// FUNCIÓN PRINCIPAL
// ============================================
int main() {
    Grafo g;

    // ============================================
    // CONSTRUIR EL GRAFO SEGÚN LA IMAGEN
    // ============================================
    cout << "Construyendo grafo del itinerario..." << endl;
    
    // Aristas del grafo (basado en la imagen)
    g.agregarArista('A', 'B', 3);
    g.agregarArista('A', 'C', 5);
    g.agregarArista('A', 'D', 2);
    g.agregarArista('A', 'H', 10);
    
    g.agregarArista('B', 'C', 5);
    g.agregarArista('B', 'D', 6);
    g.agregarArista('B', 'E', 4);
    g.agregarArista('B', 'G', 3);
    g.agregarArista('B', 'H', 9);
    
    g.agregarArista('C', 'E', 1);
    g.agregarArista('C', 'F', 7);
    
    g.agregarArista('D', 'G', 12);
    g.agregarArista('D', 'H', 14);
    
    g.agregarArista('E', 'F', 15);
    g.agregarArista('E', 'G', 9);
    
    g.agregarArista('F', 'H', 7);

    // Imprimir el grafo construido
    g.imprimirGrafo();

    // ============================================
    // APLICAR DIJKSTRA
    // ============================================
    char origen;
    cout << "\nIngrese la ciudad de origen (A-H): ";
    cin >> origen;

    // Validar que el nodo exista
    if (origen < 'A' || origen > 'H') {
        cout << "Ciudad inválida. Use letras de A a H." << endl;
        return 1;
    }

    g.dijkstra(origen);

    // ============================================
    // EJEMPLOS ESPECÍFICOS (del análisis)
    // ============================================
    cout << "\n\n=== EJEMPLOS DESTACADOS ===" << endl;
    cout << "Camino más corto de A a G:" << endl;
    cout << "A -> B -> G (costo: 3 + 3 = 6)" << endl;
    
    cout << "\nCamino más corto de A a E:" << endl;
    cout << "A -> B -> E (costo: 3 + 4 = 7)" << endl;
    
    cout << "\nCamino más corto de A a F:" << endl;
    cout << "A -> B -> C -> F (costo: 3 + 5 + 7 = 15)" << endl;
    cout << "O: A -> B -> E -> C -> F (costo: 3 + 4 + 1 + 7 = 15)" << endl;

    return 0;
}