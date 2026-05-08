#include "Network.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

static bool isValidId(const std::string& s){
    if (s.empty()) return false;
    for(char c:s)if (isspace((unsigned char)c)) return false;
    return true;
}

int main()
{
    Network net;
    std::string line;

    std::cout << "Escribe 'help' para ver comentarios: \n";
    while(true){
        std::cout << "red: ";
        if (!std::getline(std::cin, line)) break;
        if(line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if(cmd == "quit"  || cmd == "exit") break;

        else if(cmd == "help"){
            std::cout << "Comandos:\n"
                      << "  addr <id>                 - agregar router\n"
                      << "  delr <id>                 - eliminar router\n"
                      << "  addlink <u> <v> <cost>    - agregar enlace\n"
                      << "  dellink <u> <v>           - eliminar enlace\n"
                      << "  load <file>               - cargar topologia desde archivo\n"
                      << "  gen <n> <dens> <maxCost>  - generar red aleatoria\n"
                      << "  cost <u> <v>              - mostrar costo minimo\n"
                      << "  path <u> <v>              - mostrar camino\n                      "
                      << "show                        - mostrar red y tablas\n"
                      << "  help, exit\n";
        }

        else if (cmd == "addr"){
            std::string id; if(iss >> id && isValidId(id)) net.agregarRouter(id);
            else std::cout << "Uso: addr <id>\n";
        }

        else if (cmd == "delr"){
            std::string id; if (iss >> id && isValidId(id)) net.removeRouter(id);
            else std::cout<< "Uso: delr <id>\n";
        }
        else if(cmd == "addlink"){
            std::string u,v;int c;
            if (iss>>u>>v>>c && isValidId(u) && isValidId(v) && c>0) net.conectarRouters(u,v,c);
            else std::cout << "Uso: addlink <u> <v> <cost>\n";
        }
        else if(cmd == "dellink"){
            std::string u,v;
            if(iss>>u>>v && isValidId(u) && isValidId(v)) net.removelink(u,v);
            else std::cout << "Uso: dellink <u> <v>\n";
        }
        else if(cmd == "load"){
            std::string f; if(iss>>f) net.loadFromFile(f);
            else std::cout << "Uso: load <file>\n";
        }
        else if(cmd == "gen"){
            int n; double d; int mc;
            if (iss>>n>>d>>mc) net.generateRandom(n,d,mc);
            else std::cout << "Uso: gen <n> <density> <maxCost>\n";
        }
        else if(cmd == "cost"){
            std::string u,v; if(iss >> u >> v && isValidId(u) && isValidId(v)){
                int c = net.getCosto(u,v);
                if (c < 0) std::cout << "No hay camino\n";
                else std::cout << "Costo: " << c << "\n";
            }else std::cout << "Uso: cost <u> <v>\n";
        }
        else if(cmd == "path"){
            std::string u,v; if (iss >> u >> v && isValidId(u) && isValidId(v)){
                auto p = net.getPath(u,v);
                if (p.empty()) std::cout << "No hay camino\n";
                else{
                    for (size_t i = 0; i<p.size(); i++){
                        std::cout << p[i] << (i + 1<p.size() ? "->":"\n");
                    }
                }
            }else std::cout << "Uso: path <u> <v>\n";
        }
        else if (cmd == "show"){
            net.mostrarRed();
            net.computerAllRoutes();
        }
        else {
            std::cout << "Comando desconocido. Escriba 'help'.\n";
        }
    }

    std::cout << "Fin del programa.\n";
    return 0;
}
