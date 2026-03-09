#include "registrousuarios.h"
#include "codificar.h"
#include <iostream>
#include <cstdio>
#include <cstring>

struct Usuario {
    char cedula[20];
    char clave[20];
    float saldo;
    int rol;
};

void codificarUsuario(Usuario& u){
    int semilla = recibirSemilla();

    while(true){
        int metodo = recibirMetodo();

        if(metodo == 1){
            unsigned char* codificado = codificarMetodo1((unsigned char*)&u, sizeof(Usuario), semilla);
            memcpy(&u, codificado, sizeof(Usuario));

            delete[] codificado;
            codificado = nullptr;
            break;

        }else if(metodo == 2){
            unsigned char* codificado = codificarMetodo2((unsigned char*)&u, sizeof(Usuario), semilla);
            memcpy(&u, codificado, sizeof(Usuario));

            delete[] codificado;
            codificado = nullptr;
            break;

        }else{
            std::cout << "Por favor, no sea pendejo he ingrese 1 o 2 para escoger el metodo de codificación" << std::endl;
        }
    }
}


void verificarArchivoUsuarios() {
    FILE* archivo = fopen("..\\..\\usuarios\\usuarios.bin", "rb");

    if (archivo != NULL) {
        fclose(archivo);
        return;
    }

    archivo = fopen("..\\..\\usuarios\\usuarios.bin", "wb");
    if (archivo == NULL) return;

    Usuario admin;

    strncpy(admin.cedula, "admin",    sizeof(admin.cedula)  - 1);
    strncpy(admin.clave,  "admin123", sizeof(admin.clave)   - 1);
    admin.cedula[sizeof(admin.cedula) - 1] = '\0';
    admin.clave [sizeof(admin.clave)  - 1] = '\0';
    admin.saldo = 0.0f;
    admin.rol   = 1;

    codificarUsuario(admin);

    fwrite(&admin, sizeof(Usuario), 1, archivo);
    fclose(archivo);

    std::cout << "Funciono " << std::endl;
}

void menuRegistroUsuarios(){
    verificarArchivoUsuarios();

}
