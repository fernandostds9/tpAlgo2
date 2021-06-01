#include "SimCity.h"
#include "Mapa.h"

SimCity::SimCity(Mapa m){
    _casas.clear();
    _comercios.clear();
    _mapa = m;
    _construccionesNuevas = false;
    _popularidad = 0;
    _turno = 0;
}

SimCity::SimCity(Mapa m, list<pair<Casilla, Nat>> casas, list<pair<Casilla, Nat>> comercios, bool construccionesNuevas,
                 Nat turno, Nat popularidad) : _casas(casas), _comercios(comercios) {
    _mapa = m;
    _casas = casas;
    _comercios = comercios;
    _construccionesNuevas = construccionesNuevas;
    _turno = turno;
    _popularidad = popularidad;
}

void SimCity::agregarCasa(Casilla c) {
    //Asumimos que agrega en O(1)
    _casas.push_back(pair<Casilla, Nat>(c, 0));
    _construccionesNuevas = true;
}

void SimCity::agregarComercio(Casilla c) {
    //Asumimos que agrega en O(1)
    _comercios.push_back(pair<Casilla, Nat>(c, 0));
    _construccionesNuevas = true;
}

void SimCity::avanzarTurno() {

    for(pair<Casilla,  Nat> casa : _casas) {
        auto index = find(_casas.begin(), _casas.end(), casa);
        if (index != _casas.end())
            index->second++;
    }

    for(pair<Casilla,  Nat> comercio : _comercios) {
        auto index = find(_comercios.begin(), _comercios.end(), comercio);
        if (index != _comercios.end())
            index->second++;
    }

    _turno++;
    _construccionesNuevas = false;
}

void SimCity::unir(SimCity sc) {
    _mapa.unirMapa(sc._mapa);

    for(pair<Casilla,  Nat> casa : sc._casas)
        //Asumimos que agrega en O(1)
        _casas.push_back(casa);

    for(pair<Casilla,  Nat> comercio : sc._comercios)
        //Asumimos que agrega en O(1)
        _comercios.push_back(comercio);
    _construccionesNuevas = _construccionesNuevas || sc.huboConstruccion();
    _popularidad += sc._popularidad + 1;
    _turno = max(_turno, sc._turno);
}

set<Casilla> SimCity::casas() {
    set<Casilla> conjCasas;

    arreglarConstrucciones();

    for(pair<Casilla, Nat> casa : _casas)
        conjCasas.insert(casa.first);

    return conjCasas;
}

set<Casilla> SimCity::comercios() {
    set<Casilla> conjComercios;

    arreglarConstrucciones();

    for(pair<Casilla, Nat> comercio : _comercios)
        conjComercios.insert(comercio.first);

    return conjComercios;
}

Nat SimCity::nivel(Casilla c) {
    Nat nivel = 0;
    arreglarConstrucciones();

    for(pair<Casilla, Nat> casa : _casas)
        if (c == casa.first)
            nivel = casa.second;

    for(pair<Casilla, Nat> comercio : _comercios)
        if (c == comercio.first) {
            nivel = comercio.second;
            for(pair<Casilla, Nat> casa : _casas) {
                if(distanciaMenorA4(comercio.first, casa.first))
                    nivel = max(nivel, casa.second);
            }
        }

    return nivel;
}

bool SimCity::huboConstruccion() const {
    return _construccionesNuevas;
}

Nat SimCity::popularidad() const {
    return _popularidad;
}

Nat SimCity::antiguedad() const {
    return _turno;
}

Mapa SimCity::mapa() const {
    return _mapa;
}
