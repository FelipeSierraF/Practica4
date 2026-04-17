#include "Network.h"
#include <iostream>


void Network::agregarRouter(const std::string& id){
    if(routers.find(id) == routers.end()){
        routers[id] = Router(id);
    }else{
        std::cout << "El router " << id << "Ya existe " << std::endl;
    }
}

void Network::conectarRouters(const std::string& r1, const std::string& r2, int costo) {
    // Agregar la conexión bidireccional
    adj[r1].push_back({r2, costo});
    adj[r2].push_back({r1, costo});

    // También actualizar las conexiones en cada Router
    routers[r1].agregarConexion(r2, costo);
    routers[r2].agregarConexion(r1, costo);
}

void Network::imprimirRouters(){
    for(const auto& pair : routers){
        std::cout << "Router: " << pair.first << std::endl;
        pair.first.imprimirTabla();
    }
}
