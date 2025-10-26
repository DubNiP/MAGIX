#pragma once

#include "Personagem.hpp"
#include <SFML/System/Clock.hpp>

class Jogador: public Personagem {
protected:
	int pontos;
	float invencibilidade;
	Clock danoClock;
	Texture* textura;
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
	void tomarDano(int dano);
	void carregarSprite();

};