#ifndef COMPORTAMIENTOAUXILIAR_H
#define COMPORTAMIENTOAUXILIAR_H

#include <chrono>
#include <time.h>
#include <thread>
#include <list>
#include "comportamientos/comportamiento.hpp"

struct EstadoA {
  int f;
  int c;
  int brujula;
  bool zapatillas;

  bool operator==(const EstadoA &st) const{
    return (f == st.f and c == st.c and brujula == st.brujula and zapatillas == st.zapatillas);
  }
};

struct EstadoA_N3{
  int f;
  int c;
  int brujula;
  int coste;
  int h;
  bool zapatillas;

  bool operator==(const EstadoA_N3 &st) const{
    return (f == st.f and c == st.c and brujula == st.brujula);
  }
};

struct NodoA{
  EstadoA estado;
  list<Action> secuencia;

  bool operator==(const NodoA &node) const{
    return estado == node.estado;
  }

  bool operator<(const NodoA &node) const{
    if (estado.f < node.estado.f) return true;
    else if (estado.f == node.estado.f and estado.c < node.estado.c) return true;
    else if (estado.f == node.estado.f and estado.c == node.estado.c and 
            estado.brujula < node.estado.brujula) return true;
    else if (estado.f == node.estado.f and estado.c == node.estado.c and 
            estado.brujula == node.estado.brujula and estado.zapatillas < node.estado.zapatillas) return true;
    else return false;
  }
};

struct NodoA_N3{
  EstadoA_N3 estado;
  list<Action> secuencia;

  bool operator==(const NodoA_N3 &node) const{
    return estado == node.estado;
  }

  bool operator<(const NodoA_N3 &node) const{
    return ((estado.coste + estado.h) > (node.estado.coste + node.estado.h));
  }
};

class ComportamientoAuxiliar : public Comportamiento
{

public:
  ComportamientoAuxiliar(unsigned int size = 0) : Comportamiento(size)
  {
    // Inicializar Variables de Estado Niveles 0,1,4
    last_action = IDLE;
    tiene_zapatillas = false;
    giro45Izq = 0;
    vector<int> col(size, 0);
    for (int i = 0; i < size; i++){
      memmory.push_back(col);
    }
  }
  ComportamientoAuxiliar(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    // Inicializar Variables de Estado Niveles 2,3
    hayPlan = false;
  }
  ComportamientoAuxiliar(const ComportamientoAuxiliar &comport) : Comportamiento(comport) {}
  ~ComportamientoAuxiliar() {}

  Action think(Sensores sensores);

  int interact(Action accion, int valor);

  Action ComportamientoAuxiliarNivel_0(Sensores sensores);
  Action ComportamientoAuxiliarNivel_1(Sensores sensores);
  Action ComportamientoAuxiliarNivel_2(Sensores sensores);
  Action ComportamientoAuxiliarNivel_3(Sensores sensores);
  Action ComportamientoAuxiliarNivel_4(Sensores sensores);
  Action ComportamientoAuxiliarNivel_E(Sensores sensores);
  list<Action> AnchuraAuxiliar(const EstadoA &inicio, const EstadoA &final, 
                      const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
  list<Action> AnchuraAuxiliar_V2(const EstadoA &inicio, const EstadoA &final, 
                      const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
  list<Action> AuxiliarA(const EstadoA_N3 &inicio, const EstadoA_N3 &final,
                      const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);
  void VisualizaPlan(const EstadoA &st, const list<Action> &plan);
  void VisualizaPlan_N3(const EstadoA_N3 &st, const list<Action> &plan);

private:
  // Definir Variables de Estado
  Action last_action;
  bool tiene_zapatillas;
  int giro45Izq;

  //Variables nivel E
  list<Action> plan;
  bool hayPlan;
  vector<vector<int>> memmory;
};

#endif
