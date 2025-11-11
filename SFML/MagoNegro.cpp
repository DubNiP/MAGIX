#include "MagoNegro.hpp"
#include "ListaEntidades.hpp"
#include <cmath>
#include "Projetil.hpp"
#include "Gerenciador_Colisoes.hpp"


namespace entidades {
	namespace personagens {

		MagoNegro::MagoNegro(Vector2f pos, Mago* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel, 1),
			tamanho(400),
			ataqueClock(),
			apto(true),
			moverAleatorio(0),
			velocidadeInicialX(vel.x)
		{
			carregarSprite();
			moverAleatorio = rand() % 2;
			if (barraVida && barraFundo) {
				barraFundo->setSize(Vector2f(50.f, 2.f));
				barraVida->setSize(Vector2f(50.f, 2.f));
				barraFundo->setPosition(Vector2f(pos.x + 10.f, pos.y - 10.f));
				barraVida->setPosition(Vector2f(pos.x + 10.f, pos.y - 10.f));
			}
		}

		MagoNegro::~MagoNegro()
		{
		}

		void MagoNegro::incluirListaEntidades(listas::ListaEntidades* pLEnt) {
			listaEntidades = pLEnt;
		}

		void MagoNegro::incluirGerenciadorColisoes(Gerenciadores::GerenciadorColisoes* pGC) {
			GC = pGC;
		}


		void MagoNegro::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao, false);
			}
		}

		void MagoNegro::tomarDano(int dano, bool bond) {
			if (dano > 0 && bond) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
					barraVida->setSize(Vector2f(40.f * (num_vidas / 10.f), 3.f));
				}
			}
		}

		void MagoNegro::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();


			if(fabs(posJog.x - posInim.x) < tamanho) {
				criarProjetil();
			}

			if (relogioDePulo.getElapsedTime().asSeconds() >= 3.0f && emTerra) {
				pular();
				relogioDePulo.restart();
				return;
			}

			if (fabs(posJog.x - posInim.x) + 150 < tamanho && fabs(posJog.y - posInim.y) + 150 < tamanho && apto) {
				if (posJog.x > posInim.x) {
					moverDireita();
				}
				else {
					moverEsquerda();
				}
			}
			else {
				if (getPos().x < posInicial.x - tamanho * 0.5 && getPos().x < 50.0f || getPos().x < 30.f) moverDireita();
				else if (getPos().x > posInicial.x + tamanho * 3 && getPos().x > 50.0f || getPos().x > 1250.f) moverEsquerda();
				else movimentoAleatorio();
			}
		}


		void MagoNegro::pular() {
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

		void MagoNegro::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= velocidadeInicialX;
			setPos(novaPos);
			setOlhandoDir(false);
		}

		void MagoNegro::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += velocidadeInicialX;
			setPos(novaPos);
			setOlhandoDir(true);
		}

		void MagoNegro::movimentoAleatorio() {
			if (moverAleatorio % 2 == 0) moverDireita();
			else if (moverAleatorio % 2 != 0 && getPos().x > 30) moverEsquerda();

			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				moverAleatorio = rand() % 4;
				relogio.restart();
			}
		}

		void MagoNegro::executar() {
			mover();
			attPos();
			gravidade();
			posicaoBarra();
		}

		void MagoNegro::posicaoBarra() {
			Vector2f barraPos = getPos();
			barraPos.y -= 10.f;
			barraPos.x += 10.f;
			if (barraVida && barraFundo) {
				barraFundo->setPosition(barraPos);
				barraVida->setPosition(barraPos);
			}
		}

		void MagoNegro::carregarSprite() {
			if (!carregarTexturaSprite("Textures/magoNegro.png", false, false)) {
				throw "Textura não carregada";
			}
			setPos(pos);
		}

		void MagoNegro::criarProjetil() {
			if (apto && GC && listaEntidades) {
				apto = false;
				if (pJog->getPos().x > getPos().x) {
					Projetil* p = new Projetil(Vector2f(pos.x + 20.f, pos.y + 10.f), true, false);
					GC->incluirProjetil(p);
					listaEntidades->incluir(p);
				}
				else {
					Projetil* p = new Projetil(Vector2f(pos.x - 20.f, pos.y + 10.f), false, false);
					GC->incluirProjetil(p);
					listaEntidades->incluir(p);
				}
			}

			if (ataqueClock.getElapsedTime().asSeconds() > 1.f) {
				apto = true;
				ataqueClock.restart();
			}
		}
	}
}