#ifndef CODIFICAR_H
#define CODIFICAR_H

void menuCodificar();
int recibirSemilla();
int recibirMetodo();
unsigned char* codificarMetodo1(const unsigned char* buffer, int tam, int semilla);
unsigned char* codificarMetodo2(const unsigned char* buffer, int tam, int semilla);


#endif // CODIFICAR_H
