#include "Personagem.hpp"

namespace entidades {
	namespace personagens {

		Personagem::Personagem(Vector2f pos, Vector2f velocidade):
			Entidade(pos, velocidade),
			num_vidas(1000)
		{
		}

		Personagem::~Personagem() {

		}

		//Personagem::salvarDataBuffer() {};

		int Personagem::getVidas() const {
			return num_vidas;
		}

		void Personagem::setVidas(int vidas) { 
			num_vidas = vidas; 
		}

		float Personagem::getVelocidade() const { 
			return vel; 
		}

		void Personagem::setVelocidade(float velo) {
			vel = velo;
		}

		void Personagem::tomarDano(int dano) {
			if (dano > 0) {
				int vidas = getVidas() - dano;
				if (vidas < 0) vidas = 0;
				setVidas(vidas);
			}
		}
	} 
}