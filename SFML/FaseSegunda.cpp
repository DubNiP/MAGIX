#include "FaseSegunda.hpp"

FaseSegunda::FaseSegunda(Jogador* pJog):
	Fase(pJog),
	maxChefoes(2)
{

}
FaseSegunda::~FaseSegunda() {

}


void FaseSegunda::criarInimigos() {
	criarChefoes();
}
void FaseSegunda::criarObstaculo() {
	criarObsMedios();
}


void FaseSegunda::criarChefoes() {

}

void FaseSegunda::criarObsMedios() {

}
//void criarProjeteis();