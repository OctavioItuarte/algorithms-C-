# Algoritmos de Grafos en C++

Este proyecto implementa varios algoritmos clásicos sobre grafos dirigidos y no dirigidos utilizando C++.

## Características

- Soporte para **Grafos Dirigidos (GrafoD)** y **Grafos No Dirigidos (GrafoND)**.
- Implementación de algoritmos clásicos:
  - **Búsqueda en Profundidad (DFS)**
  - **Búsqueda en Amplitud (BFS)**
  - **Orden de Postorden**
  - **Componentes fuertemente conexas**
  - **Componentes conexas**
  - **Puntos de articulación (articulation points)**
  - **Dijkstra** (caminos mínimos desde un nodo a todos los demás)
  - **Floyd-Warshall** (caminos mínimos entre todos los pares de nodos)
- Uso de estructuras auxiliares:
  - `Sets` para componentes conexas
  - `heapDijkstra.h` y `AristaCompleta.h` para aristas y caminos
- Sobrecarga de `operator<<` para imprimir grafos
