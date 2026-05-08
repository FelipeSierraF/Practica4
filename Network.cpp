#include "Network.h"
#include <iostream>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>


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

    it1->second.agregarConexion(r2,costo);
    it2->second.agregarConexion(r1,costo);

    auto actualizar_o_agregar = [&](const std::string& a, const std::string& b, int w){
        auto& vec = adj[a];
        bool encontrado = false;
        for(auto& p:vec){
            if(p.first == b){
                p.second = w;
                encontrado = true;
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

void Network::mostrarRed() const{
    std::cout << "========RED DE ENRUTADORES==========" << std::endl;
    for (const auto& par:routers){
        par.second.mostrarConexion();
        std::cout << "\n";
    }
}

static std::pair<std::unordered_map<std::string,int>, std::unordered_map<std::string,std::string>>
distrak_aux(const std::map<std::string, Router>& routers,
            const std::map<std::string, std::vector<std::pair<std::string, int>>>& adj,
            const std::string& src){

    const int INF = std::numeric_limits<int>::max()/4;
    std::unordered_map<std::string,int> dist;
    std::unordered_map<std::string,std::string> prev;
    std::unordered_map<std::string, int> hops;

    for(const auto& p:routers){
        dist[p.first] = INF;
        prev[p.first] = "";
        hops[p.first] = INF;
    }

    if(routers.find(src) == routers.end()){
        return{dist,prev};
    }

    using PI = std::pair<int, std::string>;
    std::priority_queue<PI, std::vector<PI>, std::greater<PI>> pq;

    dist[src] = 0;
    hops[src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        auto it = adj.find(u);
        if(it == adj.end()) continue;

        for(const auto& edge:it->second){
            const std::string& v = edge.first;
            int w = edge.second;

            if(dist[u] == INF)continue;
            int nd = dist[u] + w;
            int nh = hops[u] + 1;

            if (nd < dist[v] || (nd == dist[v] && nh < hops[v])){
                dist[v] = nd;
                prev[v] = u;
                hops[v] = nh;
                pq.push({dist[v], v});

            }
        }
    }

    return {dist,prev};

}

int Network::getCosto(const std::string& src, const std::string& dst) const{
    auto result = distrak_aux(routers, adj, src);
    const auto& dist = result.first;
    auto it = dist.find(dst);

    if (it == dist.end()) return -1;
    int val = it->second;
    const int INF = std::numeric_limits<int>::max() / 4;

    if(val >= INF) return-1;

    return val;
}

/*loading...*/
void Network::computerAllRoutes(){
    for(auto &p : routers){
        p.second.clearTable();
    }

    for(const auto& src_pair:routers){
        const std::string src = src_pair.first;

        auto result = distrak_aux(routers,adj,src);
        const auto& dist = result.first;
        const auto& prev = result.second;

        for(const auto& dst_pair : routers){
            const std::string dst = dst_pair.first;

            auto itd = dist.find(dst);
            const int INF = std::numeric_limits<int>::max()/4;

            if(itd == dist.end() || itd->second >= INF){
                continue;
            }

            std::vector<std::string> path;
            std::string cur = dst;

            while(true){
                path.push_back(cur);

                if(cur == src) break;

                auto itp = prev.find(cur);

                if(itp == prev.end() || itp->second.empty()){
                    path.clear();
                    break;
                }

                cur = itp->second;
            }

            if(path.empty()) continue;
            std::reverse(path.begin(), path.end());

            std::string nextHop;

            if(src==dst){
                nextHop = "-";
            }else if(path.size() >= 2){
                nextHop = path[1];
            }else{
                nextHop = path.front();
            }

            int cost = itd->second;

            routers[src].updateEntry(dst,nextHop,cost);
        }
    }
}

std::vector<std::string> Network::getPath(const std::string& src, const std::string& dst) const{
    auto resultado = distrak_aux(routers,adj,src);
    const auto& dist = resultado.first;
    const auto& prev = resultado.second;

    std::vector<std::string> path;
    auto it = dist.find(dst);
    const int INF = std::numeric_limits<int>::max()/4;

    if(it == dist.end() || it -> second >= INF) return path;

    std::string cur = dst;
    while(!cur.empty()){
        path.push_back(cur);

        if (cur == src) break;

        auto itp = prev.find(cur);

        if(itp == prev.end() || itp->second.empty()){path.clear(); return path;}

        cur = itp->second;
    }

    std::reverse(path.begin(), path.end());

    if(path.empty() || path.front() != src) return{};

    return path;
}

void Network::removelink(const std::string& id1, std::string& id2, bool recompute){
    auto it1 = adj.find(id1);
    if (it1 != adj.end()){
        auto& vec = it1->second;
        vec.erase(std::remove_if(vec.begin(), vec.end(),
                                 [&](const std::pair<std::string, int>&p){return p.first == id2;}),
                  vec.end());
    }

    auto it2 = adj.find(id2);
    if(it2 == adj.end()){
        if(it2 != adj.end()){
            auto& vec = it2->second;
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                                     [&](const std::pair<std::string,int>&p){ return p.first == id2;}),
                      vec.end());
        }
    }

    auto r1 = routers.find(id1);
    if(r1 == routers.end()) r1->second.removeConexion(id2);

    auto r2 = routers.find(id2);
    if(r2 == routers.end()) r2 ->second.removeConexion(id2);

    if(recompute) computerAllRoutes();
}

bool Network::loadFromFile(const std::string& path){
    std::ifstream f(path);

    if(!f.is_open()){
        std::cerr << "No se pudo abrir el archivo: " << path << "\n";
        return false;
    }

    std::string line;

    while(std::getline(f,line)){
        if(line.empty()) continue;

        if(line.size() > 0 && line[0] == '#') continue;

        std::istringstream iss(line);
        std::string u,v;

        int cost;
        if(!(iss >> u >> v >> cost)){
            continue;
        }

        if(routers.find(u) == routers.end()) agregarRouter(u);
        if(routers.find(v) == routers.end()) agregarRouter(v);

        conectarRouters(u,v,cost);
    }

    computerAllRoutes();
    return true;
}

void Network::removeRouter(const std::string& id, bool recompute){
    auto it = routers.find(id);
    if(it == routers.end()){
        std::cout << "El router " << id << "no existe " << std::endl;
        return;
    }

    auto itAdj =adj.find(id);
    std::vector<std::string> vecinos;
    if(itAdj != adj.end()){
        for(const auto &p:itAdj->second) vecinos.push_back(p.first);
    }

    for (const auto &v: vecinos){
        auto itv = adj.find(v);
        if(itv != adj.end()){
            auto& vec = itv->second;
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                                     [&](const std::pair<std::string, int>& pr){return pr.first == id;}),
                      vec.end());

            if(vec.empty()) adj.erase(itv);
        }

        auto rt = routers.find(v);
        if(rt != routers.end()){
            rt->second.removeConexion(id);
        }
    }

    if(itAdj != adj.end()) adj.erase(itAdj);

    routers.erase(it);

    if(recompute) computerAllRoutes();

}

void Network::generateRandom(int n, double density, int maxCost){
    routers.clear();
    adj.clear();

    std::vector<std::string> ids;
    ids.reserve(n);
    for(int i = 0; i< n; i++){
        std::string id = "R" + std::to_string(i);
        ids.push_back(id);
        agregarRouter(id);
    }

    std::mt19937 rng((unsigned)std::random_device{}());
    std::uniform_real_distribution<double> prob(0.0,1.0);
    std::uniform_int_distribution<int> costDist(1, std::max(1, maxCost));

    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            if(prob(rng) < density){
                int c = costDist(rng);

                conectarRouters(ids[i], ids[j], c, false);
            }
        }
    }

    computerAllRoutes();
}

