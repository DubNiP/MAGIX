#pragma once
#include "Personagem.hpp"

namespace entidades {
	namespace personagens {
		class Mago;  // Forward declaration
	}
}


namespace entidades {
	namespace personagens {

		class Inimigo : public Personagem {
		protected:
			int nivel_maldade;
			Mago* pJog;
			short moverAleatorio;
			Vector2f posInicial;
			int destruicao;
			Clock relogio;
			Clock relogioDePulo;
			bool bondade;
		public:
			Inimigo(Vector2f pos, Mago* jog, Vector2f velocidade = Vector2f(0.f, 0.f), int des = 0);
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
