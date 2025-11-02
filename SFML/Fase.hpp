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

namespace fases {

	class Fase: public Ente {
	protected:
		listas::ListaEntidades lista_ents;
		Gerenciadores::GerenciadorColisoes GC;
		entidades::personagens::Jogador* jog;

		Texture* textFundo;
		Sprite* spriteFundo;

		//void criarInimFaceis();
		//void criarPlataformas();
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;
		void criarCenario();                            //fazer ser virtual no futuro??? (diagrama não deixa a princípio)
		virtual void carregarFundo() = 0;
		Entidade* criaEntidade(Entidade* e);
	public:
		Fase(entidades::personagens::Jogador* pJog);
		~Fase();
		void executar();         //nao foi implementado executar nas derivadas de fase. Aqui existe uma dúvida em relaçao a esse executar
	};

}