#include "Router.h"

Router::Router() {}

Router::Router(std::string nombre){
    id = nombre;
}

void agregarConexion(const std::string& destino, int costo){
    conexiones[destino] = costo;
}

void Router::printTable() const {

}
