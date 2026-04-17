#include "Network.h"
#include <iostream>

using namespace std;

int main()
{
    Network red;

    std::string id;
    std::cout << "Ingrese el nombre del router: " << std::endl;
    std::getline(std::cin, id);
    red.agregarRouter("A");
    red.agregarRouter("B");
    red.agregarRouter("C");
    red.agregarRouter("D");

    red.conectarRouters("A", "B", 4);
    red.conectarRouters("A", "C", 10);
    red.conectarRouters("B", "C", 3);
    red.conectarRouters("B", "D", 1);
    red.conectarRouters("C", "D", 2);

    return 0;
}
