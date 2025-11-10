#pragma once
#include "Entidade.hpp"

class Projetil :public Entidade {
protected:
	bool ativo;
	bool bondade; 
	int posicao;
	int dano;                        //dano tbm..          
public:
	Projetil(Vector2f pos, bool dir, bool bondade);
	~Projetil();

	void setAtivo(bool valor);
	const bool getAtivo() const;
	void executar();
	int getDano();
	const bool getBondade();
	//void salvar();
	void carregarSprite();
};