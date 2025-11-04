#pragma once

#include "Personagem.hpp"
#include <SFML/System/Clock.hpp>

namespace entidades { 
	namespace personagens{

		class Jogador: public Personagem {
		protected:
			int pontos;
			float invencibilidade;
			Clock danoClock;
		public:
			Jogador(Vector2f pos, Vector2f vel);
			~Jogador();
			//void colidir(Inimigo* pIn);            //PROVAVEL QUE SEJA O JOGADOR DANDO DANO NO INIMIGO.
			void executar();
			//void salvar();
			void mover();

			void processarInput();

			int getPontos() const;
			void adicionarPontos(int pts);

			void reseta(Vector2f pos,int vidas, int pontos);
			void tomarDano(int dano);
			void carregarSprite();

		};
	} 
}