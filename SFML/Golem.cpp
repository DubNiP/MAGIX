#include "Golem.hpp"

namespace entidades {
	namespace personagens {

		Golem::Golem(Vector2f pos, Mago* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel, 1),
			tamanho(200)
		{
			id = 4;
			relogio.restart();
			relogioDePulo.restart();
			carregarSprite();
			velocidadeInicial.y = vel.y;
			uniform_int_distribution<int> dist2(0, 3);
			moverAleatorio = dist2(rng);
			nivel_maldade = 7;
		}

		Golem::~Golem()
		{
		}

		void Golem::danificar(Mago* pJogador) {
			if (pJogador) {
				pJogador->tomarDano(destruicao, false);
			}
		}

		void Golem::tomarDano(int dano, bool bondade) {
			if (dano > 0 && bondade) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
					barraVida.setSize(Vector2f(30.f * (num_vidas / 10.f), 3.f));
					if(pJog){
						pJog->adicionarPontos(15);
						cout << "Pontos: " << pJog->getPontos() << endl;
					}

				}
			}
		}

		void Golem::mover() {
			if (pJog) {
				Vector2f posJog = pJog->getPos();
				Vector2f posInim = getPos();

				if (relogioDePulo.getElapsedTime().asSeconds() >= 3.0f && emTerra) {
					vel.y = -60.f;
					emTerra = false;
					relogioDePulo.restart();
					return;
				}

				if (fabs(posJog.x - posInim.x) < tamanho && fabs(posJog.y - posInim.y) < tamanho) {
					if (posJog.x > posInim.x) moverDireita();
					else moverEsquerda();
				}
				else {
					if (pos.x > 1240) {
						moverAleatorio = 1;
					}
					if (pos.x < 40) {
						moverAleatorio = 0; 
					}
					movimentoAleatorio();
				}
			}
		}

		void Golem::moverEsquerda() {
			Vector2f novaPos = getPos();
			novaPos.x -= vel.x;  
			setPos(novaPos);
			setOlhandoDir(false);
		}

		void Golem::moverDireita() {
			Vector2f novaPos = getPos();
			novaPos.x += vel.x;  
			setPos(novaPos);
			setOlhandoDir(true);
		}

		void Golem::movimentoAleatorio() {

			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				uniform_int_distribution<int> dist2(0, 3);
				moverAleatorio = dist2(rng);
				relogio.restart();
			}

			if (moverAleatorio % 2 == 0) moverDireita();
			else if (moverAleatorio % 2 != 0) moverEsquerda();
		}

		void Golem::executar() {
			iniciarClocks();
			mover();
			attPos();
			gravidade();
			posicaoBarra();
		}

		void Golem::salvar() {
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

		void Golem::salvarDataBuffer() {

			Inimigo::salvarDataBuffer();

			tempBuffer << tamanho << endl;
		}

		void Golem::carregar(int num, int m, Mago* jog, short mA, Vector2f pI,
			int d, int tam) {
			Inimigo::carregar(num, m, jog, mA, pI, d);
			this->tamanho = tam;
		}

		void Golem::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Golem_idle1.png")) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(2.f, 2.f));
			setPos(pos);
			atualizaDirSprite();
		}
	}
}