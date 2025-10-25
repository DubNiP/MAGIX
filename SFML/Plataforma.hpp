#pragma once

#include "Obstaculo.hpp"

class Plataforma : public Obstaculo {
private:
	//int altura;
public:
	Plataforma(Vector2f pos, Vector2f tam, bool dano = false);
	~Plataforma();

	void executar();
	void obstaculizar(Jogador* p);

};