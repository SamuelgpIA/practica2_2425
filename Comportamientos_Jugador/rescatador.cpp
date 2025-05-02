#include "../Comportamientos_Jugador/rescatador.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>

Action ComportamientoRescatador::think(Sensores sensores)
{
	Action accion = IDLE;

	switch (sensores.nivel)
	{
	case 0:
		accion = ComportamientoRescatadorNivel_0 (sensores);
		break;
	case 1:
		accion = ComportamientoRescatadorNivel_1 (sensores);
		break;
	case 2:
		accion = ComportamientoRescatadorNivel_2 (sensores);
		break;
	case 3:
		accion = ComportamientoRescatadorNivel_3 (sensores);
		break;
	case 4:
		accion = ComportamientoRescatadorNivel_4 (sensores);
		break;
	}

	return accion;
}

int ComportamientoRescatador::interact(Action accion, int valor)
{
	return 0;
}

void AnularMatrizR(vector<vector<unsigned char>> &m){
	for (int i = 0; i < m.size(); i++){
		for (int j = 0; j < m.at(i).size(); j++){
			m[i][j] = 0;
		}
	}
}

EstadoR_N2 NextCasillaRescatador(const EstadoR_N2 &st){
	EstadoR_N2 siguiente = st;
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

bool CasillaAccesibleRescatador(const EstadoR_N2 &st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoR_N2 next = NextCasillaRescatador(st);
	bool check1 = false, check2 = false, check3 = false;
	check1 = terreno[next.f][next.c] != 'P' and terreno[next.f][next.c] != 'M';
	check2 = terreno[next.f][next.c] != 'B' or (terreno[next.f][next.c] == 'B' and st.zapatillas);
	check3 = abs(altura[next.f][next.c] - altura[st.f][st.c]) <= 1;
	return check1 and check2 and check3;
}

int VeoCasillaInteresanteR_N0 (char i, char c, char d, bool zap){
	if (c == 'X') return 2;
	else if (i == 'X') return 1;
	else if (d == 'X') return 3;
	else if (!zap){
		if (c == 'D') return 2;
		else if (i == 'D') return 1;
		else if (d == 'D') return 3;
	}
	if (c == 'C') return 2;
	else if (i == 'C') return 1;
	else if (d == 'C') return 3;
	else return 0;
}

int VeoCasillaInteresanteR_N1 (char i, char c, char d, bool zap, int t1, int t2, int t3){
	
	
	if (!zap){
		if (d == 'D') return 3;
		else if (c == 'D') return 2;
		else if (i == 'D') return 1;
	}

	cout << "t1: " << t1 << "\n";
	cout << "t2: " << t2 << "\n";
	cout << "t3: " << t3 << "\n";

	if (d == 'C' or d == 'S' or d == 'X'){
		if (c == 'C' or c == 'S' or c == 'X'){
			if (t3 < t2) return 2;
			else return 3;
		}
		else if (i == 'C' or i == 'S' or i == 'X'){
			if (t3 < t1) return 1;
			else return 3;
		}
		else return 3;
	}
	else if (c == 'C' or c == 'S' or c == 'X'){
		if (i == 'C' or i == 'S' or i == 'X'){
			if (t2 < t1) return 1;
			else return 2;
		}
		else return 2;
	}
	else if (i == 'C' or i == 'S' or i == 'X'){
		return 1;
	}
	else return 0;

	
}

char ViablePorAlturaR(char casilla, int dif, bool zap){
	if (abs(dif) <= 1 or (zap and abs(dif) <= 2))
		return casilla;
	else
		return 'P';
}

void SituarSensorEnMapaR(vector<vector<unsigned char>> &m, vector<vector<unsigned char>> &a, Sensores sensores){
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

EstadoR_N2 applyR(Action accion, const EstadoR_N2 &st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoR_N2 next = st;
	switch(accion){
		case WALK:
			if (CasillaAccesibleRescatador(st, terreno, altura)){
				next = NextCasillaRescatador(st);
				if (terreno.at(st.f).at(st.c) == 'A'){
					next.energia -= 100;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia -= 10;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia += 10;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'T'){
					next.energia -= 20;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia -= 5;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia += 5;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'S'){
					next.energia -= 2;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia --;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia ++;
					}
				}
				else {
					next.energia --;
				}
			}
			break;
		case RUN:
			if (CasillaAccesibleRescatador(st, terreno, altura)){
				next = NextCasillaRescatador(st);
				if (CasillaAccesibleRescatador(next, terreno, altura)){
					next = NextCasillaRescatador(next);
				}

				if (terreno.at(st.f).at(st.c) == 'A'){
					next.energia -= 150;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia -= 15;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia += 15;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'T'){
					next.energia -= 35;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia -= 5;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia += 5;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'S'){
					next.energia -= 3;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.energia -= 2;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.energia += 2;
					}
				}
				else {
					next.energia --;
				}
			}
			break;
		case TURN_SR:
			next.brujula = (st.brujula + 1) % 8;
			if (terreno.at(next.f).at(next.c) == 'A'){
				next.energia -= 16;
			}
			else if (terreno.at(st.f).at(st.c) == 'T'){
				next.energia -= 3;
			}
			else {
				next.energia --;
			}
			break;
		case TURN_L:
			next.brujula = (st.brujula + 6) % 8;
			if (terreno.at(next.f).at(next.c) == 'A'){
				next.energia -= 30;
			}
			else if (terreno.at(st.f).at(st.c) == 'T'){
				next.energia -= 5;
			}
			else {
				next.energia --;
			}

			break;
	}

	return next;
}

bool FindR(const NodoR_N2 &st, const list<NodoR_N2> &lista){
	auto it = lista.begin();
	while (it != lista.end() and !((*it) == st)){
		it ++;
	}
	return (it != lista.end());
}

void ComportamientoRescatador::VisualizaPlan(const EstadoR_N2 &st, const list<Action> &plan){
	AnularMatrizR(mapaConPlan);
	EstadoR_N2 cst = st;

	auto it = plan.begin();
	while (it != plan.end()){
		switch(*it){
			case RUN:
				switch(cst.brujula){
					case 0:
						cst.f --;
						break;
					case 1:
						cst.f --;
						cst.c ++;
						break;
					case 2:
						cst.c ++;
						break;
					case 3:
						cst.f ++;
						cst.c ++;
						break;
					case 4:
						cst.f ++;
						break;
					case 5:
						cst.f ++;
						cst.c --;
						break;
					case 6:
						cst.c --;
						break;
					case 7:
						cst.f --;
						cst.c --;
						break;
				}
				mapaConPlan[cst.f][cst.c] = 3;
				break;
			case WALK:
				switch(cst.brujula){
					case 0:
						cst.f --;
						break;
					case 1:
						cst.f --;
						cst.c ++;
						break;
					case 2:
						cst.c ++;
						break;
					case 3:
						cst.f ++;
						cst.c ++;
						break;
					case 4:
						cst.f ++;
						break;
					case 5:
						cst.f ++;
						cst.c --;
						break;
					case 6:
						cst.c --;
						break;
					case 7:
						cst.f --;
						cst.c --;
						break;
				}
				mapaConPlan[cst.f][cst.c] = 1;
			case TURN_SR:
				cst.brujula = (cst.brujula + 1) % 8;
				break;
			case TURN_L:
				cst.brujula = (cst.brujula + 6) % 8;
				break;
		}
		it ++;
	}
}

void ComportamientoRescatador::PintaPlan(const list<Action> &plan, bool zap){
	auto it = plan.begin();
	while (it != plan.end()){
		if (*it == WALK){
			cout << "W ";
		}
		else if (*it == RUN){
			cout << "R ";
		}
		else if (*it == TURN_SR){
			cout << "r ";
		}
		else if (*it == TURN_L){
			cout << "L ";
		}
		else if (*it == CALL_ON){
			cout << "C ";
		}
		else if (*it == CALL_OFF){
			cout << "c ";
		}
		else if (*it == IDLE){
			cout << "I ";
		}
		else {
			cout << "-_ ";
		}
		it ++;
	}
	cout << "( longitud " << plan.size();
	if (zap) cout << "[Z] ";
	cout << ")\n";
}

list<Action> ComportamientoRescatador::DijkstraRescatador(const EstadoR_N2 &inicio, const EstadoR_N2 &final,
	const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoR_N2 current_node;
	priority_queue<NodoR_N2> frontier;
	list<NodoR_N2> explored;
	list<Action> path;

	current_node.estado = inicio;
	frontier.push(current_node);
	bool SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);

	//1. Generar todos los hijos
	//2. Meterlos en frontier
	//3. Comprobar el nodo de menor coste de frontier
	//4. Cerrar el nodo actual

	while (!SolutionFound){
		//Buscar el nodo actual en frontier y eliminarlo de la lista
		/*
		cout << "\n";
		PintaPlan(current_node.secuencia, tiene_zapatillas);
		cout << "\n";
		*/
		frontier.pop();
		explored.push_back(current_node);
		
		//Generando al hijo resultante de aplicar la acción WALK
		NodoR_N2 child_WALK = current_node;
		child_WALK.estado = applyR(WALK, current_node.estado, terreno, altura);
		if (child_WALK.estado.f == final.f and child_WALK.estado.c == final.c){
			child_WALK.secuencia.push_back(WALK);
			current_node = child_WALK;
			SolutionFound = true;
		}
		else {
			
			child_WALK.secuencia.push_back(WALK);
			frontier.push(child_WALK);
		}
		
		//Generando al hijo resultante de aplicar la acción RUN
		if (!SolutionFound){
			NodoR_N2 child_RUN = current_node;
			child_RUN.estado = applyR(RUN, current_node.estado, terreno, altura);
			if (child_RUN.estado.f == final.f and child_RUN.estado.c == final.c){
				child_RUN.secuencia.push_back(RUN);
				current_node = child_RUN;
				SolutionFound = true;
			}
			else {
				child_RUN.secuencia.push_back(RUN);
				frontier.push(child_RUN);
			}
		}

		//Generando al hijo resultante de aplicar la acción TURN_SR
		if (!SolutionFound){
			NodoR_N2 child_TURN_SR = current_node;
			child_TURN_SR.estado = applyR(TURN_SR, current_node.estado, terreno, altura);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			frontier.push(child_TURN_SR);
		}
		
		//Generando al hijo resultante de aplicar la acción TURN_L
		if (!SolutionFound){
			NodoR_N2 child_TURN_L = current_node;
			child_TURN_L.estado = applyR(TURN_L, current_node.estado, terreno, altura);
			child_TURN_L.secuencia.push_back(TURN_L);
			frontier.push(child_TURN_L);
		}

		if (!SolutionFound and !frontier.empty()){
			//Hay que buscar el nodo de mayor energía en frontier
			current_node = frontier.top();
			SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);
		}
	}

	if (SolutionFound){
		path = current_node.secuencia;
	}
	
	return path;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_0(Sensores sensores)
{
	Action accion;
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	//Actualización de variables
	SituarSensorEnMapaR(mapaResultado, mapaConPlan, sensores);
	if (sensores.superficie[0] == 'D'){
		tiene_zapatillas = true;
	}

	//Definición del comporamiento
	if (sensores.superficie[0] == 'X'){    //Llegué al objetivo
		accion = IDLE;
	}
	else if (giro45Izq != 0){
		accion = TURN_SR;
		giro45Izq --;
	}
	else {
		char i = ViablePorAlturaR(sensores.superficie[1], sensores.cota[1]-sensores.cota[0], tiene_zapatillas);
		char c = ViablePorAlturaR(sensores.superficie[2], sensores.cota[2]-sensores.cota[0], tiene_zapatillas);
		char d = ViablePorAlturaR(sensores.superficie[3], sensores.cota[3]-sensores.cota[0], tiene_zapatillas);

		int pos = VeoCasillaInteresanteR_N0(i, c, d, tiene_zapatillas);
		switch (pos){
			case 2:
				accion = WALK;
				break;
			case 1:
				giro45Izq = 1;
				accion = TURN_L;
				break;
			case 3:
				accion = TURN_SR;
				break;
			
		}

		if (pos == 0 or sensores.agentes[2] == 'a'){
			accion = TURN_L;
		}
	}

	//Devolver la siguiente acción a hacer 
	last_action = accion;
	return accion;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_1(Sensores sensores)
{
	Action accion;
	SituarSensorEnMapaR(mapaResultado, mapaCotas, sensores);
	if (sensores.superficie[0] == 'D'){
		tiene_zapatillas = true;
	}
	
	//Actualizamos la matriz de memoria temporal
	for (int i = 0; i < memmory.size(); i++){
		for (int j = 0; j < memmory.at(i).size(); j++){
			memmory.at(i).at(j) ++;
		}
	}
	memmory.at(sensores.posF).at(sensores.posC) = 0;//el agente ha estado en su posición actual hace 0 ciclos de tiempo

	if (giro45Izq != 0){
		accion = TURN_SR;
		giro45Izq --;
	}
	else {
		char i = ViablePorAlturaR(sensores.superficie[1], sensores.cota[1]-sensores.cota[0], tiene_zapatillas);
		char c = ViablePorAlturaR(sensores.superficie[2], sensores.cota[2]-sensores.cota[0], tiene_zapatillas);
		char d = ViablePorAlturaR(sensores.superficie[3], sensores.cota[3]-sensores.cota[0], tiene_zapatillas);
		int t_i;
		int t_c;
		int t_d;

		switch(sensores.rumbo){
			case norte:
				t_i = memmory.at(sensores.posF-1).at(sensores.posC-1);
				t_c = memmory.at(sensores.posF-1).at(sensores.posC);
				t_d = memmory.at(sensores.posF-1).at(sensores.posC+1);
				break;
			case noreste:
				t_i = memmory.at(sensores.posF-1).at(sensores.posC);
				t_c = memmory.at(sensores.posF-1).at(sensores.posC+1);
				t_d = memmory.at(sensores.posF).at(sensores.posC+1);
				break;
			case este:
				t_i = memmory.at(sensores.posF-1).at(sensores.posC+1);
				t_c = memmory.at(sensores.posF).at(sensores.posC+1);
				t_d = memmory.at(sensores.posF+1).at(sensores.posC+1);
				break;
			case sureste:
				t_i = memmory.at(sensores.posF).at(sensores.posC+1);
				t_c = memmory.at(sensores.posF+1).at(sensores.posC+1);
				t_d = memmory.at(sensores.posF+1).at(sensores.posC);
				break;
			case sur:
				t_i = memmory.at(sensores.posF+1).at(sensores.posC+1);
				t_c = memmory.at(sensores.posF+1).at(sensores.posC);
				t_d = memmory.at(sensores.posF+1).at(sensores.posC-1);
				break;
			case suroeste:
				t_i = memmory.at(sensores.posF+1).at(sensores.posC);
				t_c = memmory.at(sensores.posF+1).at(sensores.posC-1);
				t_d = memmory.at(sensores.posF).at(sensores.posC-1);
				break;
			case oeste:
				t_i = memmory.at(sensores.posF+1).at(sensores.posC-1);
				t_c = memmory.at(sensores.posF).at(sensores.posC-1);
				t_d = memmory.at(sensores.posF-1).at(sensores.posC-1);
				break;
			case noroeste:
				t_i = memmory.at(sensores.posF).at(sensores.posC-1);
				t_c = memmory.at(sensores.posF-1).at(sensores.posC-1);
				t_d = memmory.at(sensores.posF-1).at(sensores.posC);
				break;
		}

		int pos = VeoCasillaInteresanteR_N1(i, c, d, tiene_zapatillas, t_i, t_c, t_d);
		switch(pos){
			case 2:
				accion = WALK;
				break;
			case 1:
				giro45Izq = 1;
				accion = TURN_L;
				break;
			case 3:
				accion = TURN_SR;
				break;
		}

		if (pos == 0 or sensores.agentes[2] == 'a'){
			accion = TURN_L;
		}
	}

	last_action = accion;
	return accion;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_2(Sensores sensores)
{
	Action accion = IDLE;

	if (!hayPlan){
		EstadoR_N2 inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		inicio.energia = sensores.energia;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		plan = DijkstraRescatador(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan(inicio, plan);
		hayPlan = plan.size() != 0;
		if (hayPlan){
			cout << "Plan encontrado:\n";
			PintaPlan(plan, tiene_zapatillas);
		}
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

Action ComportamientoRescatador::ComportamientoRescatadorNivel_3(Sensores sensores)
{
	Action accion;
	return accion;
}

Action ComportamientoRescatador::ComportamientoRescatadorNivel_4(Sensores sensores)
{
	Action accion;
	return accion;
}