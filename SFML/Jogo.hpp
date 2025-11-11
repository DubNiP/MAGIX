#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Menu.hpp"
#include "Mago.hpp"
#include "Obstaculo.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"

using namespace sf;

class Jogo {
private:
	entidades::personagens::Mago pJog1;            
	Gerenciadores::GerenciadorGrafico& GG;
	Menu menu;
	Event event;
	fases::FasePrimeira fase1;
	fases::FaseSegunda fase2;
	void executarMenu(Menu& menu);
	void executarJogo();
public:
	Jogo();
	~Jogo();
	void executar();
};