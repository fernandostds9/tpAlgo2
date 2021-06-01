#include "aed2_Mapa.h"

aed2_Mapa::aed2_Mapa() {}

void aed2_Mapa::agregarRio(Direccion d, int p) {
    _mapa.agregarRio(d, p);
    _horizontales = _mapa.riosHorizontales();
    _verticales = _mapa.riosVerticales();
}

bool aed2_Mapa::hayRio(Casilla c) const {
    return _mapa.hayRio(c);
}

void aed2_Mapa::unirMapa(aed2_Mapa m2) {
    _mapa.unirMapa(m2._mapa);
}

aed2_Mapa::aed2_Mapa(Mapa m) {
    for (int r : m.riosVerticales()) {
        agregarRio(Vertical, r);
    }
    for (int r : m.riosHorizontales()) {
        agregarRio(Horizontal, r);
    }
}

Mapa aed2_Mapa::mapa() const {
    Mapa nuevoMapa;
    for (int r : _verticales) {
        nuevoMapa.agregarRio(Vertical, r);
    }
    for (int r : _horizontales) {
        nuevoMapa.agregarRio(Horizontal, r);
    }
    return nuevoMapa;
}
