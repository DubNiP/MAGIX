#include "Obst_Medio.hpp"

ObstMedio::ObstMedio(Vector2f pos, Vector2f tam, bool dano):
	Obstaculo(pos,tam,dano)
{

}
ObstMedio::~ObstMedio() {

}


void ObstMedio::executar() {
	attPos();
}

void ObstMedio::obstaculizar(Jogador* p) {
	if (p) {
		//IMPLEMENTAR DANO OU OQ QUER QUE SEJA NO FUTURO.	
	}
}