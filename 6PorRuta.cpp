#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
using matrix = vector<vector<T>>;

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
int main() {
    cout << "Ingrese el texto a cifrar: ";
    string texto;
    getline(cin, texto);

    int filas, columnas;
    cout << "Ingrese el número de filas: ";
    cin >> filas;
    cout << "Ingrese el número de columnas: ";
    cin >> columnas;

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
    string tipoRuta;
    cin >> tipoRuta;

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
