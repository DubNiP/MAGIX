#include "Jogador.hpp"
#include "Gerenciador_Colisoes.hpp"

namespace entidades {
	namespace personagens {

		Jogador::Jogador(Vector2f pos, Vector2f vel) :
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

		Jogador::~Jogador() {
			GC = NULL;
			listaEntidades = NULL;
		}


		void Jogador::incluirListaEntidades(listas::ListaEntidades* pLEnt) {
			listaEntidades = pLEnt;
		}

		void Jogador::incluirGerenciadorColisoes(Gerenciadores::GerenciadorColisoes* pGC) {
			GC = pGC;
		}

		void Jogador::executar() {
			processarInput();
			gravidade();
			mover();
			posicaoBarra();
		}

		//void Jogador::salvar() {}

		void Jogador::mover() {
			attPos();
		}

		void Jogador::processarInput() {
			float t = naTeia ? 0.3f : 1.0f;
			if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))) {
				if (emTerra && !naTeia) {
					emTerra = false;
					vel.y = -velocidadeInicialY;
					tempoMovimento.restart();

				}
			}
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				vel.x = velocidadeInicialX * t;
				pos.x -= vel.x;
				setOlhandoDir(false);
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
				vel.x = velocidadeInicialX * t;
				pos.x += vel.x;
				setOlhandoDir(true);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) ){

				criarProjetil();
			}
		}

		const int Jogador::getPontos() const { 
			return pontos;
		}

		void Jogador::adicionarPontos(int pts) { 
			pontos += pts; 
		}

		void Jogador::reseta(Vector2f posicao, int vidas, int pts) {
			setPos(posicao);
			num_vidas = vidas;
			pontos = pts;
			danoClock.restart();
			barraVida->setSize(Vector2f(40.f * (num_vidas / 15.f), 2.f));
		}

		void Jogador::tomarDano(int dano, bool bond) {
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

		void Jogador::posicaoBarra() {
			Vector2f barraPos = getPos();
			barraPos.y -=10.f;
			barraPos.x -= 11.f;
			if (barraVida && barraFundo) {
				barraFundo->setPosition(barraPos);
				barraVida->setPosition(barraPos);
			}
		}

		void Jogador::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Idle1.png")) {
				throw "Textura não carregada";
			}
			setPos(pos);
		}

		void Jogador::setNaTeia(bool estado) { 
			naTeia = estado;
		}

		void Jogador::criarProjetil() {
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