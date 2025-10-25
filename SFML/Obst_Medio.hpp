#pragma once

#include "Obstaculo.hpp"

class ObstMedio :public Obstaculo {
private:
	//float largura;
public:
	ObstMedio(Vector2f pos, Vector2f tam, bool dano = false);
	~ObstMedio();
	void executar();
	void obstaculizar(Jogador* p);
};