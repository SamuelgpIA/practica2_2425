#include "../Comportamientos_Jugador/auxiliar.hpp"
#include <iostream>
#include "motorlib/util.h"
#include <set>

Action ComportamientoAuxiliar::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoAuxiliarNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoAuxiliarNivel_1 (sensores);
		break;
	case 2:
		accion = ComportamientoAuxiliarNivel_2 (sensores);
		break;
	case 3:
		//accion = ComportamientoAuxiliarNivel_3 (sensores);
		accion = ComportamientoAuxiliarNivel_E (sensores);
		break;
	case 4:
		accion = ComportamientoAuxiliarNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoAuxiliar::interact(Action accion, int valor)
{
	return 0;
}

void AnularMatrizA(vector<vector<unsigned char>> &m){
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(i).size(); j++){
			m.at(i).at(j) = 0;
		}
	}
}

int VeoCasillaInteresanteA_N0 (char i, char c, char d){
	if (c == 'X') return 2;
	else if (i == 'X') return 1;
	else if (d == 'X') return 3;
	else if (d == 'C') return 3;
	else if (c == 'C') return 2;
	else if (i == 'C') return 1;
	else return 0;
}

int VeoCasillaInteresanteA_N1 (char i, char c, char d, Action just_done){
	if (d == 'C'){
		if (c == 'C' and just_done == TURN_SR) return 2;
		else return 3;
	}
	else if (c == 'C') return 2;
	else if (i == 'C') return 1;
	else if (d == 'S') return 3;
	else if (c == 'S') return 2;
	else if (i == 'S') return 1;
	else if (d == 'X') return 3;
	else if (c == 'X') return 2;
	else if (i == 'X') return 1;
	else return 0;
}

char ViablePorAlturaA(char casilla, int dif){
	if (abs(dif) <= 1)
		return casilla;
	else
		return 'P';
}

void SituarSensorEnMapaA(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores){
	// cout << "estoy en situarsensor en matriz de mapa\n";
	m[sensores.posF][sensores.posC] = sensores.superficie[0];
	int max = 4;

	int pos = 1;
	switch(sensores.rumbo){
		case norte:
			for (int i = 0; i < max; i++){
				for (int j = 0; j < (2*i)+1; j++){
					m[sensores.posF-i][sensores.posC-i+j] = sensores.superficie[i*i + j];//MapaResultado NORTE
					a[sensores.posF-i][sensores.posC-i+j] = sensores.cota[i*i + j];//MapaCota NORTE
				}
			}
			break;
		case noreste:
			//MapaResultado NORESTE
			m[sensores.posF][sensores.posC] = sensores.superficie[0];
			m[sensores.posF-1][sensores.posC] = sensores.superficie[1];
			m[sensores.posF-1][sensores.posC+1] = sensores.superficie[2];
			m[sensores.posF][sensores.posC+1] = sensores.superficie[3];
			m[sensores.posF-2][sensores.posC] = sensores.superficie[4];
			m[sensores.posF-2][sensores.posC+1] = sensores.superficie[5];
			m[sensores.posF-2][sensores.posC+2] = sensores.superficie[6];
			m[sensores.posF-1][sensores.posC+2] = sensores.superficie[7];
			m[sensores.posF][sensores.posC+2] = sensores.superficie[8];
			m[sensores.posF-3][sensores.posC] = sensores.superficie[9];
			m[sensores.posF-3][sensores.posC+1] = sensores.superficie[10];
			m[sensores.posF-3][sensores.posC+2] = sensores.superficie[11];
			m[sensores.posF-3][sensores.posC+3] = sensores.superficie[12];
			m[sensores.posF-2][sensores.posC+3] = sensores.superficie[13];
			m[sensores.posF-1][sensores.posC+3] = sensores.superficie[14];
			m[sensores.posF][sensores.posC+3] = sensores.superficie[15];
			
			//MapaCota NORESTE
			a[sensores.posF][sensores.posC] = sensores.cota[0];
			a[sensores.posF-1][sensores.posC] = sensores.cota[1];
			a[sensores.posF-1][sensores.posC+1] = sensores.cota[2];
			a[sensores.posF][sensores.posC+1] = sensores.cota[3];
			a[sensores.posF-2][sensores.posC] = sensores.cota[4];
			a[sensores.posF-2][sensores.posC+1] = sensores.cota[5];
			a[sensores.posF-2][sensores.posC+2] = sensores.cota[6];
			a[sensores.posF-1][sensores.posC+2] = sensores.cota[7];
			a[sensores.posF][sensores.posC+2] = sensores.cota[8];
			a[sensores.posF-3][sensores.posC] = sensores.cota[9];
			a[sensores.posF-3][sensores.posC+1] = sensores.cota[10];
			a[sensores.posF-3][sensores.posC+2] = sensores.cota[11];
			a[sensores.posF-3][sensores.posC+3] = sensores.cota[12];
			a[sensores.posF-2][sensores.posC+3] = sensores.cota[13];
			a[sensores.posF-1][sensores.posC+3] = sensores.cota[14];
			a[sensores.posF][sensores.posC+3] = sensores.cota[15];
			break;
		case este:
			for (int j = 0; j < max; j++){
				for (int i = 0; i < (2*j)+1; i++){
					m[sensores.posF-j+i][sensores.posC+j] = sensores.superficie[j*j + i];//MapaResultado ESTE
					a[sensores.posF-j+i][sensores.posC+j] = sensores.cota[j*j + i];//MapaCota ESTE
				}
			}
			break;
		case sureste:
			//MapaResultado SURESTE
			m[sensores.posF][sensores.posC] = sensores.superficie[0];
			m[sensores.posF][sensores.posC+1] = sensores.superficie[1];
			m[sensores.posF+1][sensores.posC+1] = sensores.superficie[2];
			m[sensores.posF+1][sensores.posC] = sensores.superficie[3];
			m[sensores.posF][sensores.posC+2] = sensores.superficie[4];
			m[sensores.posF+1][sensores.posC+2] = sensores.superficie[5];
			m[sensores.posF+2][sensores.posC+2] = sensores.superficie[6];
			m[sensores.posF+2][sensores.posC+1] = sensores.superficie[7];
			m[sensores.posF+2][sensores.posC] = sensores.superficie[8];
			m[sensores.posF][sensores.posC+3] = sensores.superficie[9];
			m[sensores.posF+1][sensores.posC+3] = sensores.superficie[10];
			m[sensores.posF+2][sensores.posC+3] = sensores.superficie[11];
			m[sensores.posF+3][sensores.posC+3] = sensores.superficie[12];
			m[sensores.posF+3][sensores.posC+2] = sensores.superficie[13];
			m[sensores.posF+3][sensores.posC+1] = sensores.superficie[14];
			m[sensores.posF+3][sensores.posC] = sensores.superficie[15];
			
			//MapaCota SURESTE
			a[sensores.posF][sensores.posC] = sensores.cota[0];
			a[sensores.posF][sensores.posC+1] = sensores.cota[1];
			a[sensores.posF+1][sensores.posC+1] = sensores.cota[2];
			a[sensores.posF+1][sensores.posC] = sensores.cota[3];
			a[sensores.posF][sensores.posC+2] = sensores.cota[4];
			a[sensores.posF+1][sensores.posC+2] = sensores.cota[5];
			a[sensores.posF+2][sensores.posC+2] = sensores.cota[6];
			a[sensores.posF+2][sensores.posC+1] = sensores.cota[7];
			a[sensores.posF+2][sensores.posC] = sensores.cota[8];
			a[sensores.posF][sensores.posC+3] = sensores.cota[9];
			a[sensores.posF+1][sensores.posC+3] = sensores.cota[10];
			a[sensores.posF+2][sensores.posC+3] = sensores.cota[11];
			a[sensores.posF+3][sensores.posC+3] = sensores.cota[12];
			a[sensores.posF+3][sensores.posC+2] = sensores.cota[13];
			a[sensores.posF+3][sensores.posC+1] = sensores.cota[14];
			a[sensores.posF+3][sensores.posC] = sensores.cota[15];
			break;
		case sur:
			for (int i = 0; i < max; i++){
				for (int j = 0; j < (2*i)+1; j++){
					m[sensores.posF+i][sensores.posC+i-j] = sensores.superficie[i*i + j];//MapaResultado SUR
					a[sensores.posF+i][sensores.posC+i-j] = sensores.cota[i*i + j];//MapaCota SUR
				}
			}
			break;
		case suroeste:
			//MapaResultado SUROESTE
			m[sensores.posF][sensores.posC] = sensores.superficie[0];
			m[sensores.posF+1][sensores.posC] = sensores.superficie[1];
			m[sensores.posF+1][sensores.posC-1] = sensores.superficie[2];
			m[sensores.posF][sensores.posC-1] = sensores.superficie[3];
			m[sensores.posF+2][sensores.posC] = sensores.superficie[4];
			m[sensores.posF+2][sensores.posC-1] = sensores.superficie[5];
			m[sensores.posF+2][sensores.posC-2] = sensores.superficie[6];
			m[sensores.posF+1][sensores.posC-2] = sensores.superficie[7];
			m[sensores.posF][sensores.posC-2] = sensores.superficie[8];
			m[sensores.posF+3][sensores.posC] = sensores.superficie[9];
			m[sensores.posF+3][sensores.posC-1] = sensores.superficie[10];
			m[sensores.posF+3][sensores.posC-2] = sensores.superficie[11];
			m[sensores.posF+3][sensores.posC-3] = sensores.superficie[12];
			m[sensores.posF+2][sensores.posC-3] = sensores.superficie[13];
			m[sensores.posF+1][sensores.posC-3] = sensores.superficie[14];
			m[sensores.posF][sensores.posC-3] = sensores.superficie[15];
			
			//MapaCota SUROESTE
			a[sensores.posF][sensores.posC] = sensores.cota[0];
			a[sensores.posF+1][sensores.posC] = sensores.cota[1];
			a[sensores.posF+1][sensores.posC-1] = sensores.cota[2];
			a[sensores.posF][sensores.posC-1] = sensores.cota[3];
			a[sensores.posF+2][sensores.posC] = sensores.cota[4];
			a[sensores.posF+2][sensores.posC-1] = sensores.cota[5];
			a[sensores.posF+2][sensores.posC-2] = sensores.cota[6];
			a[sensores.posF+1][sensores.posC-2] = sensores.cota[7];
			a[sensores.posF][sensores.posC-2] = sensores.cota[8];
			a[sensores.posF+3][sensores.posC] = sensores.cota[9];
			a[sensores.posF+3][sensores.posC-1] = sensores.cota[10];
			a[sensores.posF+3][sensores.posC-2] = sensores.cota[11];
			a[sensores.posF+3][sensores.posC-3] = sensores.cota[12];
			a[sensores.posF+2][sensores.posC-3] = sensores.cota[13];
			a[sensores.posF+1][sensores.posC-3] = sensores.cota[14];
			a[sensores.posF][sensores.posC-3] = sensores.cota[15];
			break;
		case oeste:
			for (int j = 0; j < max; j++){
				for (int i = 0; i < (2*j)+1; i++){
					m[sensores.posF+j-i][sensores.posC-j] = sensores.superficie[j*j + i];//MapaResultado OESTE
					a[sensores.posF+j-i][sensores.posC-j] = sensores.cota[j*j + i];//MapaCota OESTE
				}
			}
			break;
		case noroeste:
			//MapaResultado NOROESTE
			m[sensores.posF][sensores.posC] = sensores.superficie[0];
			m[sensores.posF][sensores.posC-1] = sensores.superficie[1];
			m[sensores.posF-1][sensores.posC-1] = sensores.superficie[2];
			m[sensores.posF-1][sensores.posC] = sensores.superficie[3];
			m[sensores.posF][sensores.posC-2] = sensores.superficie[4];
			m[sensores.posF-1][sensores.posC-2] = sensores.superficie[5];
			m[sensores.posF-2][sensores.posC-2] = sensores.superficie[6];
			m[sensores.posF-2][sensores.posC-1] = sensores.superficie[7];
			m[sensores.posF-2][sensores.posC] = sensores.superficie[8];
			m[sensores.posF][sensores.posC-3] = sensores.superficie[9];
			m[sensores.posF-1][sensores.posC-3] = sensores.superficie[10];
			m[sensores.posF-2][sensores.posC-3] = sensores.superficie[11];
			m[sensores.posF-3][sensores.posC-3] = sensores.superficie[12];
			m[sensores.posF-3][sensores.posC-2] = sensores.superficie[13];
			m[sensores.posF-3][sensores.posC-1] = sensores.superficie[14];
			m[sensores.posF-3][sensores.posC] = sensores.superficie[15];
			
			//MapaCota NOROESTE
			a[sensores.posF][sensores.posC] = sensores.cota[0];
			a[sensores.posF][sensores.posC-1] = sensores.cota[1];
			a[sensores.posF-1][sensores.posC-1] = sensores.cota[2];
			a[sensores.posF-1][sensores.posC] = sensores.cota[3];
			a[sensores.posF][sensores.posC-2] = sensores.cota[4];
			a[sensores.posF-1][sensores.posC-2] = sensores.cota[5];
			a[sensores.posF-2][sensores.posC-2] = sensores.cota[6];
			a[sensores.posF-2][sensores.posC-1] = sensores.cota[7];
			a[sensores.posF-2][sensores.posC] = sensores.cota[8];
			a[sensores.posF][sensores.posC-3] = sensores.cota[9];
			a[sensores.posF-1][sensores.posC-3] = sensores.cota[10];
			a[sensores.posF-2][sensores.posC-3] = sensores.cota[11];
			a[sensores.posF-3][sensores.posC-3] = sensores.cota[12];
			a[sensores.posF-3][sensores.posC-2] = sensores.cota[13];
			a[sensores.posF-3][sensores.posC-1] = sensores.cota[14];
			a[sensores.posF-3][sensores.posC] = sensores.cota[15];
			break;
	}
}

EstadoA NextCasillaAuxiliar(const EstadoA &st){
	EstadoA siguiente = st;
	switch(st.brujula){
		case 0:
			siguiente.f = st.f - 1;
			break;
		case 1:
			siguiente.f = st.f - 1;
			siguiente.c = st.c + 1;
			break;
		case 2:
			siguiente.c = st.c + 1;
			break;
		case 3:
			siguiente.f = st.f + 1;
			siguiente.c = st.c + 1;
			break;
		case 4:
			siguiente.f = st.f + 1;
			break;
		case 5:
			siguiente.f = st.f + 1;
			siguiente.c = st.c - 1;
			break;
		case 6:
			siguiente.c = st.c - 1;
			break;
		case 7:
			siguiente.f = st.f - 1;
			siguiente.c = st.c - 1;
			break;
	}

	return siguiente;
}

bool CasillaAccesibleAuxiliar(const EstadoA &st, const vector<vector<unsigned char>> &terreno,
							const vector<vector<unsigned char>> &altura){
	EstadoA next = NextCasillaAuxiliar(st);
	bool check1 = false, check2 = false, check3 = false;
	check1 = terreno[next.f][next.c] != 'P' and terreno[next.f][next.c] != 'M';
	check2 = terreno[next.f][next.c] != 'B' or (terreno[next.f][next.c] == 'B' and st.zapatillas);
	check3 = abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 1;
	return check1 and check2 and check3;
}

EstadoA applyA(Action accion, const EstadoA &st, const vector<vector<unsigned char>> &terreno,
		const vector<vector<unsigned char>> &altura){
	EstadoA next = st;
	switch(accion){
		case WALK:
			if (CasillaAccesibleAuxiliar(st, terreno, altura)){
				next = NextCasillaAuxiliar(st);
			}
			break;
		case TURN_SR:
			next.brujula = (next.brujula+1)%8;
			break;
	}
	return next;
}

bool FindA(const NodoA &st, const list<NodoA> &lista){
	auto it = lista.begin();
	while (it != lista.end() and !((*it) == st)){
		it ++;
	}
	return (it != lista.end());
}

void ComportamientoAuxiliar::VisualizaPlan(const EstadoA &st, const list<Action> &plan){
	AnularMatrizA(mapaConPlan);
	EstadoA cst = st;

	auto it = plan.begin();
	while (it != plan.end()){
		switch (*it){
			case WALK:
				switch (cst.brujula){
					case 0:
						cst.f--;
						break;
					case 1:
						cst.f--;
						cst.c++;
						break;
					case 2:
						cst.c++;
						break;
					case 3:
						cst.f++;
						cst.c++;
						break;
					case 4:
						cst.f++;
						break;
					case 5:
						cst.f++;
						cst.c--;
						break;
					case 6:
						cst.c--;
						break;
					case 7:
						cst.f--;
						cst.c--;
						break;
				}
				mapaConPlan[cst.f][cst.c] = 2;
				break;
			case TURN_SR:
				cst.brujula = (cst.brujula+1)%8;
				break;
		}

		it++;
	}
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores sensores)
{
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;

	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);

	if (sensores.superficie[0] == 'D'){
		tiene_zapatillas = true;
	}

	if (sensores.superficie[0] == 'X'){    //Llegué al objetivo
		accion = IDLE;
	}
	else if (giro45Izq != 0){
		accion = TURN_SR;
		giro45Izq --;
	}
	else {
		char i = ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c = ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d = ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);

		int pos = VeoCasillaInteresanteA_N0(i, c, d);
		
		switch (pos){
			case 2:		
				accion = WALK;
				break;
			case 1:
				giro45Izq = 6;
				accion = TURN_SR;
				break;
			case 3:
				accion = TURN_SR;
				break;
		}

		if (pos == 0 or sensores.agentes[pos] == 'r'){
			giro45Izq = 6;
			accion = TURN_SR;
		}

	}

	last_action = accion;
	return accion;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores sensores)
{
	Action accion;
	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);

	if (sensores.superficie[0] == 'D'){
		tiene_zapatillas = true;
	}

	if (giro45Izq != 0){
		accion = TURN_SR;
		giro45Izq --;
	}
	else {
		char i = ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
		char c = ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
		char d = ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);

		int pos = VeoCasillaInteresanteA_N1(i, c, d, last_action);

		switch (pos){
			case 2:
				accion = WALK;
				break;
			case 1:
				giro45Izq = 6;
				accion = TURN_SR;
				break;
			case 3:
				accion = TURN_SR;
				break;
		}

		if (pos == 0 or sensores.agentes[pos] == 'r'){
			giro45Izq = 6;
			accion = TURN_SR;
		}

	}

	last_action = accion;

	
	return accion;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_2(Sensores sensores)
{
	Action accion;
	return accion;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_3(Sensores sensores)
{
	Action accion;
	return accion;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_4(Sensores sensores)
{
	Action accion;
	return accion;
}

list<Action> AvanzaASaltosDeCaballo(){
	list<Action> secuencia;
	secuencia.push_back(WALK);
	secuencia.push_back(WALK);
	secuencia.push_back(TURN_SR);
	secuencia.push_back(TURN_SR);
	secuencia.push_back(WALK);
	return secuencia;
}

list<Action> ComportamientoAuxiliar::AnchuraAuxiliar(const EstadoA &inicio, const EstadoA &final,
						const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoA current_node;
	list<NodoA> frontier;
	list<NodoA> explored;
	list<Action> path;

	current_node.estado = inicio;
	frontier.push_back(current_node);
	bool SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);
	while (!SolutionFound and !frontier.empty()){
		frontier.pop_front();
		explored.push_back(current_node);

		//Compruebo si estoy en una casilla de zapatillas
		if (terreno[current_node.estado.f][current_node.estado.c] == 'D'){
			current_node.estado.zapatillas = true;
		}

		//Genero el hijo resultante al aplicar la acción WALK
		NodoA child_WALK = current_node;
		child_WALK.estado = applyA(WALK, current_node.estado, terreno, altura);
		if (child_WALK.estado.f == final.f and child_WALK.estado.c == final.c){
			//El hijo generado es solución
			child_WALK.secuencia.push_back(WALK);
			current_node = child_WALK;
			SolutionFound = true;
		}
		else if (!FindA(child_WALK, frontier) and !FindA(child_WALK, explored)){
			//Se mete en la lista frontier después de añadir a la secuencia la acción
			child_WALK.secuencia.push_back(WALK);
			frontier.push_back(child_WALK);

		}


		//Genero el hijo resultante de aplicar la acción TURN_SR
		if (!SolutionFound){
			NodoA child_TURN_SR = current_node;
			child_TURN_SR.estado = applyA(TURN_SR, current_node.estado, terreno, altura);
			if (!FindA(child_TURN_SR, frontier) and !FindA(child_TURN_SR, explored)){
				child_TURN_SR.secuencia.push_back(TURN_SR);
				frontier.push_back(child_TURN_SR);
			}
		}

		//Paso a evalaur el siguiente nodo en la lista frontier
		if (!SolutionFound and !frontier.empty()){
			current_node = frontier.front();
			SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);
		}
	}

	//Devuelvo el camino si se ha encontrado solución
	if (SolutionFound){
		path = current_node.secuencia;
	}

	return path;
}

list<Action> ComportamientoAuxiliar::AnchuraAuxiliar_V2(const EstadoA &inicio, const EstadoA &final,
	const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoA current_node;
	list<NodoA> frontier;
	set<NodoA> explored;
	list<Action> path;

	current_node.estado = inicio;
	frontier.push_back(current_node);
	bool SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);
	while (!SolutionFound and !frontier.empty()){
		frontier.pop_front();
		explored.insert(current_node);

		//Compruebo si estoy en una casilla de zapatillas
		if (terreno[current_node.estado.f][current_node.estado.c] == 'D'){
			current_node.estado.zapatillas = true;
		}

		//Genero el hijo resultante al aplicar la acción WALK
		NodoA child_WALK = current_node;
		child_WALK.estado = applyA(WALK, current_node.estado, terreno, altura);
		if (child_WALK.estado.f == final.f and child_WALK.estado.c == final.c){
			//El hijo generado es solución
			child_WALK.secuencia.push_back(WALK);
			current_node = child_WALK;
			SolutionFound = true;
		}
		else if (explored.find(child_WALK) == explored.end()){
			//Se mete en la lista frontier después de añadir a la secuencia la acción
			child_WALK.secuencia.push_back(WALK);
			frontier.push_back(child_WALK);

		}
		

		//Genero el hijo resultante de aplicar la acción TURN_SR
		if (!SolutionFound){
			NodoA child_TURN_SR = current_node;
			child_TURN_SR.estado = applyA(TURN_SR, current_node.estado, terreno, altura);
			if (explored.find(child_TURN_SR) == explored.end()){
				child_TURN_SR.secuencia.push_back(TURN_SR);
				frontier.push_back(child_TURN_SR);
			}
		}

		//Paso a evalaur el siguiente nodo en la lista frontier
		if (!SolutionFound and !frontier.empty()){
			current_node = frontier.front();
			while (explored.find(current_node) != explored.end()){
				frontier.pop_front();
				current_node = frontier.front();
			}
		}
	}

	//Devuelvo el camino si se ha encontrado solución
	if (SolutionFound){
		path = current_node.secuencia;
	}

	return path;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_E(Sensores sensores)
{
	Action accion = IDLE;
	if (!hayPlan){
		//Invocar al método de búsqueda
		EstadoA inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		//plan = AnchuraAuxiliar(inicio, fin, mapaResultado, mapaCotas);
		plan = AnchuraAuxiliar_V2(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan(inicio, plan);
		hayPlan = plan.size() != 0;
	}
	if (hayPlan and plan.size() > 0){
		accion = plan.front();
		plan.pop_front();
	}
	if (plan.size() == 0){
		hayPlan = false;
	}
	return accion;
}