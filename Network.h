#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "Router.h"

class Network{
private:
    std::map<std::string, Router> routers;
    std::map<std::string, std::vector<std::pair<std::string,int>>> adj;

public:
    void agregarRouter(const std::string& id);
    void imprimirRouters();
    void conectarRouters(const std::string& r1, const std::string& r2, int costo, bool recompute = true);
    void computerAllRoutes();
};

#endif // NETWORK_H
