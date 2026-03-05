#include "decodificar.h"
#include "auxiliares.h"
#include "codificar.h"
#include <iostream>

unsigned char* decodificarMetodo1(const unsigned char* bufferCodificado, int tam, int semilla) {
    int n = semilla;
    int totalBits = tam * 8;
    int numBloques = (totalBits + n - 1) / n;

    // Aquí iremos reconstruyendo el archivo original
    unsigned char* resultado = new unsigned char[tam];
    for (int i = 0; i < tam; i++)
        resultado[i] = bufferCodificado[i];

    auto getBitFrom = [&](const unsigned char* buf, int pos) -> int {
        int byteIdx = pos / 8;
        int bitIdx  = 7 - (pos % 8);
        return (buf[byteIdx] >> bitIdx) & 1;
    };

    auto setBit = [&](int pos, int val) {
        int byteIdx = pos / 8;
        int bitIdx  = 7 - (pos % 8);
        if (val)
            resultado[byteIdx] |=  (1 << bitIdx);
        else
            resultado[byteIdx] &= ~(1 << bitIdx);
    };

    auto flipBit = [&](int pos) {
        setBit(pos, 1 - getBitFrom(resultado, pos));
    };

    for (int b = 0; b < numBloques; b++) {
        int inicio = b * n;
        int fin    = inicio + n;
        if (fin > totalBits) fin = totalBits;

        if (b == 0) {
            // El primer bloque siempre se invierte completamente
            for (int i = inicio; i < fin; i++)
                flipBit(i);
        } else {
            int prevInicio = (b - 1) * n;
            int prevFin    = prevInicio + n;
            if (prevFin > totalBits) prevFin = totalBits;

            int unos  = 0;
            int ceros = 0;

            for (int i = prevInicio; i < prevFin; i++) {
                if (getBitFrom(resultado, i) == 1) unos++;
                else                               ceros++;
            }

            if (unos == ceros) {
                for (int i = inicio; i < fin; i++)
                    flipBit(i);
            }
            else if (ceros > unos) {
                for (int i = inicio; i < fin; i += 2)
                    flipBit(i);
            }
            else {
                for (int i = inicio; i < fin; i += 3)
                    flipBit(i);
            }
        }
    }

    return resultado;
}

unsigned char* decodificarMetodo2(const unsigned char* bufferCodificado, int tam, int semilla) {
    int n = semilla;
    int totalBits = tam * 8;

    unsigned char* resultado = new unsigned char[tam];
    for (int i = 0; i < tam; i++)
        resultado[i] = 0;

    auto getBit = [&](const unsigned char* buf, int pos) -> int {
        int byteIdx = pos / 8;
        int bitIdx  = 7 - (pos % 8);
        return (buf[byteIdx] >> bitIdx) & 1;
    };

    auto setBit = [&](int pos, int val) {
        int byteIdx = pos / 8;
        int bitIdx  = 7 - (pos % 8);
        if (val)
            resultado[byteIdx] |=  (1 << bitIdx);
        else
            resultado[byteIdx] &= ~(1 << bitIdx);
    };

    int numBloques = (totalBits + n - 1) / n;

    for (int b = 0; b < numBloques; b++) {
        int inicio = b * n;
        int fin    = inicio + n;
        if (fin > totalBits) fin = totalBits;

        int bitsEnBloque = fin - inicio;

        for (int i = 0; i < bitsEnBloque; i++) {
            // Rotación inversa: desplazamiento a la izquierda
            int posOrigen  = inicio + ((i + 1) % bitsEnBloque);
            int posDestino = inicio + i;

            setBit(posDestino, getBit(bufferCodificado, posOrigen));
        }
    }

    return resultado;
}


void menuDecodificar(){
    std::cout << std::endl;
    std::cout << "===============Bienvenido al menu de decodificación=======================" << std::endl;

    int tam = 0;
    unsigned char* buffer = leerArchivoBin(tam);

    if (!buffer) {
        std::cout << "Error al cargar archivo.\n";
        return;
    }

    while(true){
        int semilla = recibirSemilla(); // Función que se encarga de recibir y validar la semilla
        int metodo = recibirMetodo(); // Función que recibe el numero por el cual se va a codificar
        //(No esta condicionada a x cantidad de numeros)

        if(metodo == 1){
            unsigned char* decodificado = decodificarMetodo1(buffer,tam,semilla);
            guardarArchivoBinDeco(decodificado,tam);
            delete[] decodificado;
            decodificado = nullptr;
            break;

        }else if(metodo == 2){
            unsigned char* decodificado = decodificarMetodo2(buffer,tam,semilla);
            guardarArchivoBinDeco(decodificado,tam);
            delete[] decodificado;
            decodificado = nullptr;
            break;

        }else if(metodo == 0){
            break;
        }
    }
}
