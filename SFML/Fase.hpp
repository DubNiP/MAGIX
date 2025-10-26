#pragma once
#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Jogador.hpp"
#include "Obst_Dificil.hpp"
#include "Ente.hpp"
#include "Projetil.hpp"
#include "ListaEntidades.hpp"

using namespace sf;

class Fase: public Ente {
protected:
	ListaEntidades lista_ents;
	GerenciadorGrafico* GG;
	GerenciadorColisoes GC;
	Jogador* jog;

	Texture* textFundo;
	Sprite* spriteFundo;

	//void criarInimFaceis();
	//void criarPlataformas();
	void criarProjetil();                                       //Comentar com o Rafa
	virtual void criarInimigos() = 0;          
	virtual void criarObstaculo() = 0;
	void criarCenario();
	virtual void carregarFundo() = 0;
public:
	Fase(Jogador* pJog, GerenciadorGrafico* pGG);
	~Fase();
	void executar();                  //DEVE SER VIRTUAL NO FUTURO
};