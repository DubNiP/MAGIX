#include "FasePrimeira.hpp"

FasePrimeira::FasePrimeira(Jogador* pJog, GerenciadorGrafico* pGG):
	Fase(pJog, pGG),
	maxInimMedios(10)
{

}

FasePrimeira::~FasePrimeira() {

}

void FasePrimeira::criarInimigos() {
	//criarInimFaceis();
	criarInimMedios();
}


void FasePrimeira::criarObstaculo() {
	//criarPlataformas();
	criarObsMedios();
}


void FasePrimeira::criarInimMedios() {
	Inimigo* in1 = new Inimigo(Vector2f(200.f, 200.f), 0.f);                   //substituir por algo no futuro..
	GC.incluirInimigo(in1);
	lista_ents.incluir(in1);
}


void FasePrimeira::criarObsMedios() {
	Obstaculo* obs1 = new ObstDificil(Vector2f(400.f, 300.f), Vector2f(200.f, 40.f), false, 0);     //substituir por algo no futuro..
	GC.incluirObstaculo(obs1);
	lista_ents.incluir(obs1);
}
