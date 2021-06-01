#ifndef TP3_SIMCITY_MAPA_H
#define TP3_SIMCITY_MAPA_H

#include <iostream>
#include <set>
#include "Tipos.h"

using namespace std;

class Mapa {
public:

    Mapa();

    void agregarRio(Direccion d, int p);

    bool hayRio(Casilla c) const;

    void unirMapa(Mapa m2);

    set<int> riosHorizontales();

    set<int> riosVerticales();

private:
    set<int> _horizontales;
    set<int> _verticales;
};

#endif //TP3_SIMCITY_MAPA_H
