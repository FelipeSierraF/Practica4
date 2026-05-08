#include "Router.h"
#include <iostream>

Router::Router() {}


/*Asignamos el nombre de la clave :v*/
Router::Router(std::string nombre){
    id = nombre;
}

/*Función que agrega el costo de la conexión que se esta señalando en el momento de la ejecución*/
void Router::agregarConexion(const std::string& destino, int costo){
    conexiones[destino] = costo;
}

void Router::mostrarConexion() const{
    std::cout << "Router: " << id << " esta conectado con: \n";
    for(auto& par : conexiones){
        std::cout << "-> "  << par.first << " (costo " << par.second << ")\n";
    }
}

const std::string& Router::getId() const { return id; }

void Router::updateEntry(const std::string& destino, const std::string& nexHop, int costo){
    if(destino == id){
        table[destino] = RouterEntry{"-",0};
        return;
    }

    table[destino] = RouterEntry{nexHop, costo};
}

void Router::printTable()const{
    std::cout << "Tabla de enrutamiento del router " << id <<":" << std::endl;

    if(table.empty()){
        std::cout << "Tabla vacía" << std::endl;
        return;
    }

    std::cout << "Destino siguienteHop costo \n";
    std::cout << "------------------------------\n";

    for(const auto& p:table){
        const auto& dest = p.first;
        const auto& entry = p.second;

        std::string nh = entry.nextHop.empty() ? "-":entry.nextHop;
        std::cout << dest << "      " << nh << "        " << entry.costo << std::endl;
    }
}

const std::map<std::string,RouterEntry>& Router::getTable() const{
    return table;
}

void Router::clearTable(){
    table.clear();
}

void Router::removeConexion(const std::string& destino){
    auto it = conexiones.find(destino);
    if(it != conexiones.end()) conexiones.erase(it);
}
