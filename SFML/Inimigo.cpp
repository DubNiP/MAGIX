#include "Inimigo.hpp"

namespace entidades {
	namespace personagens {

		Inimigo::Inimigo(Vector2f pos, Jogador* jog, Vector2f vel) :
			Personagem(pos, vel),
			nivel_maldade(3),
			moverAleatorio(-1),
			pJog(jog)
		{
		}

		Inimigo::~Inimigo() {

		}
	} 
}

