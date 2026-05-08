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
    void conectarRouters(const std::string& r1, const std::string& r2, int costo, bool recompute = true);
    void mostrarRed() const;
    void computerAllRoutes();
    void removelink(const std::string& id1, std::string& id2, bool recompute = true);
    bool loadFromFile(const std::string& path);
    void removeRouter(const std::string&, bool recompute = true);
    void generateRandom(int n, double density, int maxCost);

    int getCosto(const std::string& src, const std::string& dst) const;
    std::vector<std::string> getPath(const std::string& src, const std::string& dst) const;
};

#endif // NETWORK_H
