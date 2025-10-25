#pragma once
#include "Fase.hpp"


class FasePrimeira : public Fase {
private:
	const int maxInimMedios;
public:
	FasePrimeira(Jogador* pJog, GerenciadorGrafico* pGG);
	~FasePrimeira();


	void criarInimigos();
	void criarObstaculo();


	void criarInimMedios();


	void criarObsMedios();
};