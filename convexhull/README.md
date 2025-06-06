# Envoltura Convexa en C++ (Convex Hull)

### Proyecto académico para prácticas de geometría computacional y algoritmos. Implementa dos algoritmos clásicos para hallar la envoltura convexa de un conjunto de puntos en el plano.

- **Jarvis March** (también conocido como el método del regalo).
  - Complejidad: O(nh), donde n es el número de puntos y h el número de puntos en la envoltura.
  - Recorre los puntos envolviendo el conjunto como si fuera un hilo alrededor.
- **QuickHull** (Divide y conquista).
  - Complejidad promedio: O(n log n)
  - Divide el conjunto en mitades recursivamente encontrando los puntos más lejanos.

## Descripción

La **envoltura convexa** de un conjunto de puntos es el polígono convexo más pequeño que contiene a todos los puntos del conjunto. Es útil en geometría computacional, visualización de datos, reconocimiento de patrones, entre otros.

El usuario ingresa puntos manualmente y elige qué algoritmo usar para hallar la envolvente convexa. Al finalizar, se muestran los puntos del contorno en orden.

## Notas
- El programa pide las coordenadas una por una (X, Y).
- Elige 'J' para usar el algoritmo Jarvis March, o 'Q' para QuickHull.
- El orden de impresión de los puntos depende del algoritmo.
- Usa Lista como estructura auxiliar para almacenar y evitar duplicados en la solución.
