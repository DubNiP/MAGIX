#include "Personagem.hpp"

namespace entidades {
	namespace personagens {

		Personagem::Personagem(Vector2f pos, Vector2f velocidade):
			Entidade(pos, velocidade),
			num_vidas(10)
		{
		}

		Personagem::~Personagem() {

		}

		//Personagem::salvarDataBuffer() {};

		const int Personagem::getVidas() const {
			return num_vidas;
		}

		void Personagem::setVidas(int vidas) { 
			num_vidas = vidas; 
		}

		void Personagem::tomarDano(int dano, bool bond) {
			if (dano > 0) {
				int vidas = getVidas() - dano;
				if (vidas < 0) vidas = 0;
				setVidas(vidas);
			}
		}
	} 
}