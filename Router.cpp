#include "Router.h"

Router::Router() {}


/*Asignamos el nombre de la clave :v*/
Router::Router(std::string nombre){
    id = nombre;
}

void agregarConexion(const std::string& destino, int costo){
    conexiones[destino] = costo;
}

void Router::printTable() const {

}
