#ifndef COMPORTAMIENTORESCATADOR_H
#define COMPORTAMIENTORESCATADOR_H

#include <chrono>
#include <time.h>
#include <thread>
#include <list>
#include "comportamientos/comportamiento.hpp"

struct EstadoR_N2{
  int f;
  int c;
  int brujula;
  int energia;
  bool zapatillas;

  bool operator==(const EstadoR_N2 &st) const{
    return (f == st.f and c == st.c and brujula == st.brujula and energia  == st.energia);
  }
};

struct NodoR_N2{
  EstadoR_N2 estado;
  list<Action> secuencia;

  bool operator==(const NodoR_N2 &node) const{
    return estado == node.estado;
  }

  bool operator<(const NodoR_N2 &node) const{
    if (estado.f < node.estado.f) return true;
    else if (estado.f == node.estado.f and estado.c < node.estado.c) return true;
    else if (estado.f == node.estado.f and estado.c == node.estado.c and 
            estado.brujula < node.estado.brujula) return true;
    else if (estado.f == node.estado.f and estado.c == node.estado.c and
            estado.brujula == estado.brujula and estado.energia < estado.energia) return true;
    else return false;
  }
};

class ComportamientoRescatador : public Comportamiento
{

public:
  ComportamientoRescatador(unsigned int size = 0) : Comportamiento(size)
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
  ComportamientoRescatador(std::vector<std::vector<unsigned char>> mapaR, std::vector<std::vector<unsigned char>> mapaC) : Comportamiento(mapaR,mapaC)
  {
    // Inicializar Variables de Estado Niveles 2,3
    hayPlan = false;
  }
  ComportamientoRescatador(const ComportamientoRescatador &comport) : Comportamiento(comport) {}
  ~ComportamientoRescatador() {}

  Action think(Sensores sensores);

  int interact(Action accion, int valor);

  Action ComportamientoRescatadorNivel_0(Sensores sensores);
  Action ComportamientoRescatadorNivel_1(Sensores sensores);
  Action ComportamientoRescatadorNivel_2(Sensores sensores);
  Action ComportamientoRescatadorNivel_3(Sensores sensores);
  Action ComportamientoRescatadorNivel_4(Sensores sensores);
  void VisualizaPlan(const EstadoR_N2 &st, const list<Action> &plan);
  void PintaPlan(const list<Action> &plan, bool zap);
  list<Action> DijkstraRescatador(const EstadoR_N2 &inicio, const EstadoR_N2 &final, 
          const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura);

private:
  // Variables de Estado
  Action last_action;
  bool tiene_zapatillas;
  int giro45Izq;
  vector<vector<int>> memmory;

  list<Action> plan;
  bool hayPlan;
};

#endif
