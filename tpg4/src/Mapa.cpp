#include "Mapa.h"

Mapa::Mapa() {}

void Mapa::agregarRio(Direccion d, int p) {
    if(d == Horizontal) {
        _horizontales.insert(p);
    } else {
        _verticales.insert(p);
    }
}

bool Mapa::hayRio(Casilla c) const {
    return _verticales.count(c.first) == 1 || _horizontales.count(c.second) == 1;
}

void Mapa::unirMapa(Mapa m2) {
    _verticales.insert(m2._verticales.begin(), m2._verticales.end());
    _horizontales.insert(m2._horizontales.begin(), m2._horizontales.end());
}

set<int> Mapa::riosHorizontales() {
    return _horizontales;
}

set<int> Mapa::riosVerticales() {
    return _verticales;
}
