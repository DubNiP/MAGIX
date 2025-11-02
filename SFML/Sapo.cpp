#include "Sapo.hpp"
#include <cmath>

namespace entidades { 
	namespace personagens {

		Sapo::Sapo(Vector2f pos, float vel, Jogador* pJog) :
			Inimigo(pos, vel, pJog),
			raio(100.f),
			destruicao(7),
			relogio(),
			posInicial()
		{
			carregarSprite();
			executar();
		}

		Sapo::~Sapo()
		{
		}

		void Sapo::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao);
			}
		}

		void Sapo::tomarDano(int dano) {
			if (dano > 0) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
				}
			}
		}

		void Sapo::mover() {
			if (!pJog) {
				movimentoAleatorio();
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (fabs(posJog.x - posInim.x) < raio) {
				if (posJog.x > posInim.x) moverDireita();

				else moverEsquerda();

			}
			else {
				if (getPos().x < posInicial.x - raio * 2) moverDireita();
				else if (getPos().x > posInicial.x + raio * 2) moverEsquerda();
				else movimentoAleatorio();
			}
		}
		
		void Sapo::movimentoAleatorio() {
			if (moverAleatorio % 2 == 0) moverDireita();

			else moverEsquerda();


			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 2.0f) {
				moverAleatorio = rand() % 4;
				relogio.restart();
			}

		}

		void Sapo::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel;
			setPos(novaPos);
		}

		void Sapo::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel;
			setPos(novaPos);
		}


		void Sapo::perseguir(Vector2f posicaoJog, Vector2f posicaoInim) {
			if (posicaoJog.x < posicaoInim.x) {
				moverEsquerda();
			}
			else if (posicaoJog.x > posicaoInim.x) {
				moverDireita();
			}
		}

		void Sapo::executar() {
			mover();
			attPos();
		}

		void Sapo::carregarSprite() {                         
			if (!carregarTexturaSprite("Textures/Sapo.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(1.5f, 1.5f));
			setPos(pos);
		}

		//void salvar() {}	

	} 
}