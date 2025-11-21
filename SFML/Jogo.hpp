#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Colisoes.hpp"
#include "Menu.hpp"
#include "Mago.hpp"
#include "Obstaculo.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
#include "MenuPrincipalState.hpp"

using namespace sf;

class Jogo {
private:
	entidades::personagens::Mago pJog1;   
	entidades::personagens::Mago pJog2;
	State* estadoAtual;
	fases::FasePrimeira fase1;
	fases::FaseSegunda fase2;
public:
	Jogo();
	~Jogo();
	void executar();
	void mudarEstado(State* novoEstado);

	//GETTERS
	entidades::personagens::Mago* getMago1();
	entidades::personagens::Mago* getMago2();
	fases::FasePrimeira* getFase1();
	fases::FaseSegunda* getFase2();
};