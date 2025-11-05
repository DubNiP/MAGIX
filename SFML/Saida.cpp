#include "Saida.hpp"

namespace entidades {
	namespace obstaculos {

		Saida::Saida(Vector2f pos, Vector2f tam) :
			Obstaculo(pos,tam)
		{
			setSprite();
		}

		Saida::~Saida() {

		}

		void Saida::executar() {
			attPos();
		}

		void Saida::obstaculizar(entidades::personagens::Jogador* p) {
		}

		void Saida::setSprite() {
			if (!carregarTexturaSprite("Textures/Saida.png", true, false)) {
				throw "Textura não carregada";
			}
			if (Sprite* sp = getSprite()) {
				sp->setTextureRect(IntRect(0, 0, static_cast<int>(largura), static_cast<int>(altura)));
			}
			setScale(Vector2f(1.5f, 1.5f));
			setPos(pos);
		}
	}
}