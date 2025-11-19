#include "Mago.hpp"
#include "fase.hpp"

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
			concluiuFase(false),
			faseAtual(NULL)
		{
			id = 1;
			carregarSprite();
		}

		Mago::~Mago() {
			faseAtual = NULL;
		}

		void Mago::executar() {
			if (faseAtual && faseAtual->getFaseIniciada()) {
				iniciarClocks();
			}
			gravidade();
			mover();
			posicaoBarra();
		}

		void Mago::salvar() {
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

		void Mago::salvarDataBuffer() {
			Personagem::salvarDataBuffer();

			tempBuffer << pontos << " " 
				<< invencibilidade << " " 
				<< danoClock.getElapsedTime().asSeconds() << " " 
				<< ataqueClock.getElapsedTime().asSeconds() << " " 
				<< naTeia << " " 
				<< apto << " " 
				<< concluiuFase << endl;
			
		}

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
				if (ataqueClock.getElapsedTime().asSeconds() > 1.f) {
					apto = true;
					ataqueClock.restart();
				}
				if (apto) {
					apto = false;
						if(faseAtual)
							faseAtual->criarProjetil(getPos(), olhandoDir, true);
				}
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
			ataqueClock.restart();
			clocksIni = false;
			vel.y = 0.f;
			emTerra = true;
			barraVida.setSize(Vector2f(30.f * (num_vidas / 15.f), 2.f));
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
				barraVida.setSize(Vector2f(30.f * (num_vidas / 15.f), 2.f));
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

		void Mago::setConcluiuFase(bool c) {
			concluiuFase = c;
		}	

		void Mago::setFaseAtual(fases::Fase* f) {
			faseAtual = f;
		}

		bool Mago::getConcluiuFase() const {
			return concluiuFase;
		}	

	} 
}