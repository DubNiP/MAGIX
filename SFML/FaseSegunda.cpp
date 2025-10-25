#include "FaseSegunda.hpp"

FaseSegunda::FaseSegunda(Jogador* pJog, GerenciadorGrafico* pGG):
	Fase(pJog,pGG),
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