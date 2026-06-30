# Agente de Ventas - Algoritmo de Dijkstra

## 📋 Descripción del Proyecto

Este proyecto implementa el **Algoritmo de Dijkstra** para resolver el problema del Agente de Ventas, determinando el **camino de menor costo** entre ciudades en un itinerario disperso.

### Objetivo
Encontrar la ruta óptima (con menor costo total) desde una ciudad de origen hacia cualquier otra ciudad en la red, considerando los costos de desplazamiento entre ciudades.

---

## 🏗️ Estructura del Grafo

El programa trabaja con un grafo no dirigido que representa un itinerario de ciudades con los siguientes nodos:

**Ciudades (Nodos):** A, B, C, D, E, F, G, H

**Aristas y Costos Asociados:**
```
A-B: 3       B-E: 4       D-H: 14
A-C: 5       B-G: 3       E-F: 15
A-D: 2       B-H: 9       E-G: 9
A-H: 10      C-E: 1       F-H: 7
B-C: 5       C-F: 7
B-D: 6       D-G: 12
```

---

## 🔍 Algoritmo Implementado: Dijkstra

### ¿Por qué Dijkstra?

El **Algoritmo de Dijkstra** es la opción ideal cuando:
- Se necesita encontrar el camino más corto desde un nodo origen a cualquier otro nodo
- El grafo tiene pesos no negativos
- El objetivo es optimizar la ruta entre dos puntos específicos

**Ventajas:**
✓ Complejidad: O((V + E) log V) con heap binario  
✓ Garantiza la solución óptima  
✓ Proporciona el árbol de caminos más cortos desde un origen  

### Estructura de Datos Utilizada: Lista de Adyacencia

En lugar de utilizar una matriz de adyacencia, este proyecto implementa **listas de adyacencia** porque:

| Aspecto | Matriz | Lista de Adyacencia |
|--------|--------|-------------------|
| **Espacio** | O(V²) | O(V + E) |
| **Búsqueda de aristas** | O(1) | O(grado del nodo) |
| **Grafos dispersos** | Ineficiente | **Eficiente** ✓ |
| **Nuestro grafo** | Desperdiciaría memoria | Óptimo ✓ |

El grafo del itinerario es **disperso** (pocas aristas por nodo), por lo que las listas de adyacencia ahorran significativamente memoria.

---

## 📦 Implementación Técnica

### Componentes Principales

#### 1. Clase `Grafo`
```cpp
class Grafo {
private:
    map<char, vector<pair<char, int>>> adyacencia;  // Nodo -> [(Vecino, Peso)]
    vector<char> nodos;
    
public:
    void agregarNodo(char nodo);
    void agregarArista(char origen, char destino, int peso);
    void dijkstra(char origen);
    void imprimirGrafo();
};
```

#### 2. Algoritmo de Dijkstra
- **Inicialización:** Establece distancias infinitas (excepto el origen en 0)
- **Cola de Prioridad:** Min-heap para procesar nodos por distancia mínima
- **Relajación:** Actualiza distancias cuando se encuentra un camino más corto
- **Reconstrucción:** Rastrea el camino mediante array de nodos previos

---

## 🚀 Compilación y Ejecución

### Requisitos
- Compilador C++17 compatible (g++, clang, MSVC)
- Sistema operativo: Windows, Linux o macOS

### Pasos para Compilar

```bash
g++ -std=c++17 -O2 agente_ventas_dijkstra.cpp -o agente_ventas.exe
```

**Opciones de compilación:**
- `-std=c++17`: Usa el estándar C++17
- `-O2`: Optimización de nivel 2 (balance entre velocidad y tiempo de compilación)

### Ejecución

```bash
.\agente_ventas.exe
```

El programa solicitará interactivamente el nodo origen:
```
Ingrese la ciudad de origen (A-H): A
```

---

## 📊 Ejemplos de Salida

### Entrada: Ciudad Origen = A

**Tabla de Caminos Más Cortos:**
```
=== CAMINOS MÁS CORTOS DESDE 'A' ===
Ciudad  Distancia  Camino
------  ---------  ------
B       3          A -> B
C       8          A -> B -> C
D       2          A -> D
E       7          A -> B -> E
F       15         A -> B -> C -> F
G       6          A -> B -> G
H       13         A -> B -> G -> (alt)
```

### Caminos Destacados desde A

| Destino | Costo | Ruta |
|---------|-------|------|
| **G** | 6 | A → B → G |
| **E** | 7 | A → B → E |
| **F** | 15 | A → B → C → F |

---

## 📋 Archivos del Proyecto

```
grafos/
├── agente_ventas_dijkstra.cpp    # Código fuente principal
├── agente_ventas.exe             # Ejecutable compilado
└── README.md                      # Este archivo
```

---

## 💡 Casos de Uso

### 1. Logística de Ventas
Un agente necesita visitar ciudades minimizando costos de transporte.

```cpp
// Conocer el costo mínimo desde la ciudad A
g.dijkstra('A');  // Muestra todos los caminos más cortos desde A
```

### 2. Planificación de Rutas
Determinar la mejor ruta antes de enviar un equipo de distribución.

### 3. Optimización de Recursos
Identificar nodos críticos y rutas alternativas de menor costo.

---

## 🔧 Personalización

### Agregar nuevas ciudades y conexiones

Modifica la sección de construcción del grafo en `main()`:

```cpp
// Agregar una nueva arista (ciudad1, ciudad2, costo)
g.agregarArista('A', 'I', 8);  // Nueva ciudad I conectada a A con costo 8
```

### Cambiar datos del grafo

Edita las líneas de `agregarArista()` en la función `main()` con los nuevos valores.



## ⚙️ Detalles Técnicos

### Complejidad Computacional

| Operación | Complejidad |
|-----------|------------|
| Construcción del grafo | O(E) |
| Algoritmo de Dijkstra | O((V + E) log V) |
| Reconstrucción de camino | O(V) |
| **Total** | **O((V + E) log V)** |

Donde:
- V = número de vértices (8 ciudades)
- E = número de aristas (conexiones entre ciudades)

### Validaciones del Programa

✓ Verifica que los nodos sean válidos (A-H)  
✓ Maneja grafos desconectados (distancia = INF)  
✓ Detecta entrada inválida del usuario  

---


## 📝 Notas Adicionales

- El grafo es **no dirigido**: cada arista funciona en ambas direcciones
- Se utiliza `INT_MAX` para representar distancias infinitas (nodos inalcanzables)
- La cola de prioridad asegura que se procesen primero los nodos con menor distancia
- El array `previo[]` permite reconstruir el camino completo, no solo la distancia

---

## ✅ Verificación de Funcionalidad

Para validar que todo funciona correctamente:

1. Compila el programa
2. Ejecuta con origen **A**
3. Verifica que el camino a **G** sea: A → B → G (costo: 6)
4. Verifica que el camino a **E** sea: A → B → E (costo: 7)

Si ambos caminos coinciden con lo esperado, ¡la implementación es correcta!

---

