#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Menu.hpp"
#include "Jogador.hpp"
#include "Obstaculo.hpp"


using namespace sf;

class Jogo {
private:
	Jogador pJog1;            
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