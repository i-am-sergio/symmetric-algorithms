# Algoritmos de Cifrado Simétrico

Este proyecto presenta la implementación de seis algoritmos clásicos de cifrado simétrico, cada uno con enfoques únicos para proteger la información. A continuación se describen brevemente cada uno de los algoritmos:

## 1. Cifrado César
El Cifrado César es un método de sustitución en el que cada letra del texto se reemplaza por otra letra que se encuentra un número fijo de posiciones más adelante en el alfabeto. Este desplazamiento es circular, lo que significa que después de la 'Z' se regresa a la 'A'.

## 2. Cifrado Atbash
El Cifrado Atbash es otro método de sustitución que invierte el alfabeto. Cada letra se sustituye por su opuesta en el alfabeto, es decir, 'A' se convierte en 'Z', 'B' en 'Y', y así sucesivamente. Este cifrado es simple pero efectivo para ocultar información.

## 3. Cifrado Playfair
El Cifrado Playfair utiliza un cuadrado de 5x5 para cifrar pares de letras. Si las letras en el par son iguales, se agrega una letra de relleno. El cifrado se basa en la posición de las letras en el cuadrado, utilizando reglas específicas para la sustitución.

## 4. Cifrado Polybios
El Cifrado Polybios emplea una cuadrícula de 5x5 para representar letras con pares de coordenadas. Cada letra se sustituye por su correspondiente par de números, proporcionando una forma sencilla de cifrado que es fácil de usar y recordar.

## 5. Cifrado AMSCO
El Cifrado AMSCO combina sustitución y transposición. Primero, las letras del texto se reorganizan utilizando una clave, y luego se aplican sustituciones. Este método permite una mayor complejidad en el cifrado, mejorando la seguridad de los datos.

## 6. Cifrado por Ruta
El Cifrado por Ruta se basa en patrones de recorrido en una cuadrícula. Utiliza diferentes tipos de rutas (zigzag, espirales, diagonales) para cifrar el texto, lo que añade una capa adicional de complejidad y adaptabilidad a los métodos de cifrado.

## Conclusiones
Estos algoritmos ilustran la variedad de técnicas disponibles en la criptografía simétrica. Desde métodos simples como el Cifrado César y Atbash hasta enfoques más complejos como el Cifrado AMSCO y el Cifrado por Ruta, cada algoritmo tiene sus propias características y aplicaciones. Este trabajo busca proporcionar una comprensión profunda de estos métodos, su implementación y su relevancia en la protección de datos.


# Comparacion: Algoritmos de Cifrado Simétrico

| Algoritmo                | Tipo                 | Complejidad      |
|--------------------------|----------------------|-------------------|
| Cifrado César            | Sustitución          | Baja              |
| Cifrado Atbash           | Sustitución          | Baja              |
| Cifrado Playfair         | Sustitución y Transposición | Media        |
| Cifrado Polybios         | Sustitución          | Baja              |
| Cifrado AMSCO            | Sustitución y Transposición | Alta         |
| Cifrado por Ruta         | Sustitución y Transposición | Media        |
