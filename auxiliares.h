#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <string>

bool validarEntrada(std::string n);
unsigned char *leerArchivo(int &tam);
void guardarArchivoBin(const unsigned char* datos, int tam);

#endif // AUXILIARES_H
