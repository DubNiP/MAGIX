#pragma once
#include "Obstaculo.hpp"

class ObstDificil : public Obstaculo {
private:
	short int danosidade;
public:
	ObstDificil(Vector2f pos, Vector2f tam, bool dano = false, int quantDano = 1);
	~ObstDificil();
	//void salvarDataBuffer();
	void executar();
	void obstaculizar(Jogador* p);
	int getDanosidade() const;
};


