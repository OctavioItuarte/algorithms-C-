# Conjunto Mínimo de Llaves para Abrir Cerraduras

Este programa resuelve el problema de encontrar el conjunto mínimo de llaves necesario para abrir un conjunto de cerraduras, utilizando dos métodos:

- **Backtracking** (búsqueda exhaustiva con poda)
- **Aproximación** (algoritmo voraz)

---

## Descripción del Problema

Dada una matriz binaria donde:

- Las **filas representan llaves**
- Las **columnas representan cerraduras**
- `Mat[i][j] = 1` significa que la llave `i` abre la cerradura `j`

El objetivo es determinar el conjunto mínimo de llaves que puede abrir todas las cerraduras.

---

## Instrucciones de Uso

1. Ejecuta el programa.
2. Ingresa la cantidad de llaves (`m`) y cerraduras (`n`).
3. Para cada llave, especifica cuántas cerraduras abre y cuáles (numeradas del `1` al `n`).
4. Selecciona el algoritmo:
   - `1` → Backtracking
   - `2` → Aproximación
   - `3` → Ambos

---

## Algoritmos Implementados

### 1. Backtracking

- Evalúa todas las combinaciones posibles de llaves.
- Utiliza poda para reducir el espacio de búsqueda.
- **Completo**, pero costoso para `n > 20`.

### 2. Aproximación (Set Cover)

- Escoge la llave que abre la mayor cantidad de cerraduras restantes.
- Remueve cerraduras cubiertas y repite.
- **No garantiza óptimo**, pero es **rápido y eficiente**.
