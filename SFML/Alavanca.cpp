#include "Alavanca.hpp"


namespace entidades {
	namespace obstaculos {
		Alavanca::Alavanca(Vector2f pos, Vector2f tam, Plataforma* pPlat):
			Obstaculo(pos,tam),
			p(pPlat),
			acionada(false)
		{
			carregarSprite();
		}

		Alavanca::~Alavanca() {
			p = NULL;                  //listaEntidades já faz o delete.
		}

		void Alavanca::executar() {
			attPos();
		}

		void Alavanca::obstaculizar(entidades::personagens::Mago* pJ) {
			if (p) {
				p->setAtiva();
			}
		}

		void Alavanca::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Alavanca.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}
	}
}