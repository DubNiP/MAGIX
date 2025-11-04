#include "Golem.hpp"

namespace entidades { 
	namespace personagens {

		Golem::Golem(Vector2f pos, Jogador* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel),
			tamanho(300),
			destruicao(1),
			relogio(),
			posInicial(pos)
		{
			relogio.restart();
			carregarSprite();
			moverAleatorio = rand() % 2;
		}

		Golem::~Golem()
		{
		}


		void Golem::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao);
			}
		}

		void Golem::tomarDano(int dano) {
			if (dano > 0) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
				}
			}
		}

		void Golem::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (fabs(posJog.x - posInim.x) < tamanho) {
				if (posJog.x > posInim.x) moverDireita();

				else if(getPos().x > 30.0f){
					moverEsquerda();
				}

			}
			else {
				if (getPos().x < posInicial.x - tamanho * 0.5 && getPos().x < 30.0f) moverDireita();
				else if (getPos().x > posInicial.x + tamanho * 3 && getPos().x > 30) moverEsquerda();
				else movimentoAleatorio();
			}
		}

		void Golem::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel.x;
			setPos(novaPos);
		}

		void Golem::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel.x;
			setPos(novaPos);
		}

		void Golem::movimentoAleatorio() {
			if (moverAleatorio % 2 == 0) moverDireita();

			else if(moverAleatorio % 2 != 0 && getPos().x > 30) moverEsquerda();


			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				moverAleatorio = rand() % 4;
				relogio.restart();
			}

		}

		void Golem::executar() {
			mover();
			attPos();
			gravidade();
		}

		void Golem::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Golem_idle1.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(2.f, 2.f));
			setPos(pos);
		}


		//void salvar() {}	
	} 
}