#pragma once
#include "Entidade.hpp"

namespace entidades { 
	namespace personagens {

		class Personagem : public Entidade {
		protected:
			int num_vidas;
		public:
			Personagem(Vector2f pos, Vector2f velocidade = Vector2f(0.f, 0.f));
			~Personagem();
			//void salvarDataBuffer;
			virtual void executar() = 0;
			//virtual void salvar() = 0;
			virtual void mover() = 0;

			const int getVidas() const;
			void setVidas(int vidas);
			virtual void tomarDano(int dano, bool bond);
		};
	}
}