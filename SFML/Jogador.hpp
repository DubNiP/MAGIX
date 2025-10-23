#pragma once

#include "Personagem.hpp"

class Jogador: public Personagem {
protected:
	int pontos;
public:
	Jogador(Vector2f pos, float vel);
	~Jogador();
	//void colidir(Inimigo* pIn);            //VOID MESMO?
	void executar();
	//void salvar();
	void mover();

	void processarInput();

	int getPontos() const;
	void adicionarPontos(int pts);

	void reseta(Vector2f pos,int vidas, int pontos);
};