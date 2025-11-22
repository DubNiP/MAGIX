#pragma once
#include "Personagem.hpp"
#include <SFML/System/Clock.hpp>
#include "Projetil.hpp"

namespace fases {
	class Fase;
}

using namespace sf;

namespace entidades { 
	namespace personagens{

		class Mago: public Personagem {
		protected:      //Seguindo diagrama UML base.
			int pontos;
		private:
			float invencibilidade;
			Clock danoClock;
			Clock ataqueClock;
			float tempDanoSalv;
			float tempAtaqSalv;
			bool naTeia;
			bool apto;
			bool concluiuFase;
			fases::Fase* faseAtual;
		public:
			Mago(Vector2f pos, Vector2f vel);
			~Mago();

			void executar();
			void salvar();
			void carregar(int num, int pontos, float inv, float tempDanoSalv, float tempAtaqSalv, bool naTeia, bool apt, bool fConcl);
			void salvarDataBuffer();
			void mover();

			void processarInput(bool esquerda, bool direita, bool pular, bool atirar);


			const int getPontos() const;
			void adicionarPontos(int pts);

			void reseta(Vector2f pos,int vidas, int pontos);
			void tomarDano(int dano, bool bond);

			void carregarSprite();
			void setNaTeia(bool t);
			void setConcluiuFase(bool c);
			void setFaseAtual(fases::Fase* f);
			bool getConcluiuFase() const;
		};
	} 
}