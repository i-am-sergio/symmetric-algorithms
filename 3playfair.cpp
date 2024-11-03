#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Alfabeto sin la 'J'
const string alfabeto = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // 'J' se combina con 'I'

/*
    @ Función: Crear la tabla de Playfair
    @ Parámetros:
        @ clave: clave para crear la tabla
    @ Retorno: tabla de Playfair (5x5)
*/
vector<vector<char>> crearTabla(const string& clave) {
    vector<vector<char>> tabla(5, vector<char>(5));
    string claveLimpiada;
    vector<bool> letraUsada(25, false);

    // Limpiar la clave y crear la tabla
    for (char c : clave) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Combinar J con I
        if (isalpha(c) && !letraUsada[c - 'A']) {
            letraUsada[c - 'A'] = true;
            claveLimpiada += c;
        }
    }

    // Agregar letras restantes del alfabeto
    for (char c : alfabeto) {
        if (!letraUsada[c - 'A']) {
            claveLimpiada += c;
        }
    }

    // Llenar la tabla
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tabla[i][j] = claveLimpiada[i * 5 + j];
        }
    }
    
    return tabla;
}

/*
    @ Función: Encontrar la posición de un carácter en la tabla
    @ Parámetros:
        @ c: carácter a buscar
        @ tabla: tabla de Playfair
    @ Retorno: posición del carácter en la tabla
*/
pair<int, int> encontrarPosicion(char c, const vector<vector<char>>& tabla) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabla[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // No encontrado
}

/*
    @ Función: Preparar el texto para cifrar
    @ Parámetros:
        @ texto: texto a preparar
    @ Retorno: texto preparado
*/
string prepararTexto(string texto) {
    string resultado;
    for (char c : texto) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Combinar J con I
        if (isalpha(c)) {
            resultado += c;
        }
    }

    // Manejar pares
    string resultadoFinal;
    for (size_t i = 0; i < resultado.length(); i++) {
        resultadoFinal += resultado[i];
        if (i + 1 < resultado.length()) {
            if (resultado[i] == resultado[i + 1]) {
                resultadoFinal += 'X'; // Añadir 'X' si hay letras repetidas
            } else {
                resultadoFinal += resultado[i + 1];
                i++; // Saltar la siguiente letra
            }
        }
    }
    
    // Si el texto final es impar, agregar 'X'
    if (resultadoFinal.length() % 2 != 0) {
        resultadoFinal += 'X';
    }

    return resultadoFinal;
}

/*
    @ Función: Cifrar utilizando Playfair
    @ Parámetros:
        @ clave: clave para cifrar
        @ texto: texto a cifrar
    @ Retorno: texto cifrado
*/
string cifrarPlayfair(const string& clave, const string& texto) {
    auto tabla = crearTabla(clave);
    string textoPreparado = prepararTexto(texto);
    string textoCifrado;

    for (size_t i = 0; i < textoPreparado.length(); i += 2) {
        char a = textoPreparado[i];
        char b = textoPreparado[i + 1];
        
        auto posA = encontrarPosicion(a, tabla);
        auto posB = encontrarPosicion(b, tabla);

        if (posA.first == posB.first) { // Mismo fila
            textoCifrado += tabla[posA.first][(posA.second + 1) % 5];
            textoCifrado += tabla[posB.first][(posB.second + 1) % 5];
        } else if (posA.second == posB.second) { // Misma columna
            textoCifrado += tabla[(posA.first + 1) % 5][posA.second];
            textoCifrado += tabla[(posB.first + 1) % 5][posB.second];
        } else { // Diferentes filas y columnas
            textoCifrado += tabla[posA.first][posB.second];
            textoCifrado += tabla[posB.first][posA.second];
        }
    }

    return textoCifrado;
}

// Función de descifrado Playfair
string descifrarPlayfair(const string& clave, const string& texto) {
    auto tabla = crearTabla(clave);
    string textoDescifrado;

    for (size_t i = 0; i < texto.length(); i += 2) {
        char a = texto[i];
        char b = texto[i + 1];
        
        auto posA = encontrarPosicion(a, tabla);
        auto posB = encontrarPosicion(b, tabla);

        if (posA.first == posB.first) { // Mismo fila
            textoDescifrado += tabla[posA.first][(posA.second + 4) % 5];
            textoDescifrado += tabla[posB.first][(posB.second + 4) % 5];
        } else if (posA.second == posB.second) { // Misma columna
            textoDescifrado += tabla[(posA.first + 4) % 5][posA.second];
            textoDescifrado += tabla[(posB.first + 4) % 5][posB.second];
        } else { // Diferentes filas y columnas
            textoDescifrado += tabla[posA.first][posB.second];
            textoDescifrado += tabla[posB.first][posA.second];
        }
    }

    return textoDescifrado;
}

int main() {
    string texto = "ATAQUEINMINENTE"; // Clave para el cifrado
    string clave = "SEGURIDAD"; // Texto a cifrar

    // Cifrado Playfair
    string textoCifrado = cifrarPlayfair(clave, texto);
    cout << "Texto cifrado (Playfair): " << textoCifrado << endl;

    // Descifrado Playfair
    string textoDescifrado = descifrarPlayfair(clave, textoCifrado);
    cout << "Texto descifrado (Playfair): " << textoDescifrado << endl;

    return 0;
}
