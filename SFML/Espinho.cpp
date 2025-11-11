#include "Espinho.hpp"


namespace entidades { 
	namespace obstaculos {

		Espinho::Espinho(Vector2f pos, Vector2f tam, int quantDano):
			Obstaculo(pos,tam,true),
			danosidade(quantDano)
		{
			carregarSprite();
		}

		Espinho::~Espinho() {

		}

		//void ObstDificil::salvarDataBuffer(){}


		void Espinho::executar() {
			attPos();
		}


		void Espinho::obstaculizar(entidades::personagens::Mago* p) {
			if (p) {
				p->setVidas(p->getVidas() - danosidade);
			}
		}

		const int Espinho::getDanosidade() const {
			return danosidade;
		}

		void Espinho::carregarSprite() {
			if (!carregarTexturaSprite("Textures/4 Conjoined Spikes.png", true, false)) {
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