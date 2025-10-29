#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Menu.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"
#include "FasePrimeira.hpp"


using namespace sf;

class Jogo {
private:
	Jogador pJog1;
	GerenciadorGrafico GG;
	Menu menu;
	Event event;
	FasePrimeira fase1;
	void executarMenu(Menu& menu);
	void executarJogo();
public:
	Jogo();
	~Jogo();
	void executar();
};