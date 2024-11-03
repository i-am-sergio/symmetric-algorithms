#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

template <typename T> using matrix = vector<vector<T>>;

/*
    @ Funcion: Crear la matriz de Polybios
    @ Retorno: matriz de Polybios 5x5
*/
matrix<char> crearMatrizPolybios() {
    matrix<char> matriz(5, vector<char>(5));
    string letras = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // La 'J' se representa con la 'I'
    int indice = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = letras[indice++];
        }
    }
    return matriz;
}

/*
    @ Funcion: Encontrar la posición de una letra en la matriz
    @ Parametros:
        @ matriz: matriz de Polybios
        @ letra: letra a buscar
    @ Retorno: posición de la letra en la matriz
*/
pair<int, int> encontrarPosicion(const matrix<char>& matriz, char letra) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matriz[i][j] == letra) {
                return {i + 1, j + 1}; // Retornamos 1-indexado
            }
        }
    }
    return {-1, -1}; // Caso de error
}

/*
    @ Funcion: Cifrar un mensaje utilizando Polybios
    @ Parametros:
        @ mensaje: mensaje a cifrar
        @ matriz: matriz de Polybios
    @ Retorno: mensaje cifrado
*/
string cifrarPolybios(const string& mensaje, const matrix<char>& matriz) {
    string mensajeCifrado;

    for (char letra : mensaje) {
        if (isalpha(letra)) {
            letra = toupper(letra);
            if (letra == 'J') letra = 'I'; // Reemplazar 'J' por 'I'
            auto [fila, columna] = encontrarPosicion(matriz, letra);
            mensajeCifrado += to_string(fila) + to_string(columna) + " ";
        } else {
            mensajeCifrado += letra; // Mantener espacios y otros caracteres
        }
    }

    return mensajeCifrado;
}

/*
    @ Funcion: Descifrar un mensaje cifrado con Polybios
    @ Parametros:
        @ mensajeCifrado: mensaje cifrado
        @ matriz: matriz de Polybios
    @ Retorno: mensaje descifrado
*/
string descifrarPolybios(const string& mensajeCifrado, const matrix<char>& matriz) {
    string mensajeDescifrado;
    int i = 0;

    while (i < mensajeCifrado.size()) {
        if (isdigit(mensajeCifrado[i]) && i + 1 < mensajeCifrado.size() && isdigit(mensajeCifrado[i + 1])) {
            int fila = stoi(string(1, mensajeCifrado[i])) - 1; // Convertir a entero y restar 1
            int columna = stoi(string(1, mensajeCifrado[i + 1])) - 1; // Convertir a entero y restar 1

            mensajeDescifrado += matriz[fila][columna];
            i += 2; // Avanzar dos posiciones
        } else {
            mensajeDescifrado += mensajeCifrado[i];
            i++;
        }
    }

    return mensajeDescifrado;
}


int main() {
    matrix<char> matriz = crearMatrizPolybios();
    string mensaje;

    cout << "Ingrese el mensaje a cifrar: ";
    getline(cin, mensaje);

    string mensajeCifrado = cifrarPolybios(mensaje, matriz);
    cout << "Mensaje cifrado: " << mensajeCifrado << endl;

    string mensajeDescifrado = descifrarPolybios(mensajeCifrado, matriz);
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}
