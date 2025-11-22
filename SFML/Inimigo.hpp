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
			float tempSalvo;
			float tempPuloSalvo;
			bool bondade;
		public:
			Inimigo(Vector2f pos, Mago* jog, Vector2f velocidade = Vector2f(0.f, 0.f), int des = 0);
			~Inimigo();
			void salvarDataBuffer();
			virtual void salvar() = 0;
			void carregar(int num, int m, Mago* jog, short mA, Vector2f pI,
				int d, float tS, float tP);
			virtual void executar() = 0;
			virtual void danificar(Mago* pJog) = 0;
			virtual void mover() = 0;
			virtual void carregarSprite() = 0;
		};
	} 
}
