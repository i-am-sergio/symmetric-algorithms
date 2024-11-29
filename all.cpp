#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
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

int CallCifradoCesar() {
    string texto = "SEGURIDAD";
    int desplazamiento = 3;
    // Cifrado
    string textoCifrado = cifrarCesar(texto, desplazamiento);
    cout << "Texto cifrado (Cesar): " << textoCifrado << endl;
    // Descifrado
    string textoDescifrado = descifrarCesar(textoCifrado, desplazamiento);
    cout << "Texto descifrado (Cesar): " << textoDescifrado << endl;

    return 0;
}


/*
    @ Función: cifra un texto utilizando el cifrado Atbash
    @ Parámetros:
        @ texto: texto a cifrar
    @ Retorno: texto cifrado
*/
string cifrarAtbash(const string& texto) {
    // Alfabeto y su versión invertida
    const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string alfabetoInvertido = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

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


int CallCifradoAtbash() {
    string texto = "criptoSISTEMA";

    // Cifrado Atbash
    string textoCifrado = cifrarAtbash(texto);
    cout << "Texto cifrado (Atbash): " << textoCifrado << endl;

    // Descifrado Atbash
    string textoDescifrado = cifrarAtbash(textoCifrado);
    cout << "Texto descifrado (Atbash): " << textoDescifrado << endl;

    return 0;
}


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


int CallCifradoPlayfair() {
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

int CallCifradoPolybios() {
    matrix<char> matriz = crearMatrizPolybios();
    string mensaje = "CRIPTO";

    cout << "Ingrese el mensaje a cifrar: CRIPTO\n";
    // getline(cin, mensaje);

    string mensajeCifrado = cifrarPolybios(mensaje, matriz);
    cout << "Mensaje cifrado: " << mensajeCifrado << endl;

    string mensajeDescifrado = descifrarPolybios(mensajeCifrado, matriz);
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}


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


int CallCifradoAMSCO() {
    cout << "Ingrese el texto a cifrar: ESTOYSEGURO\n";
    string texto = "ESTOYSEGURO";
    // getline(cin, texto);

    cout << "Ingrese la clave: 321";
    string clave = "321";
    // cin >> clave;

    string mensajeCifrado = cifrarAMSCO(texto, clave);
    cout << "Mensaje cifrado: " << mensajeCifrado << endl;
    
    string mensajeDescifrado = descifrarAMSCO(mensajeCifrado, clave);
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}



// Rutas de Cifrado
string RutaZigZag(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaDiagonales(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeSupIzqHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeSupDerHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeInfIzqHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeInfDerHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeSupIzqAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeSupDerAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeInfIzqAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string RutaEspiralDesdeInfDerAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas);
string CifrarPorRuta(const string& texto, int filas, int columnas, const string& tipoRuta);

// Rutas de Descifrado
string DescifrarRutaZigZag(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaDiagonales(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaEspiralDesdeSupIzqHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaEspiralDesdeSupDerHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaEspiralDesdeInfIzqHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaEspiralDesdeInfDerHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaDesdeSupIzqAntiHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaDesdeSupDerAntiHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaDesdeInfIzqAntiHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarRutaDesdeInfDerAntiHorario(const string& textoCifrado, int filas, int columnas);
string DescifrarPorRuta(const string& textoCifrado, int filas, int columnas, const string& tipoRuta);

// Función principal
int CallCifradoPorRuta() {
    cout << "Ingrese el texto a cifrar: ATAQUETEMPRANO\n";
    string texto = "ATAQUETEMPRANO";
    // getline(cin, texto);

    int filas = 3, columnas = 5;
    cout << "Ingrese el número de filas: 3\n";
    // cin >> filas;
    cout << "Ingrese el número de columnas: 5\n";
    // cin >> columnas;

    // comprueba que el número de filas x columnas >= longitud del texto 
    while (filas * columnas < texto.size()) {
        cout << "El número de filas x columnas debe ser >= a la longitud del texto!!!" << endl;
        cout << "Ingrese el número de filas: ";
        cin >> filas;
        cout << "Ingrese el número de columnas: ";
        cin >> columnas;
    }

    cout << "Ingrese el tipo de ruta: "
        << "zigzag, diagonales, espiralTLH, espiralTRH, espiralBLH, espiralBRH, \n"
        << "espiralTLAH, espiralTRAH, espiralBLAH, espiralBRAH" << endl;
    string tipoRuta = "espiralTLH";
    // cin >> tipoRuta;

    string mensajeCifrado = CifrarPorRuta(texto, filas, columnas, tipoRuta);
    cout << "Mensaje cifrado: " << mensajeCifrado << endl;

    string mensajeDescifrado = DescifrarPorRuta(mensajeCifrado, filas, columnas, tipoRuta);
    cout << "Mensaje descifrado: " << mensajeDescifrado << endl;

    return 0;
}


/*
    @ Funcion: Recorrer la cuadrícula en zigzag
    @ Parametros: 
        - cuadrícula: matriz de caracteres
        - filas: número de filas de la cuadrícula
        - columnas: número de columnas de la cuadrícula
    @ Retorno: string con el texto cifrado
*/
string RutaZigZag(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    for (int columna = 0; columna < columnas; ++columna) {
        if (columna % 2 == 0) { // Columna par: recorrer hacia abajo
            for (int fila = 0; fila < filas; ++fila) {
                if (cuadrícula[fila][columna] != ' ') {
                    textoCifrado += cuadrícula[fila][columna];
                }
            }
        } else { // Columna impar: recorrer hacia arriba
            for (int fila = filas - 1; fila >= 0; --fila) {
                if (cuadrícula[fila][columna] != ' ') {
                    textoCifrado += cuadrícula[fila][columna];
                }
            }
        }
    }
    return textoCifrado;
}


/*
    @ Funcion: Recorrer la cuadrícula en diagonales
    @ Parametros: 
        - cuadrícula: matriz de caracteres
        - filas: número de filas de la cuadrícula
        - columnas: número de columnas de la cuadrícula
    @ Retorno: string con el texto cifrado
*/
string RutaDiagonales(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;

    for (int diag = 0; diag < filas + columnas - 1; ++diag) {
        int startRow = (diag < columnas) ? 0 : diag - columnas + 1;
        int startCol = (diag < columnas) ? diag : columnas - 1;

        while (startRow < filas && startCol >= 0) {
            if (cuadrícula[startRow][startCol] != ' ') {
                textoCifrado += cuadrícula[startRow][startCol];
            }
            ++startRow;
            --startCol;
        }
    }
    return textoCifrado;
}

// Función para la ruta espiral desde la esquina superior izquierda en sentido horario
/*
    @ Funcion: Recorrer la cuadrícula en espiral desde la esquina superior izquierda en sentido horario
    @ Parametros: 
        - cuadrícula: matriz de caracteres
        - filas: número de filas de la cuadrícula
        - columnas: número de columnas de la cuadrícula
    @ Retorno: string con el texto cifrado
*/
string RutaEspiralDesdeSupIzqHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[top][i];
        ++top;
        for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][right];
        --right;
        if (top <= bottom) for (int i = right; i >= left; --i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        if (left <= right) for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][left];
        ++left;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina superior derecha en sentido horario
string RutaEspiralDesdeSupDerHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][right];
        --right;
        for (int i = right; i >= left; --i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        if (left <= right) for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][left];
        ++left;
        if (top <= bottom) for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[top][i];
        ++top;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina inferior izquierda en sentido horario
string RutaEspiralDesdeInfIzqHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][left];
        ++left;
        for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[top][i];
        ++top;
        if (left <= right) for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][right];
        --right;
        if (top <= bottom) for (int i = right; i >= left; --i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina inferior derecha en sentido horario
string RutaEspiralDesdeInfDerHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left; --i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][left];
        ++left;
        if (top <= bottom) for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[top][i];
        ++top;
        if (left <= right) for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][right];
        --right;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina superior izquierda en sentido antihorario
string RutaEspiralDesdeSupIzqAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][left];
        ++left;
        for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        if (left <= right) for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][right];
        --right;
        if (top <= bottom) for (int i = right; i >= left; --i) textoCifrado += cuadrícula[top][i];
        ++top;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina superior derecha en sentido antihorario
string RutaEspiralDesdeSupDerAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left; --i) textoCifrado += cuadrícula[top][i];
        ++top;
        for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][left];
        ++left;
        if (top <= bottom) for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        if (left <= right) for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][right];
        --right;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina inferior izquierda en sentido antihorario
string RutaEspiralDesdeInfIzqAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
        for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][right];
        --right;
        if (top <= bottom) for (int i = right; i >= left; --i) textoCifrado += cuadrícula[top][i];
        ++top;
        if (left <= right) for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][left];
        ++left;
    }

    return textoCifrado;
}

// Función para la ruta espiral desde la esquina inferior derecha en sentido antihorario
string RutaEspiralDesdeInfDerAntiHorario(const matrix<char>& cuadrícula, int filas, int columnas) {
    string textoCifrado;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = bottom; i >= top; --i) textoCifrado += cuadrícula[i][right];
        --right;
        for (int i = right; i >= left; --i) textoCifrado += cuadrícula[top][i];
        ++top;
        if (left <= right) for (int i = top; i <= bottom; ++i) textoCifrado += cuadrícula[i][left];
        ++left;
        if (top <= bottom) for (int i = left; i <= right; ++i) textoCifrado += cuadrícula[bottom][i];
        --bottom;
    }

    return textoCifrado;
}

/*
    @ Funcion: Cifrar un mensaje utilizando el cifrado por ruta
    @ Parametros: 
        - textoACifrar: texto a cifrar
        - filas: numero de filas de la cuadricula
        - columnas: numero de columnas de la cuadricula
        - tipoRuta: tipo de ruta a seguir
    @ Retorno: string con el texto cifrado
*/
string CifrarPorRuta(const string& textoACifrar, int filas, int columnas, const string& tipoRuta) {
    matrix<char> cuadricula(filas, vector<char>(columnas, ' '));
    int index = 0;

    // Llenar la cuadricula
    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            if (index < textoACifrar.size()) {
                cuadricula[fila][columna] = textoACifrar[index++];
            }
        }
    }

    // Seleccionar el tipo de ruta para cifrar el texto
    if (tipoRuta == "zigzag") {
        return RutaZigZag(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralTLH") {
        return RutaEspiralDesdeSupIzqHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralTRH"){
        return RutaEspiralDesdeSupDerHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralBLH"){
        return RutaEspiralDesdeInfIzqHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralBRH"){
        return RutaEspiralDesdeInfDerHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralTLAH"){
        return RutaEspiralDesdeSupIzqAntiHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralTRAH"){
        return RutaEspiralDesdeSupDerAntiHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralBLAH"){
        return RutaEspiralDesdeInfIzqAntiHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "espiralBRAH"){
        return RutaEspiralDesdeInfDerAntiHorario(cuadricula, filas, columnas);
    } else if (tipoRuta == "diagonales") {
        return RutaDiagonales(cuadricula, filas, columnas);
    } else {
        return "Tipo de ruta no válido.";
    }
}

// Función para descifrar el texto en zigzag
string DescifrarRutaZigZag(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;

    for (int columna = 0; columna < columnas; ++columna) {
        if (columna % 2 == 0) { // Columna par: llenar hacia abajo
            for (int fila = 0; fila < filas; ++fila) {
                if (index < textoCifrado.size()) {
                    cuadrícula[fila][columna] = textoCifrado[index++];
                }
            }
        } else { // Columna impar: llenar hacia arriba
            for (int fila = filas - 1; fila >= 0; --fila) {
                if (index < textoCifrado.size()) {
                    cuadrícula[fila][columna] = textoCifrado[index++];
                }
            }
        }
    }

    // Leer la cuadrícula en orden de filas para obtener el texto descifrado
    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            if (cuadrícula[fila][columna] != ' ') {
                mensajeDescifrado += cuadrícula[fila][columna];
            }
        }
    }

    return mensajeDescifrado;
}

// Función para descifrar el texto en diagonales
string DescifrarRutaDiagonales(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;

    for (int diag = 0; diag < filas + columnas - 1; ++diag) {
        int startRow = (diag < columnas) ? 0 : diag - columnas + 1;
        int startCol = (diag < columnas) ? diag : columnas - 1;

        while (startRow < filas && startCol >= 0 && index < textoCifrado.size()) {
            cuadrícula[startRow][startCol] = textoCifrado[index++];
            ++startRow;
            --startCol;
        }
    }

    // Leer la cuadrícula en orden de filas para obtener el texto descifrado
    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            if (cuadrícula[fila][columna] != ' ') {
                mensajeDescifrado += cuadrícula[fila][columna];
            }
        }
    }

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina superior izquierda en sentido horario
string DescifrarRutaEspiralDesdeSupIzqHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
    }

    // Leer la cuadrícula en orden normal
    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina superior derecha en sentido horario
string DescifrarRutaEspiralDesdeSupDerHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina inferior izquierda en sentido horario
string DescifrarRutaEspiralDesdeInfIzqHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina inferior derecha en sentido horario
string DescifrarRutaEspiralDesdeInfDerHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina superior izquierda en sentido antihorario
string DescifrarRutaDesdeSupIzqAntiHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina superior derecha en sentido antihorario
string DescifrarRutaDesdeSupDerAntiHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina inferior izquierda en sentido antihorario
string DescifrarRutaDesdeInfIzqAntiHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
        for (int i = top; i <= bottom && index < textoCifrado.size(); ++i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}

// Función para descifrar desde la esquina inferior derecha en sentido antihorario
string DescifrarRutaDesdeInfDerAntiHorario(const string& textoCifrado, int filas, int columnas) {
    matrix<char> cuadrícula(filas, vector<char>(columnas, ' '));
    int index = 0;
    int top = 0, bottom = filas - 1, left = 0, right = columnas - 1;

    while (top <= bottom && left <= right) {
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[i][right] = textoCifrado[index++];
        --right;
        for (int i = right; i >= left && index < textoCifrado.size(); --i)
            cuadrícula[bottom][i] = textoCifrado[index++];
        --bottom;
        for (int i = bottom; i >= top && index < textoCifrado.size(); --i)
            cuadrícula[i][left] = textoCifrado[index++];
        ++left;
        for (int i = left; i <= right && index < textoCifrado.size(); ++i)
            cuadrícula[top][i] = textoCifrado[index++];
        ++top;
    }

    string mensajeDescifrado;
    for (int fila = 0; fila < filas; ++fila)
        for (int columna = 0; columna < columnas; ++columna)
            mensajeDescifrado += cuadrícula[fila][columna];

    return mensajeDescifrado;
}


// Función para descifrar el mensaje en función del tipo de ruta
string DescifrarPorRuta(const string& textoCifrado, int filas, int columnas, const string& tipoRuta) {
    if (tipoRuta == "zigzag") {
        return DescifrarRutaZigZag(textoCifrado, filas, columnas);
    } else if (tipoRuta == "diagonales") {
        return DescifrarRutaDiagonales(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralTLH") {
        return DescifrarRutaEspiralDesdeSupIzqHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralTRH"){
        return DescifrarRutaEspiralDesdeSupDerHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralBLH"){
        return DescifrarRutaEspiralDesdeInfIzqHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralBRH"){
        return DescifrarRutaEspiralDesdeInfDerHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralTLAH"){
        return DescifrarRutaDesdeSupIzqAntiHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralTRAH"){
        return DescifrarRutaDesdeSupDerAntiHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralBLAH"){
        return DescifrarRutaDesdeInfIzqAntiHorario(textoCifrado, filas, columnas);
    } else if (tipoRuta == "espiralBRAH"){
        return DescifrarRutaDesdeInfDerAntiHorario(textoCifrado, filas, columnas);
    } else {
        return "Tipo de ruta no válido.";
    }
}


int main(){
    // Call to Call functions
    cout<< "====== MENU ======" << endl;
    cout<< "1. Cifrado Cesar" << endl;
    cout<< "2. Cifrado Atbash" << endl;
    cout<< "3. Cifrado Playfair" << endl;
    cout<< "4. Cifrado Polybios" << endl;
    cout<< "5. Cifrado AMSCO" << endl;
    cout<< "6. Cifrado Por Ruta" << endl;

    int opcion;
    cout<< "Ingrese la opción => ";
    cin>> opcion;

    switch(opcion){
        case 1:
            // CifradoCesar();
            CallCifradoCesar();
            break;
        case 2:
            // CifradoAtbash();
            CallCifradoAtbash();
            break;
        case 3:
            // CifradoPlayfair();
            CallCifradoPlayfair();
            break;
        case 4:
            // CifradoPolybios();
            CallCifradoPolybios();
            break;
        case 5:
            // CifradoAMSCO();
            CallCifradoAMSCO();
            break;
        case 6:
            // CifradoPorRuta();
            CallCifradoPorRuta();
            break;
        default:
            cout<< "Opción no válida" << endl;
    }
    return 0;
}


/*
ataqu
etemp
rano_

zigzag: aerattaenomqup
espiral: ataqup onaretem
diagonales: ateatrqeaumnpo

LR--DLOHELOW


HELL
OWOR
LD__
*/
