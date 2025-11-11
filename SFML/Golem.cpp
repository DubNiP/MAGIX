#include "Golem.hpp"
#include <cmath>

namespace entidades {
	namespace personagens {

		Golem::Golem(Vector2f pos, Mago* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel, 1),
			tamanho(200),
			moverAleatorio(0),
			velocidadeInicialX(vel.x)  
		{
			relogio.restart();
			relogioDePulo.restart();
			carregarSprite();
			moverAleatorio = rand() % 2;
			if (barraVida && barraFundo) {
				barraFundo->setSize(Vector2f(50.f, 2.f));
				barraVida->setSize(Vector2f(50.f, 2.f));
				barraFundo->setPosition(Vector2f(pos.x + 10.f, pos.y - 10.f));
				barraVida->setPosition(Vector2f(pos.x + 10.f, pos.y - 10.f));
			}
		}

		Golem::~Golem()
		{
		}

		void Golem::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao, false);
			}
		}

		void Golem::tomarDano(int dano, bool bondade) {
			if (dano > 0 && bondade) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
					barraVida->setSize(Vector2f(40.f * (num_vidas / 10.f), 3.f));
				}
			}
		}

		void Golem::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (relogioDePulo.getElapsedTime().asSeconds() >= 3.0f && emTerra) {
				pular();
				relogioDePulo.restart();
				return;
			}

			if (fabs(posJog.x - posInim.x) < tamanho && fabs(posJog.y - posInim.y) < tamanho) {
				if (posJog.x > posInim.x) moverDireita();
				else if (getPos().x > 30.0f) moverEsquerda();
			}
			else {
				if (getPos().x < posInicial.x - tamanho * 0.5 && getPos().x < 30.0f) moverDireita();
				else if (getPos().x > posInicial.x + tamanho * 3 && getPos().x > 30.0f) moverEsquerda();
				else movimentoAleatorio();
			}
		}

		void Golem::pular() {
			if (emTerra && pJog) {
				Vector2f posJog = pJog->getPos();
				Vector2f posInim = getPos();

				
				if (posJog.x > posInim.x) {
					
					vel.x = velocidadeInicialX * 2.0f;  
				}
				else {
					if (getPos().x > 30.0f) {
						vel.x = -velocidadeInicialX * 2.0f;  
					}
					else {
						vel.x = velocidadeInicialX * 2.0f;  
					}
				}

				vel.y = -50.0f;
				emTerra = false;
			}
		}

		void Golem::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= velocidadeInicialX;  
			setPos(novaPos);
			setOlhandoDir(false);
		}

		void Golem::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += velocidadeInicialX;  
			setPos(novaPos);
			setOlhandoDir(true);
		}

		void Golem::movimentoAleatorio() {
			if (moverAleatorio % 2 == 0) moverDireita();
			else if (moverAleatorio % 2 != 0 && getPos().x > 30) moverEsquerda();

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
			posicaoBarra();
		}

		void Golem::posicaoBarra() {
			Vector2f barraPos = getPos();
			barraPos.y -= 10.f;
			barraPos.x += 10.f;
			if (barraVida && barraFundo) {
				barraFundo->setPosition(barraPos);
				barraVida->setPosition(barraPos);
			}
		}

		void Golem::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Golem_idle1.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(2.f, 2.f));
			setPos(pos);
			atualizaDirSprite();
		}
	}
}