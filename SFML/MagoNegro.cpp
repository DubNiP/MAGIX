#include "MagoNegro.hpp"
#include "Projetil.hpp"
#include "Fase.hpp"


namespace entidades {
	namespace personagens {

		MagoNegro::MagoNegro(Vector2f pos, Mago* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel, 1),
			tamanho(300),
			ataqueClock(),
			apto(true),
			moverAleatorio(0),
			velocidadeInicialX(vel.x),
			faseAtual(NULL)
		{
			id = 3;
			carregarSprite();
			uniform_int_distribution<int> dist2(0, 3);
			moverAleatorio = dist2(rng);
			
		}

		MagoNegro::~MagoNegro()
		{
			faseAtual = NULL;
		}

		void MagoNegro::setFaseAtual(fases::Fase* f) {
			faseAtual = f;
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
					barraVida.setSize(Vector2f(40.f * (num_vidas / 10.f), 3.f));
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
				if (ataqueClock.getElapsedTime().asSeconds() > 1.f) {
					apto = true;
					ataqueClock.restart();
				}
				if (apto) {
					apto = false;
						if(faseAtual)
							faseAtual->criarProjetil(getPos(), posJog.x > posInim.x, false);
				}
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
				uniform_int_distribution<int> dist4(0, 3);
				moverAleatorio = dist4(rng);
				relogio.restart();
			}
		}

		void MagoNegro::executar() {
			iniciarClocks();
			mover();
			attPos();
			gravidade();
			posicaoBarra();
		}

		void MagoNegro::salvar() {
			tempBuffer.str("");
			tempBuffer.clear();

			salvarDataBuffer();

			buffer.open("Save/save.txt", ios::out | ios::app);

			if (!buffer.is_open()) {
				cerr << "Arquivo não pode ser aberto" << endl;
				fflush(stdin);
				return;
			}

			buffer << tempBuffer.str();

			buffer.close();
		}

		void MagoNegro::salvarDataBuffer() {
			Inimigo::salvarDataBuffer();

			tempBuffer << tamanho << " "
				<< ataqueClock.getElapsedTime().asSeconds() << " "
				<< apto << " "
				<< moverAleatorio << " "
				<< velocidadeInicialX << " "
				<< faseAtual << "fim" << "\n";
		}

		void MagoNegro::carregarSprite() {
			if (!carregarTexturaSprite("Textures/magoNegro.png", false, false)) {
				throw "Textura não carregada";
			}
			setPos(pos);
		}

	}
}