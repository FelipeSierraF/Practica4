#include "Network.h"
#include <iostream>


/*Recibimos el id del router, usamos find.id(id) para buscar la clave en el diccionario
 sii no se encuentra la clave, crea la clave id. */

void Network::agregarRouter(const std::string& id){
    if(routers.find(id) == routers.end()){
        routers[id] = Router(id);
    }else{
        std::cout << "El router " << id << "Ya existe " << std::endl;
    }
}

/*Recibimos los routers que se van a conectar y el costo, los guardamos en el tipo de dato auto
 quien interpreta el tipo de dato con el que se esta trabajando por si solo :V, donde tenemos entonces
la clave de los routers, luego mediante un if, validamos que si existan los routers ingresados.
*1- Agregamos costos en la linea 30 y 31
*2-tenemos una función lambda(la usamos para buscar la clave y actualizar el costo)
*3-Si no existe, lo creamos mediante la misma función lambda
*4-
*/

void Network::conectarRouters(const std::string& r1, const std::string& r2, int costo, bool recompute) {
    auto it1 = routers.find(r1);
    auto it2 = routers.find(r2);
    if (it1 == routers.end() || it2 == routers.end()){
        std::cout << "Uno de los routers no existe " << std::endl;
        return;
    }

    it1->second.agregarConexion(r1,costo);
    it2->second.agregarConexion(r2,costo);

    auto actualizar_o_agregar = [&](const std::string& a, const std::string& b, int w){
        auto& vec = adj[a];
        bool encontrado = false;
        for(auto& p:vec){
            if(p.first == b){
                p.second = w; encontrado = true;
                break;
            }
        }
        if(!encontrado)
            vec.emplace_back(b,w);
    };

    actualizar_o_agregar(r1,r2,costo);
    actualizar_o_agregar(r2,r1,costo);

    if(recompute) computerAllRoutes();

}

/*loading...*/
void Network::computerAllRoutes(){
    for(auto &p : routers){
    }

}
