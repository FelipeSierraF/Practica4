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
    void mostrarConexion() const;
    void removeConexion(const std::string& destino);
    const std::string& getId() const;

    void updateEntry(const std::string& destino, const std::string& nextHop, int costo);
    void clearTable();
    void printTable() const;
    const std::map<std::string,RouterEntry>& getTable()const;

};

#endif // ROUTER_H
