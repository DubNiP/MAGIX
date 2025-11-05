#include "Teia.hpp"

namespace entidades { 
	namespace obstaculos {

		Teia::Teia(Vector2f pos, Vector2f tam):
			Obstaculo(pos,tam)
		{
			carregarSprite();
		}
		Teia::~Teia() {

		}


		void Teia::executar() {
			attPos();
		}

		void Teia::obstaculizar(entidades::personagens::Jogador* p) {
			if (p) {
				p->setNaTeia(true);
			}
		}

		void Teia::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Web3.png", true, false)) {
				throw "Textura não carregada";
			}
			if (Sprite* sp = getSprite()) {
				sp->setTextureRect(IntRect(0, 0, static_cast<int>(largura), static_cast<int>(altura)));
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}
	} 
}