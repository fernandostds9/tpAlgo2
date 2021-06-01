#include "aed2_SimCity.h"
#include "aed2_Mapa.h"

aed2_SimCity::aed2_SimCity(aed2_Mapa m) : _mapa(m), _simCity(SimCity(m.mapa())){
    _huboConstruccion = false;
    _popularidad = 0;
    _antiguedad = 0;
}

void aed2_SimCity::agregarCasa(Casilla c) {
   _simCity.agregarCasa(c);

}

void aed2_SimCity::agregarComercio(Casilla c) {
    _simCity.agregarComercio(c);

}

void aed2_SimCity::avanzarTurno() {
    _simCity.avanzarTurno();
}

void aed2_SimCity::unir(aed2_SimCity sc) {
    _simCity.unir(sc.simCity());
}

set<Casilla> aed2_SimCity::casas() {
    return _simCity.casas();
}

set<Casilla> aed2_SimCity::comercios() {
    return _simCity.comercios();
}

Nat aed2_SimCity::nivel(Casilla c) {
    return _simCity.nivel(c);
}

bool aed2_SimCity::huboConstruccion() const {
    return _simCity.huboConstruccion();
}

Nat aed2_SimCity::popularidad() const {
    return _simCity.popularidad();
}

Nat aed2_SimCity::antiguedad() const {
    return _simCity.antiguedad();
}

aed2_Mapa aed2_SimCity::mapa() const {
    return aed2_Mapa(_simCity.mapa());
}

SimCity aed2_SimCity::simCity() {
    list<pair<Casilla, Nat>> casas;
    list<pair<Casilla, Nat>> comercios;

    for(Casilla casa: _simCity.casas()) {
        casas.push_back(make_pair(casa, nivel(casa)));
    }

    for(Casilla comercio: _simCity.comercios()) {
        comercios.push_back(make_pair(comercio, nivel(comercio)));
    }

    _mapa = aed2_Mapa(_simCity.mapa());
    _huboConstruccion = _simCity.huboConstruccion();
    _antiguedad = _simCity.antiguedad();
    _popularidad = _simCity.popularidad();

    return SimCity(_mapa.mapa(), casas, comercios, _huboConstruccion, _antiguedad, _popularidad);
}
