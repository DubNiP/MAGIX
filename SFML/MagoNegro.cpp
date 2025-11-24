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
			faseAtual(NULL)
		{
			id = 3;
			carregarSprite();
			velocidadeInicial.y = vel.y;
			uniform_int_distribution<int> dist2(0, 3);
			moverAleatorio = dist2(rng);
			nivel_maldade = 10;
		}

		MagoNegro::~MagoNegro()
		{
			faseAtual = NULL;
		}

		void MagoNegro::setFaseAtual(fases::Fase* f) {
			faseAtual = f;
		}

		void MagoNegro::danificar(Mago* pJogador) {
			if (pJogador) {
				pJogador->tomarDano(destruicao, false);
			}
		}

		void MagoNegro::tomarDano(int dano, bool bond) {
			if (dano > 0 && bond) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
					barraVida.setSize(Vector2f(40.f * (num_vidas / 10.f), 3.f));
					if(pJog) {
						pJog->adicionarPontos(10);
						cout << "Pontos: " << pJog->getPontos() << endl;
					}
				}
			}
		}

		void MagoNegro::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();


			if(fabs(posJog.x - posInim.x) < tamanho && fabs(posJog.y - posInim.y) < tamanho / 2) {
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
				emTerra = false;
				vel.y = velocidadeInicial.y;
				relogioDePulo.restart();
				return;
			}

			if (fabs(posJog.x - posInim.x) + 150 < tamanho && fabs(posJog.y - posInim.y) < tamanho/2 && apto) {
				if (posJog.x > posInim.x) moverDireita();
				else moverEsquerda();
			}
			else {
				if (pos.x > 1240) { moverAleatorio = 1; }
				if (pos.x < 40) { moverAleatorio = 0; }
				movimentoAleatorio();
			}
		}

		void MagoNegro::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel.x;
			setPos(novaPos);
			setOlhandoDir(false);
		}

		void MagoNegro::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel.x;
			setPos(novaPos);
			setOlhandoDir(true);
		}

		void MagoNegro::movimentoAleatorio() {
			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				uniform_int_distribution<int> dist4(0, 3);
				moverAleatorio = dist4(rng);
				relogio.restart();
			}

			if (moverAleatorio % 2 == 0) moverDireita();
			else if (moverAleatorio % 2 != 0) moverEsquerda();

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

			buffer.open(caminho, ios::out | ios::app);

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
				<< apto << endl;
		}
		
		void MagoNegro::carregar(int num, int m, Mago* jog, short mA, Vector2f pI,int d, int t, bool apt) {
			Inimigo::carregar(num, m, jog, mA, pI, d);

			this->tamanho = t;
			this->apto = apt;
		}

		void MagoNegro::carregarSprite() {
			if (!carregarTexturaSprite("Textures/magoNegro.png")) {
				throw "Textura não carregada";
			}
			setPos(pos);
		}

	}
}