#pragma once
#include "Fase.hpp"


class FasePrimeira : public Fase {
private:
	const int maxInimMedios;
protected:
	void criarInimigos();
	void criarObstaculo();


	void criarInimMedios();


	void criarObsMedios();

	void carregarFundo();
public:
	FasePrimeira(Jogador* pJog, GerenciadorGrafico* pGG);
	~FasePrimeira();
};