#include "Chefao.hpp"

namespace entidades {
	namespace personagens {

		Chefao::Chefao(Vector2f pos, Vector2f vel, Jogador* pJog) :
			Inimigo(pos, pJog, vel),
			raio(100.f),
			forca(15)
		{
			//carregarSprite();
			executar();
		}

		Chefao::~Chefao()
		{
		}

		void Chefao::danificar() {
			if (pJog) {
				pJog->tomarDano(forca);
			}
		}

		void Chefao::tomarDano(int dano) {
			if (dano > 0) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) {
						vidas = 0;
					}
					setVidas(vidas);
				}
			}
		}

		void Chefao::mover() {
			if (pJog) {
				Vector2f posJog = pJog->getPos();
				Vector2f posInim = getPos();

				if (fabs(posJog.x - posInim.x) > raio) {
					if (posJog.x > posInim.x) {
						posInim.x = posInim.x + vel.x;
						setPos(posInim);
					}
					else
					{
						posInim.x = posInim.x - vel.x;
						setPos(posInim);
					}
				}
			}
			for (int i = 0; i < 4; i++) {

				i > 1 ? moverDireita() : moverEsquerda();
			}
		}

		void Chefao::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel.x;
			setPos(novaPos);
		}

		void Chefao::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel.x;
			setPos(novaPos);
		}


		void Chefao::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
			if (posicaoJog.x < posicaoInim.x) {
				moverEsquerda();
			}
			else if (posicaoJog.x > posicaoInim.x) {
				moverDireita();
			}
		}

		void Chefao::executar() {
			mover();
			attPos();
		}

		void Chefao::carregarSprite() {                                                //MUDAR NO FUTURO!!!
			if (!carregarTexturaSprite("Textures/Chefao.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(2.2f, 2.2f));
			setPos(pos);
		}

		//void salvar() {}	
	}
}