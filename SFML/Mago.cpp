#include "Mago.hpp"
#include "Gerenciador_Colisoes.hpp"

namespace entidades {
	namespace personagens {

		Mago::Mago(Vector2f pos, Vector2f vel) :
			Personagem(pos, vel),
			pontos(0),
			invencibilidade(0.3f),
			danoClock(),
			ataqueClock(),
			naTeia(false),
			apto(true),
			listaEntidades(NULL),
			GC(NULL)
		{
			if (barraVida && barraFundo) {
				barraFundo->setPosition(Vector2f(pos.x -11.f, pos.y - 10.f));
				barraVida->setPosition(Vector2f(pos.x - 11.f, pos.y - 10.f));
			}

			carregarSprite();
		}

		Mago::~Mago() {
			GC = NULL;
			listaEntidades = NULL;
		}


		void Mago::incluirListaEntidades(listas::ListaEntidades* pLEnt) {
			listaEntidades = pLEnt;
		}

		void Mago::incluirGerenciadorColisoes(Gerenciadores::GerenciadorColisoes* pGC) {
			GC = pGC;
		}

		void Mago::executar() {
			gravidade();
			mover();
			posicaoBarra();
		}

		//void Mago::salvar() {}

		void Mago::mover() {
			attPos();
		}

		void Mago::processarInput(bool esquerda, bool direita, bool pular, bool atirar) {
			float t = naTeia ? 0.3f : 1.0f;

			if (pular) {
				if (emTerra && !naTeia) {
					emTerra = false;
					vel.y = -velocidadeInicial.y;
					tempoMovimento.restart();
				}
			}

			if (esquerda && !direita) {
				vel.x = velocidadeInicial.x * t;
				pos.x -= vel.x;
				setOlhandoDir(false);
			}

			if (direita && !esquerda) {
				vel.x = velocidadeInicial.x * t;
				pos.x += vel.x;
				setOlhandoDir(true);
			}

			if (atirar) {
				criarProjetil();
			}
		}

		const int Mago::getPontos() const {
			return pontos;
		}

		void Mago::adicionarPontos(int pts) {
			pontos += pts; 
		}

		void Mago::reseta(Vector2f posicao, int vidas, int pts) {
			setPos(posicao);
			num_vidas = vidas;
			pontos = pts;
			danoClock.restart();
			barraVida->setSize(Vector2f(40.f * (num_vidas / 15.f), 2.f));
		}

		void Mago::tomarDano(int dano, bool bond) {
			if (dano > 0 && !bond) {
				if (danoClock.getElapsedTime().asSeconds() < invencibilidade) {
					return;
				}
				int vidas = getVidas() - dano;
				if (vidas < 0) vidas = 0;
				setVidas(vidas);
				danoClock.restart();
				barraVida->setSize(Vector2f(40.f * (num_vidas / 15.f), 2.f));
			}
		}

		void Mago::posicaoBarra() {
			Vector2f barraPos = getPos();
			barraPos.y -=10.f;
			barraPos.x -= 11.f;
			if (barraVida && barraFundo) {
				barraFundo->setPosition(barraPos);
				barraVida->setPosition(barraPos);
			}
		}

		void Mago::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Idle1.png")) {
				throw "Textura não carregada";
			}
			setPos(pos);
		}

		void Mago::setNaTeia(bool estado) {
			naTeia = estado;
		}

		void Mago::criarProjetil() {
			if (apto && GC && listaEntidades) {
				apto = false;
				if (olhandoDir) {
					Projetil* p = new Projetil(Vector2f(pos.x + 20.f, pos.y + 10.f), olhandoDir, true);
					GC->incluirProjetil(p);
					listaEntidades->incluir(p);
				}
				else {
					Projetil* p = new Projetil(Vector2f(pos.x - 20.f, pos.y + 10.f), olhandoDir, true);
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