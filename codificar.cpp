#include "codificar.h"
#include "auxiliares.h"
#include <iostream>
#include <string>

int recibirSemilla(){
    std::cout << "Ingrese el tamaño de la semilla: ";
    std::string semilla;
    std::getline(std::cin, semilla);

    while(!validarEntrada(semilla)){
        std::cout << "\nError: opcion invalida, ingrese solo numeros ";
        std::getline(std::cin, semilla);
    }

    int n = stoi(semilla);

    if(n == 0){
        n+=1;
    }

    return n;

}

int recibirMetodo(){
    std::cout << "Ingrese el metodo: ";
    std::string semilla;
    std::getline(std::cin, semilla);

    while(!validarEntrada(semilla)){
        std::cout << "\nError: opcion invalida, ingrese solo numeros ";
        std::getline(std::cin, semilla);
    }

    int n = stoi(semilla);

    return n;
}

unsigned char* codificarMetodo1(const unsigned char* buffer, int tam, int semilla) {
    int n = semilla;
    int totalBits = tam * 8;
    int numBloques = (totalBits + n - 1) / n;

    unsigned char* original = new unsigned char[tam];
    for (int i = 0; i < tam; i++)
        original[i] = buffer[i];

    unsigned char* resultado = new unsigned char[tam];
    for (int i = 0; i < tam; i++)
        resultado[i] = buffer[i];

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
            for (int i = inicio; i < fin; i++)
                flipBit(i);
        } else {
            int prevInicio = (b - 1) * n;
            int prevFin    = prevInicio + n;
            if (prevFin > totalBits) prevFin = totalBits;

            int unos  = 0;
            int ceros = 0;
            for (int i = prevInicio; i < prevFin; i++) {
                if (getBitFrom(original, i) == 1) unos++;
                else ceros++;
            }

            if (unos == ceros) {
                for (int i = inicio; i < fin; i++)
                    flipBit(i);
            } else if (ceros > unos) {
                for (int i = inicio; i < fin; i += 2)
                    flipBit(i);
            } else {
                for (int i = inicio; i < fin; i += 3)
                    flipBit(i);
            }
        }
    }

    delete[] original;
    return resultado;
}

unsigned char* codificarMetodo2(const unsigned char* buffer, int tam, int semilla) {
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
            int posOrigen   = inicio + ((i - 1 + bitsEnBloque) % bitsEnBloque);
            int posDestino  = inicio + i;
            setBit(posDestino, getBit(buffer, posOrigen));
        }
    }

    return resultado;
}


void menuCodificar(){
    std::cout << std::endl;
    std::cout << "===============Bienvenido al menu de codificación===============" << std::endl;
    int tam = 0;
    unsigned char* buffer = leerArchivo(tam); // Función que lee el archivo, es como un mini menú

    if (!buffer) {
        std::cout << "Error al cargar archivo.\n";
        return;
    }

    while(true){
        int semilla = recibirSemilla(); // Función que se encarga de recibir y validar la semilla
        int metodo = recibirMetodo(); // Función que recibe el numero por el cual se va a codificar
        //(No esta condicionada a "x" cantidad de numeros)

        if(metodo == 1){
            unsigned char* codificado = codificarMetodo1(buffer, tam, semilla);
            guardarArchivoBin(codificado, tam);
            delete[] codificado;
            codificado = nullptr;
            break;

        }else if(metodo == 2){
            unsigned char* codificado = codificarMetodo2(buffer, tam, semilla);
            guardarArchivoBin(codificado, tam);
            delete[] codificado;
            codificado = nullptr;
            break;

        }else if(metodo == 0){
            break;
        }else{
            std::cout << "No existe esa opción, lea imbecil" << std::endl;
        }
    }

    delete[] buffer;
}
