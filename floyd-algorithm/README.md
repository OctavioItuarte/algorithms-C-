# Algoritmo de Floyd-Warshall en C++

Este proyecto implementa el **algoritmo de Floyd-Warshall** en C++ para encontrar los **caminos mínimos entre todos los pares de vértices** en un grafo no dirigido con pesos. También calcula las **excentricidades** de cada vértice y determina el **centro del grafo**.

---

## ¿Qué hace el programa?

1. Define un **grafo no dirigido** con 5 vértices y aristas con pesos.
2. Calcula la **matriz de costos mínimos** entre todos los pares de vértices usando el algoritmo de Floyd.
3. Almacena los **puntos intermedios** en las rutas mínimas para reconstruir los caminos.
4. Calcula la **excentricidad** de cada vértice (la mayor distancia desde un vértice a cualquier otro).
5. Determina el **centro del grafo**, es decir, el vértice con la menor excentricidad.
6. Muestra los **caminos más cortos** entre cada par de vértices, junto con su costo.

---

## ¿Qué es el algoritmo de Floyd-Warshall?

Es un algoritmo de programación dinámica que encuentra el **camino más corto entre todos los pares de nodos** en un grafo ponderado (puede ser dirigido o no dirigido). Tiene una complejidad de **O(n³)**.

### Pasos del algoritmo:

1. Se inicializa una matriz `A` con los costos directos entre nodos (o infinito si no hay conexión).
2. Se exploran caminos usando nodos intermedios `k`, actualizando `A[i][j] = min(A[i][j], A[i][k] + A[k][j])`.
3. Se almacena en la matriz `P[i][j]` el nodo intermedio que permite mejorar el camino de `i` a `j`.

---

## Estructuras utilizadas

- `C[i][j]`: matriz de costos originales del grafo.
- `A[i][j]`: matriz de costos mínimos calculados.
- `P[i][j]`: matriz de caminos, guarda nodos intermedios.
- `T[i]`: excentricidad de cada vértice (distancia máxima desde `i` a otro vértice).
- Clase `GrafoND`: grafo no dirigido (en `GrafoND.h` y `GrafoND.cpp`).

