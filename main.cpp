#include "auxiliares.h"
#include "codificar.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    cout << "===============Practica4================" << endl;
    cout << "Ingrese una de las siguientes opciones: " << endl;
    cout << "Ejercicio 1" << endl;
    cout << "Ejercicio 2" << endl;
    cout << "Ingrese 0 para finalizar la ejecución: ";

    std::string n;
    getline(cin,n);

    while(n != "0"){
        if(!validarEntrada(n)){
            cout << "\nError: opcion invalida, ingrese solo numeros ";
            getline(cin,n);
            continue;
        }
        if(n == "1"){
            menuCodificar();
        }else if(n == "2"){

        }else if(n == "0"){
            break;
        }
    }

}
