#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <string>

bool validarEntrada(std::string n);
unsigned char *leerArchivo(int &tam);
unsigned char *leerArchivoBin(int &tam);
void guardarArchivoBin(const unsigned char* datos, int tam);
void guardarArchivoBinDeco(const unsigned char* datos, int tam) ;
std::string validarSalida();

#endif // AUXILIARES_H
