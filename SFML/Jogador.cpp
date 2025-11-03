#include "Jogador.hpp"
#include "Gerenciador_Grafico.hpp"

namespace entidades {
	namespace personagens {

		Jogador::Jogador(Vector2f pos, float vel) :
			Personagem(pos, vel),
			pontos(0),
			invencibilidade(0.3f),
			danoClock()
		{
			carregarSprite();
		}

		Jogador::~Jogador() {
		}

		//void Jogador::colidir(Inimigo* pIn) {}

		void Jogador::executar() {
			processarInput(); 
			mover();
		}

		//void Jogador::salvar() {}

		void Jogador::mover() {
			attPos();
		}


		void Jogador::processarInput() {
			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
				pos.y -= vel;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
				pos.y += vel;
			}
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				pos.x -= vel;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
				pos.x += vel;
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
	} 
}