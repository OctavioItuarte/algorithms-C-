# Envolvente Convexa con Graham Scan

Este proyecto implementa el algoritmo **Graham Scan** en C++ para calcular la **envolvente convexa** de un conjunto de puntos en el plano 2D, con opción de eliminar puntos interiores para mejorar la eficiencia del cálculo.

---

## ¿Qué es la envolvente convexa?

La envolvente convexa (o *Convex Hull*) de un conjunto de puntos es el **polígono convexo más pequeño** que contiene a todos los puntos del conjunto. Puede imaginarse como la forma que tomaría una banda elástica al envolver todos los puntos.

---

## ¿Qué hace este programa?

1. **Lee puntos** desde un archivo llamado `Puntos.txt`.
2. **Permite eliminar puntos interiores** con una heurística rápida basada en extremos geométricos.
3. **Ordena los puntos** según su ángulo con respecto a un punto de referencia (*ancla*).
4. **Aplica el algoritmo de Graham Scan** para construir la envolvente convexa.
5. **Muestra en consola** los puntos que forman el contorno de la envolvente.

---

## ¿Cómo funciona el algoritmo Graham Scan?

El algoritmo sigue estos pasos:

1. **Buscar el punto más bajo (ancla)**: Se elige el punto con menor coordenada `y`, y en caso de empate, el de menor coordenada `x`. Este punto servirá como referencia para ordenar los demás.

2. **Ordenar los puntos** por el ángulo que forman respecto al ancla y el eje X (ángulo polar). Si hay colineales, se mantiene el más alejado del ancla.

3. **Construir la envolvente**:
   - Se comienzan a apilar puntos.
   - Por cada nuevo punto, se revisa si hace un giro a la derecha (no convexo). Si es así, se descarta el punto anterior.
   - Se continúa hasta formar una figura cerrada y convexa.

Este proceso tiene complejidad `O(n log n)` debido al ordenamiento inicial.

---

## Características adicionales

- **Eliminación de puntos interiores (opcional):**  
  Si el usuario lo desea, se pueden eliminar puntos que seguramente están en el interior del conjunto, identificando aquellos fuera de un cuadrilátero formado por:
  - Máxima y mínima suma de coordenadas (`x + y`)
  - Máxima y mínima resta de coordenadas (`x - y`)

- **Ordenamiento personalizado:**  
  Implementa una variante del **Merge Sort** basada en el producto cruzado para comparar ángulos.
