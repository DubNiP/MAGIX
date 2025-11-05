#include "Sapo.hpp"
#include <cmath>

namespace entidades { 
	namespace personagens {

		Sapo::Sapo(Vector2f pos, Jogador* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel),
			raio(150.f),
			destruicao(2),
			relogio(),
			posInicial(pos),
			relogioDePulo(),
			intervaloPulo(1.5f)
		{
			velocidadeInicialY = -vel.y;
			velocidadeInicialX = vel.x;
			relogioDePulo.restart();
			carregarSprite();
		}

		Sapo::~Sapo()
		{
		}

		void Sapo::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao);
			}
		}

		void Sapo::tomarDano(int dano) {
			if (dano > 0) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
				}
			}
		}

		void Sapo::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (fabs(posJog.x - posInim.x) < raio) {
				intervaloPulo = 1.0f;
				if (posJog.x > posInim.x) moverDireita();

				else moverEsquerda();

				return;
			}

			const float alcanceEsquerda = posInicial.x - raio;
			const float alcanceDireita = posInicial.x + raio;
			intervaloPulo = 0.8f;

			if (posInim.x < alcanceEsquerda * 0.5) {
				moverDireita();
			}
			else if (posInim.x > alcanceDireita * 0.5) {
				moverEsquerda();
			}
			else {
				movimentoAleatorio();
			}
		}
		
		void Sapo::movimentoAleatorio() {

			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				moverAleatorio = rand() % 2; 
				relogio.restart();
			}

			if (moverAleatorio % 2 != 1) {
				moverDireita();
			}
			else {
				moverEsquerda();
			}
		}

		void Sapo::moverEsquerda() {

			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo && pos.x > 30) {

				relogioDePulo.restart();
				tempoAceleracao.restart();

				emTerra = false;
				emAceleracao = true;

				vel.y = velocidadeInicialY;
				vel.x = -velocidadeInicialX;
			}
		}

		void Sapo::moverDireita() {
			
			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo) {

				emTerra = false;
				emAceleracao = true;

				relogioDePulo.restart();
				tempoAceleracao.restart();

				vel.y = velocidadeInicialY;
				vel.x = velocidadeInicialX;
			}
		}

		void Sapo::executar() {
			mover();
			attPos();
			gravidade();
			acelerar();
		}

		void Sapo::carregarSprite() {                         
			if (!carregarTexturaSprite("Textures/Sapo.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(1.5f, 1.5f));
			setPos(pos);
		}

		//void salvar() {}	

	} 
}