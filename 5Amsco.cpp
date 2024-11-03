#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
    @Funcion: Calcular el número de caracteres en cada columna
    @Parametros:
        @longitudClave: longitud de la clave
        @longitudTexto: longitud del texto
    @Retorno: vector con el número de caracteres en cada columna
*/
vector<int> calcularNumeroColumnas(int longitudClave, int longitudTexto) {
    vector<int> numColumnas(longitudClave, 0);
    int numCaracteres = 1;
    int indiceColumna = 0;
    int contador = longitudTexto;

    while (contador > 0) {
        numColumnas[indiceColumna] += numCaracteres;
        contador -= numCaracteres;
        indiceColumna = (indiceColumna + 1) % longitudClave;
        numCaracteres = (numCaracteres == 1) ? 2 : 1; // Alterna entre 1 y 2

        if (contador == 1 && numCaracteres == 2) { // Si estamos en la última letra
            numCaracteres = 1; // Solo añadir uno a la cuenta
        }
    }

    return numColumnas;
}

/*
    @Funcion: Cifrar un mensaje utilizando el cifrado AMSCO
    @Parametros:
        @textoACifrar: texto a cifrar
        @clave: clave para cifrar el mensaje
    @Retorno: mensaje cifrado
*/
string cifrarAMSCO(const string& textoACifrar, const string& clave) {
    int longitudClave = clave.length(); // Longitud de la clave
    int longitudTexto = textoACifrar.length();
    vector<int> numColumnas = calcularNumeroColumnas(longitudClave, longitudTexto);

    // Emparejar dígitos con el número de caracteres
    vector<pair<char, int>> digitosConCaracteres;
    for (int i = 0; i < longitudClave; ++i) {
        digitosConCaracteres.emplace_back(clave[i], numColumnas[i]);
    }

    // Dividir el texto
    vector<string> trozos(longitudClave);
    string textoRestante = textoACifrar;
    int contador = longitudTexto;
    int contadorClave = 0;
    int numCaracteres = 1;

    while (contador > 0) {
        char digito = digitosConCaracteres[contadorClave].first;
        int numColumna = digitosConCaracteres[contadorClave].second;
        
        trozos[digito - '1'] += textoRestante.substr(0, numCaracteres);
        textoRestante = textoRestante.substr(numCaracteres);
        contador -= numCaracteres;
        contadorClave = (contadorClave + 1) % longitudClave;
        numCaracteres = (numCaracteres == 1) ? 2 : 1; // Alterna entre 1 y 2

        if (numCaracteres == 2 && contador == 1) {
            numCaracteres = 1;
        }
    }

    // Unir el texto cifrado
    string textoCifrado;
    for (const auto& trozo : trozos) {
        textoCifrado += trozo;
    }

    return textoCifrado;
}

/*
    @Funcion: Descifrar un mensaje cifrado con AMSCO
    @Parametros:
        @textoCifrado: mensaje cifrado
        @clave: clave para descifrar el mensaje
    @Retorno: mensaje descifrado
*/
string descifrarAMSCO(const string& textoCifrado, const string& clave) {
    int longitudClave = clave.length();
    int longitudTexto = textoCifrado.length();
    vector<int> numColumnas = calcularNumeroColumnas(longitudClave, longitudTexto);

    // Emparejar dígitos con el número de letras en cada columna
    vector<pair<char, int>> digitosConCaracteres;
    for (int i = 0; i < longitudClave; ++i) {
        digitosConCaracteres.emplace_back(clave[i], numColumnas[i]);
    }

    // Ordenar las columnas según la clave
    sort(digitosConCaracteres.begin(), digitosConCaracteres.end());
    
    // Dividir el texto cifrado
    vector<string> trozos(longitudClave);
    string textoRestante = textoCifrado;

    for (int i = 0; i < longitudClave; ++i) {
        trozos[i] = textoRestante.substr(0, digitosConCaracteres[i].second);
        textoRestante = textoRestante.substr(digitosConCaracteres[i].second);
    }

    // Unir el mensaje descifrado
    string mensajeDescifrado;
    int contadorClave = 0;
    int numCaracteres = 1;
    int contador = longitudTexto;

    while (contador > 0) {
        int indiceColumna = clave[contadorClave] - '1'; // Convertir a índice
        mensajeDescifrado += trozos[indiceColumna].substr(0, numCaracteres);
        trozos[indiceColumna] = trozos[indiceColumna].substr(numCaracteres);
        contador -= numCaracteres;
        contadorClave = (contadorClave + 1) % longitudClave;
        numCaracteres = (numCaracteres == 1) ? 2 : 1; // Alterna entre 1 y 2

        if (numCaracteres == 2 && contador == 1) {
            numCaracteres = 1;
        }
    }

    return mensajeDescifrado;
}

// Función principal
int main() {
    cout << "Ingrese el texto a cifrar: ";
    string texto;
    getline(cin, texto);

    cout << "Ingrese la clave: ";
    string clave;
    cin >> clave;

    string mensajeCifrado = cifrarAMSCO(texto, clave);
    cout << "Mensaje cifrado: " << mensajeCifrado << endl;
    
    string mensajeDescifrado = descifrarAMSCO(mensajeCifrado, clave);
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}
