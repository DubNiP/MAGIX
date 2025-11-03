#pragma once
#include "Entidade.hpp"

namespace entidades { 
	namespace personagens {

		class Personagem : public Entidade {
		protected:
			int num_vidas;
			float vel;
		public:
			Personagem(Vector2f pos, float velocidade = 0);
			~Personagem();
			//void salvarDataBuffer;
			virtual void executar() = 0;
			//virtual void salvar() = 0;
			virtual void mover() = 0;

			int getVidas() const;	
			void setVidas(int vidas); 
			float getVelocidade() const;
			virtual void tomarDano(int dano);
		};
	}
}