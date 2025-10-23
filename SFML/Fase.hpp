#pragma once
#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"

using namespace sf;

class Fase {
protected:
	//ListaEntidades lista_ents;
	GerenciadorGrafico* GG;
	GerenciadorColisoes GC;
	Jogador* jog;
	//void criarInimFaceis();
	//void criarPlataformas();
	//virtual void criarInimigos() = 0;
	void criarObstaculo();                          //DEVE SER VIRTUAL NO FUTURO
	void criarCenario();
public:
	Fase(Jogador* pJog, GerenciadorGrafico* pGG);
	~Fase();
	void executar();                          //DEVE SER VIRTUAL NO FUTURO
};