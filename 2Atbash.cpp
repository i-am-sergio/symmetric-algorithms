#include <iostream>
#include <string>
using namespace std;

// Alfabeto y su versión invertida
const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string alfabetoInvertido = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

/*
    @ Función: cifra un texto utilizando el cifrado Atbash
    @ Parámetros:
        @ texto: texto a cifrar
    @ Retorno: texto cifrado
*/
string cifrarAtbash(const string& texto) {
    string textoCifrado = "";
    for (char caracter : texto) { // Recorrer cada caracter
        if (isalpha(caracter)) {
            // Determinar si la letra es mayúscula o minúscula
            bool esMayuscula = isupper(caracter);
            // Convertir a mayúscula
            char letraMayuscula = toupper(caracter); 
            // Encontrar la posición en el alfabeto original
            size_t posicion = alfabeto.find(letraMayuscula);
            // Si se encuentra la letra, agregar su correspondiente en el alfabeto invertido
            if (posicion != string::npos) {// string::npos es un valor que indica que no se encontró la letra
                char nuevoCaracter = esMayuscula ? alfabetoInvertido[posicion] : tolower(alfabetoInvertido[posicion]);
                textoCifrado += nuevoCaracter;
            }
        } else {
            // Si no es una letra, se deja igual
            textoCifrado += caracter;
        }
    }
    return textoCifrado;
}

int main() {
    string texto = "criptoSISTEMA";

    // Cifrado Atbash
    string textoCifrado = cifrarAtbash(texto);
    cout << "Texto cifrado (Atbash): " << textoCifrado << endl;

    // Descifrado Atbash
    string textoDescifrado = cifrarAtbash(textoCifrado);
    cout << "Texto descifrado (Atbash): " << textoDescifrado << endl;

    return 0;
}
