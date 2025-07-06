#include "../Comportamientos_Jugador/auxiliar.hpp"
#include <iostream>
#include "motorlib/util.h"
#include <set>
#include <queue>
#include <algorithm>

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
		accion = ComportamientoAuxiliarNivel_3 (sensores);
		//accion = ComportamientoAuxiliarNivel_E (sensores);
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

int VeoCasillaInteresanteA_N0 (char i, char c, char d, bool zap, int t1, int t2, int t3){
	if (!zap){
		if (d == 'D') return 3;
		else if (c == 'D') return 2;
		else if (i == 'D') return 1;
	}

	if (d == 'C' or d == 'X'){
		if (c == 'C' or c == 'X'){
			if (t3 < t2) return 2;
			else return 3;
		}
		else if (i == 'C' or i == 'X'){
			if (t3 < t1) return 1;
			else return 3;
		}
		else return 3;
	}
	else if (c == 'C' or c == 'X'){
		if (i == 'C' or i == 'X'){
			if (t2 < t1) return 1;
			else return 2;
		}
		else return 2;
	}
	else if (i == 'C' or i == 'X'){
		return 1;
	}

	else return 0;

	/*if (locus[3] == 'C' or locus[3] == 'X'){
		if (locus[2] == 'C' or locus[2] == 'X'){
			if (tempus[3] < tempus[2]) return 2;
			else return 3;
		}
		else if (locus[1] == 'C' or locus[1] == 'X'){
			if (tempus[3] < tempus[1]) return 1;
			else return 3;
		}
		else return 3;
	}
	else if (locus[2] == 'C' or locus[2] == 'X'){
		if (locus[1] == 'C' or locus[1] == 'X'){
			if (tempus[2] < tempus[1]) return 1;
			else return 2;
		}
		else return 2;
	}
	else if (locus[1] == 'C' or locus[1] == 'X'){
		if (locus[8] == 'C' or locus[8] == 'X'){
			if (locus[6] == 'C' or locus[6] == 'X'){
				if (tempus[8] < tempus[6]) return 6;
				else return 8;
			}
			else if (locus[4] == 'C' or locus[4] == 'X'){
				if (tempus[8] < tempus[4]) return 4;
				else return 8;
			}
			else return 3;
		}
		else if (locus[6] == 'C' or locus[6] == 'X'){
			if (locus[4] == 'C' or locus[4] == 'X'){
				if (tempus[6] < tempus[4]) return 4;
				else return 6;
			}
			else return 6;
		}
		else if (locus[4] == 'C' or locus[4] == 'X'){
			return 4;
		}
		else return 1;
	}
	else return 0;*/
}

int VeoCasillaInteresanteA_N1 (char i, char c, char d, bool zap, int t1, int t2, int t3){
	
	
	if (!zap){
		if (d == 'D') return 3;
		else if (c == 'D') return 2;
		else if (i == 'D') return 1;
	}

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

EstadoA_N3 NextCasillaAuxiliar_N3(const EstadoA_N3 &st){
	EstadoA_N3 siguiente = st;
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

bool CasillaAccesibleAuxiliar_N3(const EstadoA_N3 &st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
EstadoA_N3 next = NextCasillaAuxiliar_N3(st);
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

EstadoA_N3 applyA_N3(Action accion, const EstadoA_N3 &st, const vector<vector<unsigned char>> &terreno,
	const vector<vector<unsigned char>> &altura){
	EstadoA_N3 next = st;
	switch(accion){
		case WALK:
			if (CasillaAccesibleAuxiliar_N3(st, terreno, altura)){
				next = NextCasillaAuxiliar_N3(st);
				if (terreno.at(st.f).at(st.c) == 'A'){
					next.coste += 100;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.coste += 10;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.coste -= 10;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'T'){
					next.coste += 20;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.coste += 5;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.coste -= 5;
					}
				}
				else if (terreno.at(st.f).at(st.c) == 'S'){
					next.coste += 2;
					if (altura.at(next.f).at(next.c) > altura.at(st.f).at(st.c)){
						next.coste ++;
					}
					else if (altura.at(next.f).at(next.c) < altura.at(st.f).at(st.c)){
						next.coste --;
					}
				}
				else {
					next.coste ++;
				}
			}
			break;
		case TURN_SR:
			next.brujula = (next.brujula+1)%8;
			if (terreno.at(next.f).at(next.c) == 'A'){
				next.coste += 16;
			}
			else if (terreno.at(next.f).at(next.c) == 'T'){
				next.coste += 3;
			}
			else {
				next.coste ++;
			}
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

bool FindA_N3(const NodoA_N3 &st, const list<NodoA_N3> &lista){
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

void ComportamientoAuxiliar::VisualizaPlan_N3(const EstadoA_N3 &st, const list<Action> &plan){
	AnularMatrizA(mapaConPlan);
	EstadoA_N3 cst = st;

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

list<Action> ComportamientoAuxiliar::AuxiliarA(const EstadoA_N3 &inicio, const EstadoA_N3 &final,
	const vector<vector<unsigned char>> &terreno, const vector<vector<unsigned char>> &altura){
	NodoA_N3 current_node;
	priority_queue<NodoA_N3> frontier;
	list<NodoA_N3> explored;
	list<Action> path;

	current_node.estado = inicio;
	frontier.push(current_node);
	bool SolutionFound = (current_node.estado.f == final.f and current_node.estado.c == final.c);

	//1. Generar todos los hijos
	//2. Meterlos en frontier
	//3. Comprobar el nodo de menor coste de frontier
	//4. Cerrar el nodo actual

	while (!SolutionFound){

		current_node = frontier.top();
		frontier.pop();
		explored.push_back(current_node);

		if (terreno.at(current_node.estado.f).at(current_node.estado.c) == 'D'){
			current_node.estado.zapatillas = true;
		}

		if (current_node.estado.f == final.f and current_node.estado.c == final.c){
			SolutionFound = true;
		}


		if (!SolutionFound){
			//Generando el hijo resultante de aplicar la acción WALK
			NodoA_N3 child_WALK = current_node;
			child_WALK.estado = applyA_N3(WALK, current_node.estado, terreno, altura);
			child_WALK.estado.h = abs(child_WALK.estado.f - final.f) + abs(child_WALK.estado.c - final.c);
			child_WALK.secuencia.push_back(WALK);
			if (!FindA_N3(child_WALK, explored)){
				frontier.push(child_WALK);
			}
			else {
				auto ind = std::find(explored.begin(), explored.end(), child_WALK);
				if ((*ind) < child_WALK){
					(*ind).estado.coste = child_WALK.estado.coste;
					(*ind).estado.h = child_WALK.estado.h;
					(*ind).secuencia = child_WALK.secuencia;
					frontier.push((*ind));
				}
			}
		}
		if (!SolutionFound){
			//Generando el hijo resultante de aplicar la acción TURN_SR
			NodoA_N3 child_TURN_SR = current_node;
			child_TURN_SR.estado = applyA_N3(TURN_SR, current_node.estado, terreno, altura);
			child_TURN_SR.estado.h = abs(child_TURN_SR.estado.f - final.f) + abs(child_TURN_SR.estado.c - final.c);
			child_TURN_SR.secuencia.push_back(TURN_SR);
			if (!FindA_N3(child_TURN_SR, explored)){
				frontier.push(child_TURN_SR);
			}
			else {
				auto ind = std::find(explored.begin(), explored.end(), child_TURN_SR);
				if ((*ind) < child_TURN_SR){
					(*ind).estado.coste = child_TURN_SR.estado.coste;
					(*ind).estado.h = child_TURN_SR.estado.h;
					(*ind).secuencia = child_TURN_SR.secuencia;
					frontier.push((*ind));
				}
			}
		}
		
	}

	if (SolutionFound){
		path = current_node.secuencia;
	}
	
	return path;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores sensores)
{
	// El comportamiento de seguir un camino hasta encontrar un puesto base.
	Action accion;

	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);

	for (int i = 0; i < memmory.size(); i++){
		for (int j = 0; j < memmory.at(i).size(); j++){
			memmory.at(i).at(j) ++;
		}
	}
	memmory.at(sensores.posF).at(sensores.posC) = -10;

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
		int objetivo_relativo = -1;
		bool objetivo_encontrado = false;
		int posiciones[] = {2, 3, 1, 6, 8, 7, 5, 4};

		for (int i = 0; i < posiciones[sizeof(posiciones) - 1] && !objetivo_encontrado; i++){
			if (sensores.superficie[i] == 'X'){
				objetivo_relativo = i;
				objetivo_encontrado = true;
			}
		}

		if (sensores.cota[objetivo_relativo] - sensores.cota[0] > 1){
			objetivo_encontrado = false;
			for (int j = 0; j < sensores.superficie.size() && !objetivo_encontrado; j++){
				if (sensores.superficie[j] == 'X' && j != objetivo_relativo){
					if (sensores.cota[j] - sensores.cota[0] <= 1){
						objetivo_relativo = j;
						objetivo_encontrado = true;
					}
				}
			}
			
			if (!objetivo_encontrado){
				objetivo_relativo = -1;
			}
		}

		if (objetivo_relativo != -1){
			if (objetivo_relativo == 2 || objetivo_relativo == 6){
				accion = WALK;
			}
			else if (objetivo_relativo == 1 || objetivo_relativo == 4 || objetivo_relativo == 5){
				accion = TURN_SR;
				if ((sensores.superficie[1] == 'X' or sensores.superficie[1] == 'C') and sensores.cota[1] - sensores.cota[0] <= 1){
					giro45Izq = 6;
				}
			}
			else if (objetivo_relativo == 3 || objetivo_relativo == 7 || objetivo_relativo == 8){
				accion = TURN_SR;
				if ((sensores.superficie[3] != 'X' and sensores.superficie[3] != 'C') or sensores.cota[3] - sensores.cota[0] > 1){
					giro45Izq = 6;
				}
			}
			else {
				objetivo_encontrado = false;
			}
		}
		
		if (!objetivo_encontrado){
			char i = ViablePorAlturaA(sensores.superficie[1], sensores.cota[1]-sensores.cota[0]);
			char c = ViablePorAlturaA(sensores.superficie[2], sensores.cota[2]-sensores.cota[0]);
			char d = ViablePorAlturaA(sensores.superficie[3], sensores.cota[3]-sensores.cota[0]);
			char d_2 = ViablePorAlturaA(sensores.superficie[8], sensores.cota[8]-sensores.cota[0]);
			char i_2 = ViablePorAlturaA(sensores.superficie[4], sensores.cota[4]-sensores.cota[0]);
			int t_i;
			int t_c;
			int t_d;
			int t_i2;
			int t_d2;

			/*char vision[8];
			for (int i = 0; i < sizeof(vision); i++){
				vision[i] = ViablePorAlturaA(sensores.superficie[i], sensores.cota[i] - sensores.cota[0]);
			}

			int time[8];
			
			switch(sensores.rumbo){
				case norte:
					for (int j = 0; j < 3; j++){
						for (int k = 0; k < (2*j)+1; k++){
							time[j*j+k] = memmory.at(sensores.posF-j).at(sensores.posC-j+k);
						}
					}
					break;
				case noreste:
					time[0] = memmory.at(sensores.posF).at(sensores.posC);
					time[1] = memmory.at(sensores.posF-1).at(sensores.posC);
					time[2] = memmory.at(sensores.posF-1).at(sensores.posC+1);
					time[3] = memmory.at(sensores.posF).at(sensores.posC+1);
					time[4] = memmory.at(sensores.posF-2).at(sensores.posC);
					time[5] = memmory.at(sensores.posF-2).at(sensores.posC+1);
					time[6] = memmory.at(sensores.posF-2).at(sensores.posC+2);
					time[7] = memmory.at(sensores.posF-1).at(sensores.posC+2);
					time[8] = memmory.at(sensores.posF).at(sensores.posC+2);
					break;
				case este:
					for (int j = 0; j < 3; j++){
						for (int k = 0; k < (2*j)+1; k++){
							time[j*j+k] = memmory.at(sensores.posF-j+k).at(sensores.posC+j);
						}
					}
					break;
				case sureste:
					time[0] = memmory.at(sensores.posF).at(sensores.posC);
					time[1] = memmory.at(sensores.posF).at(sensores.posC+1);
					time[2] = memmory.at(sensores.posF+1).at(sensores.posC+1);
					time[3] = memmory.at(sensores.posF+1).at(sensores.posC);
					time[4] = memmory.at(sensores.posF).at(sensores.posC+2);
					time[5] = memmory.at(sensores.posF+1).at(sensores.posC+2);
					time[6] = memmory.at(sensores.posF+2).at(sensores.posC+2);
					time[7] = memmory.at(sensores.posF+2).at(sensores.posC+1);
					time[8] = memmory.at(sensores.posF+2).at(sensores.posC);
					break;
				case sur:
					for (int j = 0; j < 3; j++){
						for (int k = 0; k < (2*j)+1; k++){
							time[j*j+k] = memmory.at(sensores.posF+j).at(sensores.posC+j-k);
						}
					}
					break;
				case suroeste:
					time[0] = memmory.at(sensores.posF).at(sensores.posC);
					time[1] = memmory.at(sensores.posF+1).at(sensores.posC);
					time[2] = memmory.at(sensores.posF+1).at(sensores.posC-1);
					time[3] = memmory.at(sensores.posF).at(sensores.posC-1);
					time[4] = memmory.at(sensores.posF+2).at(sensores.posC);
					time[5] = memmory.at(sensores.posF+2).at(sensores.posC-1);
					time[6] = memmory.at(sensores.posF+2).at(sensores.posC-2);
					time[7] = memmory.at(sensores.posF+1).at(sensores.posC-2);
					time[8] = memmory.at(sensores.posF).at(sensores.posC-2);
					break;
				case oeste:
					for (int j = 0; j < 3; j++){
						for (int k = 0; k < (2*j)+1; k++){
							time[j*j+k] = memmory.at(sensores.posF+j-k).at(sensores.posC-j);
						}
					}
					break;
				case noroeste:
					time[0] = memmory.at(sensores.posF).at(sensores.posC);
					time[1] = memmory.at(sensores.posF).at(sensores.posC-1);
					time[2] = memmory.at(sensores.posF-1).at(sensores.posC-1);
					time[3] = memmory.at(sensores.posF-1).at(sensores.posC);
					time[4] = memmory.at(sensores.posF).at(sensores.posC-2);
					time[5] = memmory.at(sensores.posF-1).at(sensores.posC-2);
					time[6] = memmory.at(sensores.posF-2).at(sensores.posC-2);
					time[7] = memmory.at(sensores.posF-2).at(sensores.posC-1);
					time[8] = memmory.at(sensores.posF-2).at(sensores.posC);
					break;
			}*/



			//Comprobar las 8 casillas del cono
			//Si la ultima accion fue girar y encuentra un tiempo mayor delante

			switch(sensores.rumbo){
				case norte:
					t_i = memmory.at(sensores.posF-1).at(sensores.posC-1);
					t_c = memmory.at(sensores.posF-1).at(sensores.posC);
					t_d = memmory.at(sensores.posF-1).at(sensores.posC+1);
					t_i2 = memmory.at(sensores.posF-2).at(sensores.posC-2);
					t_d2 = memmory.at(sensores.posF-2).at(sensores.posC+2);
					break;
				case noreste:
					t_i = memmory.at(sensores.posF-1).at(sensores.posC);
					t_c = memmory.at(sensores.posF-1).at(sensores.posC+1);
					t_d = memmory.at(sensores.posF).at(sensores.posC+1);
					t_i2 = memmory.at(sensores.posF-2).at(sensores.posC);
					t_d2 = memmory.at(sensores.posF).at(sensores.posC+2);
					break;
				case este:
					t_i = memmory.at(sensores.posF-1).at(sensores.posC+1);
					t_c = memmory.at(sensores.posF).at(sensores.posC+1);
					t_d = memmory.at(sensores.posF+1).at(sensores.posC+1);
					t_i2 = memmory.at(sensores.posF-2).at(sensores.posC+2);
					t_d2 = memmory.at(sensores.posF+2).at(sensores.posC+2);
					break;
				case sureste:
					t_i = memmory.at(sensores.posF).at(sensores.posC+1);
					t_c = memmory.at(sensores.posF+1).at(sensores.posC+1);
					t_d = memmory.at(sensores.posF+1).at(sensores.posC);
					t_i2 = memmory.at(sensores.posF).at(sensores.posC+2);
					t_d2 = memmory.at(sensores.posF+2).at(sensores.posC);
					break;
				case sur:
					t_i = memmory.at(sensores.posF+1).at(sensores.posC+1);
					t_c = memmory.at(sensores.posF+1).at(sensores.posC);
					t_d = memmory.at(sensores.posF+1).at(sensores.posC-1);
					t_i2 = memmory.at(sensores.posF+2).at(sensores.posC+2);
					t_d2 = memmory.at(sensores.posF+2).at(sensores.posC-2);
					break;
				case suroeste:
					t_i = memmory.at(sensores.posF+1).at(sensores.posC);
					t_c = memmory.at(sensores.posF+1).at(sensores.posC-1);
					t_d = memmory.at(sensores.posF).at(sensores.posC-1);
					t_i2 = memmory.at(sensores.posF+2).at(sensores.posC);
					t_d2 = memmory.at(sensores.posF).at(sensores.posC-2);
					break;
				case oeste:
					t_i = memmory.at(sensores.posF+1).at(sensores.posC-1);
					t_c = memmory.at(sensores.posF).at(sensores.posC-1);
					t_d = memmory.at(sensores.posF-1).at(sensores.posC-1);
					t_i2 = memmory.at(sensores.posF+2).at(sensores.posC-2);
					t_d2 = memmory.at(sensores.posF-2).at(sensores.posC-2);
					break;
				case noroeste:
					t_i = memmory.at(sensores.posF).at(sensores.posC-1);
					t_c = memmory.at(sensores.posF-1).at(sensores.posC-1);
					t_d = memmory.at(sensores.posF-1).at(sensores.posC);
					t_i2 = memmory.at(sensores.posF).at(sensores.posC-2);
					t_d2 = memmory.at(sensores.posF-2).at(sensores.posC);
					break;
			}

			int pos = VeoCasillaInteresanteA_N0(i, c, d, tiene_zapatillas, t_i, t_c, t_d);
			
			switch(pos){
				case 2:
					accion = WALK;
					break;
				case 3:
					accion = TURN_SR;
					break;
				case 1:
					giro45Izq = 6;
					accion = TURN_SR;
					break;
			}
			
			if (pos == 0 or sensores.agentes[pos] == 'r'){
				giro45Izq = 6;
				accion = TURN_SR;
			}
		}
		

	}

	last_action = accion;
	return accion;
}

Action ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores sensores)
{
	Action accion;
	SituarSensorEnMapaA(mapaResultado, mapaCotas, sensores);

	for (int i = 0; i < memmory.size(); i++){
		for (int j = 0; j < memmory.at(i).size(); j++){
			memmory.at(i).at(j) ++;
		}
	}

	memmory.at(sensores.posF).at(sensores.posC) = 0;

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
		}

		int pos = VeoCasillaInteresanteA_N1(i, c, d, tiene_zapatillas, t_i, t_c, t_d);

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
	Action accion = IDLE;
	
	if (!hayPlan){
		EstadoA_N3 inicio, fin;
		inicio.f = sensores.posF;
		inicio.c = sensores.posC;
		inicio.brujula = sensores.rumbo;
		inicio.zapatillas = tiene_zapatillas;
		inicio.coste = 0;
		fin.f = sensores.destinoF;
		fin.c = sensores.destinoC;
		inicio.h = abs(inicio.f - fin.f) + abs(inicio.c - fin.c);
		plan = AuxiliarA(inicio, fin, mapaResultado, mapaCotas);
		VisualizaPlan_N3(inicio, plan);
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