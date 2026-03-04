#include "auxiliares.h"
#include <iostream>
#include <string>
#include <cctype>

std::string construirRuta(std::string name){
    //Ruta absoluta de los archivos
    std::string basePath = "C:\\Users\\felip\\Documents\\Proyectos resueltos\\Practica4\\dataset\\";

    if (name.find('.') == std::string::npos) { name += ".txt"; }

    //Completamos la ruta
    std::string fullName = basePath + name;

    return fullName;
}

bool validarEntrada(std::string n){
    if(n.empty()) return false;

    for(char c : n){
        if(!isdigit(c)) return false;
    }

    return true;
}

unsigned char* leerArchivo(int& tam){
    std::cout << "Ingrese el nombre del archivo a utilizar: ";
    std::string name;
    std::getline(std::cin, name);

    std::string archivo = construirRuta(name);

    FILE* f = fopen(archivo.c_str(), "rb");
    if (!f) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        tam = 0;
        return nullptr;
    }

    fseek(f, 0, SEEK_END);
    tam = ftell(f);
    rewind(f);

    if (tam <= 0) {
        std::cerr << "Archivo vacío o error al obtener tamaño." << std::endl;
        fclose(f);
        return nullptr;
    }

    unsigned char* buffer = new unsigned char[tam];

    size_t leidos = fread(buffer, 1, tam, f);
    fclose(f);

    if (leidos != (size_t)tam) {
        std::cerr << "Error al leer el archivo completo." << std::endl;
        delete[] buffer;
        tam = 0;
        return nullptr;
    }

    std::cout << "Archivo leído correctamente, tamaño: "
              << tam << " bytes" << std::endl;

    return buffer;
}

void guardarArchivoBin(const unsigned char* datos, int tam) {

    // Ruta fija donde se guardarán los archivos
    const std::string rutaBase =
        "C:\\Users\\felip\\Documents\\Proyectos resueltos\\Practica4\\codificados\\";

    char nombre[256];
    printf("Ingrese el nombre del archivo de salida (sin extension): ");
    scanf("%255s", nombre);

    // Construimos nombre completo con extensión
    std::string nombreCompleto = rutaBase + std::string(nombre) + ".bin";

    FILE* archivo = fopen(nombreCompleto.c_str(), "wb");

    if (archivo != nullptr) {
        fwrite(datos, sizeof(unsigned char), tam, archivo);
        fclose(archivo);
        printf("Archivo guardado exitosamente en:\n%s\n", nombreCompleto.c_str());
    } else {
        printf("Error: no se pudo crear el archivo:\n%s\n", nombreCompleto.c_str());
    }
}
