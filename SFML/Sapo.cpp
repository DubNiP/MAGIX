#include "Sapo.hpp"
#include <cmath>

namespace entidades { 
	namespace personagens {

		Sapo::Sapo(Vector2f pos, Jogador* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel),
			raio(150.f),
			destruicao(3),
			relogio(),
			posInicial()
		{
			posInicial = pos;
			forcaGravidade = 40;
			velocidadeInicialY = -vel.y;
			relogioDePulo.restart();
			intervaloPulo = 1.5f;
			carregarSprite();
			executar();
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
			else if (posInim.x > alcanceDireita * 1.5) {
				moverEsquerda();
			}
			else {
				movimentoAleatorio();
			}
		}
		
		void Sapo::movimentoAleatorio() {

			float dt = relogio.getElapsedTime().asSeconds();
			if (dt >= 1.0f) {
				moverAleatorio = rand() % 4; 
				relogio.restart();
			}

			if (moverAleatorio % 2 != 1) {
				moverDireita();
			}
			else if (moverAleatorio % 2 == 0) {
				if (getPos().x > 30.0f) moverEsquerda();
			}
		}

		void Sapo::moverEsquerda() {

			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo) {
				
				relogioDePulo.restart();
				emTerra = false;
				
				Vector2f novaPos = getPos();
				novaPos.x -= vel.x;
				vel.y = velocidadeInicialY; // negativo para subir
				setPos(novaPos);
			}
		}

		void Sapo::moverDireita() {
			
			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo) {

				emTerra = false;
				relogioDePulo.restart();

				Vector2f novaPos = getPos();
				vel.y = velocidadeInicialY;
				novaPos.x += vel.x;
				setPos(novaPos);
			}
		}

		void Sapo::executar() {
			mover();
			attPos();
			gravidade();
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