#include "Inimigo.hpp"

namespace entidades {
	namespace personagens {

		Inimigo::Inimigo(Vector2f pos, Mago* jog, Vector2f vel, int des) :
			Personagem(pos, vel),
			nivel_maldade(3),
			pJog(jog),
			moverAleatorio(-1),
			posInicial(pos),
			destruicao(des),
			relogio(),
			relogioDePulo(),
			bondade(false)
		{
		}

		Inimigo::~Inimigo() {

		}

		void Inimigo::salvarDataBuffer() {
			Personagem::salvarDataBuffer();

			tempBuffer << nivel_maldade << " "
				<< moverAleatorio << " "
				<< posInicial.x << " "
				<< posInicial.y << " "
				<< destruicao << " "
				<< relogio.getElapsedTime().asSeconds() << " "
				<< relogioDePulo.getElapsedTime().asSeconds() << " "
				<< bondade << " ";
		}
	} 
}

