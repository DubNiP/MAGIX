#include "Teia.hpp"
#include "Mago.hpp"

namespace entidades { 
	namespace obstaculos {

		Teia::Teia(Vector2f pos, Vector2f tam):
			Obstaculo(pos,tam),
			vida(3),
			ativo(true)
		{
			carregarSprite();
		}
		Teia::~Teia() {

		}


		void Teia::executar() {
			attPos();
		}

		void Teia::obstaculizar(entidades::personagens::Mago* p) {
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
		void Teia::setVida(int v) {
			vida = v > 0 ? v : 0;
			ativo = (vida > 0);
		}
		const int Teia::getVida() const {
			return vida;
		}

		const bool Teia::getAtivo() const {
			return ativo;
		}
	} 
}