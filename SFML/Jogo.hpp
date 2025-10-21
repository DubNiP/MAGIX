#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador.Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Menu.hpp"
#include "Jogador.hpp"

using namespace sf;

class Jogo {
private:
	Jogador* pJog1;             //OBS: apesar do nome, no diagrama n é ponteiro...
	GerenciadorGrafico GG;
	GerenciadorColisoes GC;     //OBS: mudar para fase no futuro 
	Menu menu;
	Event event;
	void executarMenu(Menu& menu);
	void executarJogo();
public:
	Jogo();
	~Jogo();
	void executar();
};