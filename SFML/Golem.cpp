#include "Golem.hpp"

namespace entidades { 
	namespace personagens {

		Golem::Golem(Vector2f pos, float vel, Jogador* pJog) :
			Inimigo(pos, vel, pJog), 
			relogio(),
			tamanho(100)
		{
			relogio.restart();
			posInicial = pos;
			destruicao = 1;
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
				movimentoAleatorio();
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (fabs(posJog.x - posInim.x) < tamanho) {
				if (posJog.x > posInim.x) moverDireita();

				else moverEsquerda();

			}
			else {
				if (getPos().x < posInicial.x - tamanho * 2) moverDireita();
				else if (getPos().x > posInicial.x + tamanho * 2) moverEsquerda();
				else movimentoAleatorio();
			}
		}

		void Golem::movimentoAleatorio() {
			if (moverAleatorio % 2 == 0) moverDireita();

			else moverEsquerda();


			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 2.0f) {
				moverAleatorio = rand() % 4;
				relogio.restart();
			}

		}

		void Golem::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel;
			setPos(novaPos);
		}

		void Golem::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel;
			setPos(novaPos);
		}

		void Golem::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
			if (posicaoJog.x < posicaoInim.x)	moverEsquerda();
	
			else if (posicaoJog.x > posicaoInim.x) moverDireita();
	
		}

		void Golem::executar() {
			mover();
			attPos();
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