#include <iostream>
#include <string>
using namespace std;

/*
    @ Funcion: se cifra desplazando cada letra un numero fijo de posiciones
    @ Parametros: 
        @@ texto: texto a cifrar
        @@ desplazamiento: num posiciones a desplazar
    @ Retorno: texto cifrado
*/

string cifrarCesar(const string& texto, int desplazamiento) {
    string textoCifrado = "";
    for (char caracter : texto) { // Recorrer cada caracter del texto
        if (isalpha(caracter)) { // Verificar si es una letra
            // Determinar el inicio del alfabeto
            // 'A' = 65, 'a' = 97
            char inicio = isupper(caracter) ? 'A' : 'a'; 
            // Desplazar y mantener en el rango del alfabeto
            char nuevoCaracter = inicio + (caracter - inicio + desplazamiento) % 26;
            textoCifrado += nuevoCaracter; // Agregar el caracter cifrado
        } else {
            textoCifrado += caracter;
        }
    }
    return textoCifrado;
}

/*
    @ Funcion: Se utiliza el negativo del desplazamiento para descifrar
    @ Parametros: 
        @@ texto: texto a descifrar
        @@ desplazamiento: num posiciones a desplazar
    @ Retorno: texto descifrado
*/
string descifrarCesar(const string& texto, int desplazamiento) {
    return cifrarCesar(texto, -desplazamiento);
}

int main() {
    string texto = "SEGURIDAD";
    int desplazamiento = 3;
    // Cifrado
    string textoCifrado = cifrarCesar(texto, desplazamiento);
    cout << "Texto cifrado: " << textoCifrado << endl;
    // Descifrado
    string textoDescifrado = descifrarCesar(textoCifrado, desplazamiento);
    cout << "Texto descifrado: " << textoDescifrado << endl;

    return 0;
}
