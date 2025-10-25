#include "Obst_Dificil.hpp"

ObstDificil::ObstDificil(Vector2f pos, Vector2f tam, bool dano, int quantDano):
	Obstaculo(pos,tam,dano),
	danosidade(quantDano)
{

}

ObstDificil::~ObstDificil() {

}

//void ObstDificil::salvarDataBuffer(){}


void ObstDificil::executar() {
	attPos();
}


void ObstDificil::obstaculizar(Jogador* p) {
	if (p) {
		//IMPLEMENTAR DANO OU OQ QUER QUE SEJA NO FUTURO.	
	}
}

int ObstDificil::getDanosidade() const {
	return danosidade;
}