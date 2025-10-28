#pragma once
#include "Jogador.hpp"
#include "Personagem.hpp"


class Inimigo : public Personagem {
protected:
	int nivel_maldade;
	Jogador* pJog;
public:
	Inimigo(Vector2f pos, float vel, Jogador* jog);
	~Inimigo();
	//void salvarDataBuffer();
	virtual void executar() = 0;
	virtual void danificar() = 0;
	//virtual void salva() = 0;
	virtual void mover() = 0;
	virtual void perseguir(Vector2f posicaoJog, Vector2f posicaoInim) = 0;
	virtual void carregarSprite() = 0;
};
