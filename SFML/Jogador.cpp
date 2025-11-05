#include "Jogador.hpp"
#include "Gerenciador_Grafico.hpp"

namespace entidades {
	namespace personagens {

		Jogador::Jogador(Vector2f pos, Vector2f vel) :
			Personagem(pos, vel),
			pontos(0),
			invencibilidade(30.f),
			danoClock(),
			naTeia(false)
		{
			carregarSprite();
		}

		Jogador::~Jogador() {
		}

		//void Jogador::colidir(Inimigo* pIn) {}

		void Jogador::executar() {
			processarInput();
			gravidade();
			mover();
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
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
				vel.x = velocidadeInicialX * t;
				pos.x += vel.x;
			}
		}

		int Jogador::getPontos() const { 
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
		}

		void Jogador::tomarDano(int dano) {
			if (dano > 0) {
				if (danoClock.getElapsedTime().asSeconds() < invencibilidade) {
					return;
				}
				int vidas = getVidas() - dano;
				if (vidas < 0) vidas = 0;
				setVidas(vidas);
				danoClock.restart();
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
	} 
}