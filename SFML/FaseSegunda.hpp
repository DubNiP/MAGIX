#pragma once
#include "Fase.hpp"

class FaseSegunda :public Fase {
private:
	const int maxChefoes;
protected:

	void criarInimigos();
	void criarObstaculo();
	void criarChefoes();
	void criarObsMedios();
	//void criarProjeteis();
public:
	FaseSegunda(Jogador* pJog, GerenciadorGrafico* pGG);
	~FaseSegunda();
};