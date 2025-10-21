#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador.Grafico.hpp"
#include <iostream>

using namespace std;

class Menu;

class Jogo {
private:
	//Jogador pJog1;
	GerenciadorGrafico GG;
	void executarMenu(Menu& menu);
	void executarJogo();
public:
	Jogo();
	~Jogo();
	void executar();
};