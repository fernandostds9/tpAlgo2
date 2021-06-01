#ifndef SIMCITY_H
#define SIMCITY_H

#include <iostream>
#include <set>
#include <list>
#include "Mapa.h"
#include <algorithm>

using namespace std;

class SimCity {
public:

    SimCity(Mapa m);

    SimCity(Mapa m,
            list<pair<Casilla, Nat>> casas,
            list<pair<Casilla, Nat>> comercios,
            bool construccionesNuevas,
            Nat turno,
            Nat popularidad
            );

    void agregarCasa(Casilla c);

    void agregarComercio(Casilla c);

    void avanzarTurno();

    void unir(SimCity sc);

    Mapa mapa() const;

    set<Casilla> casas() ;

    set<Casilla> comercios() ;

    Nat nivel(Casilla c) ;

    bool huboConstruccion() const;

    Nat popularidad() const;

    Nat antiguedad() const;


private:
    Mapa _mapa;
    list<pair<Casilla, Nat>> _casas;
    list<pair<Casilla, Nat>> _comercios;
    bool _construccionesNuevas;
    Nat _turno;
    Nat _popularidad;

    // Funciones Auxiliares

    static bool distanciaMenorA4(Casilla c1, Casilla c2) {
        return (abs(c1.first - c2.first) + abs(c1.second - c2.second)) < 4;
    };

    void arreglarConstrucciones() {
        for(pair<Casilla, Nat> casa1 : _casas) {
            for(pair<Casilla, Nat> casa2 : _casas) {
                if(casa1.first == casa2.first) {
                    // Validamos que las casas sean distintas basándonos en su indice.
                    auto indexCasa1 = find(_casas.begin(), _casas.end(), casa1);
                    auto indexCasa2 = find(_casas.begin(), _casas.end(), casa2);
                    if (indexCasa1 != indexCasa2) {
                        pair<Casilla, Nat> casaMenorNivel = casa1.second < casa2.second ? casa1 : casa2;
                        auto index = find(_casas.begin(), _casas.end(), casaMenorNivel);
                        if (index != _casas.end())
                            _casas.erase(index);
                    }
                }
            }
        }

        for(pair<Casilla, Nat> comercio1 : _comercios) {
            for(pair<Casilla, Nat> comercio2 : _comercios) {
                if(comercio1.first == comercio2.first) {
                    // Validamos que los comercios sean distintas basándonos en su indice.
                    auto indexComercio1 = find(_comercios.begin(), _comercios.end(), comercio1);
                    auto indexComercio2 = find(_comercios.begin(), _comercios.end(), comercio2);
                    if (indexComercio1 != indexComercio2) {
                        pair<Casilla, Nat> comercioMenorNivel =
                                comercio1.second < comercio2.second ? comercio1 : comercio2;
                        auto index = find(_comercios.begin(), _comercios.end(), comercioMenorNivel);
                        if (index != _comercios.end())
                            _comercios.erase(index);
                    }
                }
            }
        }

        for(pair<Casilla, Nat> casa : _casas) {
            for(pair<Casilla, Nat> comercio : _comercios) {
                if(casa.first == comercio.first) {
                    auto index = find(_comercios.begin(), _comercios.end(), comercio);
                    if (index != _comercios.end()) {
                        _comercios.erase(index);
                        break;
                    }
                }
            }
        }
    };
};

#endif //SIMCITY_H
