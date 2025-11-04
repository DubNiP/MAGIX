#pragma once
#include "Jogador.hpp"
#include "Personagem.hpp"

namespace entidades {
	namespace personagens {

		class Inimigo : public Personagem {
		protected:
			int nivel_maldade;
			Jogador* pJog;
			short moverAleatorio;
		public:
			Inimigo(Vector2f pos, Jogador* jog, Vector2f velocidade = Vector2f(0.f, 0.f));
			~Inimigo();
			//void salvarDataBuffer();
			virtual void executar() = 0;
			virtual void danificar() = 0;
			//virtual void salva() = 0;
			virtual void mover() = 0;
			virtual void carregarSprite() = 0;
		};
	} 
}
