#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <map>

struct RouterEntry {
    std::string nextHop;
    int costo;
};

class Router{
private:
    std::string id;
    std::map<std::string, int> conexiones;
    std::map<std::string, RouterEntry> table;
public:
    Router();
    Router(std::string nombre);

    void agregarConexion(const std::string& destino, int costo);
    void printTable() const;

};

#endif // ROUTER_H
