#pragma once
#include "Entidade.hpp"

class Projetil :public Entidade {
protected:
	bool ativo;
	float velocidade;                       //todo personagem tem velocidade, então talvez vale  pena mover velocidade para entidade...
	bool direcao;
	int posicao;
	int dano;                              //mesma coisa com dano
public:
	Projetil(Vector2f pos, bool dir);
	~Projetil();

	void setAtivo(bool valor);
	bool getAtivo() const;
	void moverDireita();
	void moverEsquerda();
	void executar();
	int getDano();
	//void salvar();
	void carregarSprite();
};