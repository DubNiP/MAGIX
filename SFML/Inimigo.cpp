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
				<< relogioDePulo.getElapsedTime().asSeconds() << " ";
		}

		void Inimigo::carregar(int num, int m, Mago* jog, short mA, Vector2f pI,
			int d, float tS, float tP) {
			
			this->num_vidas = num;
			this->nivel_maldade = m;
			this->pJog = jog;
			this->moverAleatorio = mA;
			this->posInicial = pI;
			this->destruicao = d;
			this->tempSalvo = tS;
			this->tempPuloSalvo = tP;
			relogio.restart();
			relogioDePulo.restart();
			barraVida.setSize(Vector2f(30.f * (num_vidas / 10.f), 2.f));
			retomar();
		}
	} 
}

