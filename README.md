# osm-routing-engine
Sistema de Procesamiento de Mapas y Rutas en C++

Este proyecto es un motor de procesamiento de mapas y cálculo de rutas desarrollado en C++. Es capaz de leer datos reales de OpenStreetMap (formato XML), procesar la información geográfica y calcular el camino más corto entre dos Puntos de Interés (POIs).

Desarrollado como proyecto académico para la asignatura de Laboratorio de Programación en la Universitat Autònoma de Barcelona (UAB).

Características Principales

- Parseo de datos reales (XML): Lectura y extracción de nodos, vías y metadatos de archivos .osm utilizando la librería Xerces-C++.
- Estructuras de Datos Avanzadas: Construcción de Grafos ponderados para modelar la red de calles y caminos.
  - Implementación desde cero de un BallTree (árbol binario espacial) para la partición del espacio           geográfico.
- Algoritmia Espacial: Cálculo de distancias geográficas reales mediante la Fórmula del Haversine.
  - Búsqueda del nodo más cercano optimizada mediante la estructura BallTree.
  - Algoritmo de búsqueda del camino más corto sobre el grafo de coordenadas.
- Arquitectura de Software: Diseño basado en Programación Orientada a Objetos (POO) con herencia y polimorfismo. 

Tecnologías y Herramientas

- Lenguaje principal: C++
- Librerías: STL (Standard Template Library), Xerces-C++ (XML Parser)
- Arquitectura: DLL (Dynamic-Link Library) para integración multiplataforma.
- Frontend (Proporcionado por la UAB): C# .NET Core (WPF)

Retos Técnicos Superados

El mayor reto técnico de este proyecto consistió en desacoplar los Puntos de Interés (restaurantes, tiendas, etc.) de los nodos transitables (caminos). Para resolver a qué calle pertenece un local concreto de forma eficiente, se implementó un árbol BallTree que divide el espacio geográfico por radios, permitiendo realizar búsquedas espaciales recursivas (1NN) con una complejidad temporal muy inferior a la fuerza bruta.

---
Desarrollado por Víctor Segura y Èric Medina - Estudiantes de Ingeniería Informática en la UAB.
