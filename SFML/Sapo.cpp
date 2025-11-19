#include "Sapo.hpp"
#include <cmath>

namespace entidades { 
	namespace personagens {

		Sapo::Sapo(Vector2f pos, Mago* pJog, Vector2f vel) :
			Inimigo(pos, pJog, vel, 2),
			raio(150.f),
			intervaloPulo(1.5f)
		{
			id = 2;
			velocidadeInicial.y = -vel.y;
			velocidadeInicial.x = vel.x;
			relogioDePulo.restart();
			
			carregarSprite();
		}

		Sapo::~Sapo()
		{
		}

		void Sapo::executar() {
			iniciarClocks();
			mover();
			attPos();
			gravidade();
			acelerar();
			posicaoBarra();
		}

		void Sapo::salvar() {
			tempBuffer.str("");
			tempBuffer.clear();

			Inimigo::salvarDataBuffer();

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

		void Sapo::salvarDataBuffer() {

			tempBuffer << raio << " "
			<< intervaloPulo << endl;

		}

		void Sapo::danificar() {
			if (pJog) {
				pJog->tomarDano(destruicao, false);
			}
		}

		void Sapo::tomarDano(int dano, bool bondade) {
			if (dano > 0 && bondade) {
				{
					int vidas = getVidas() - dano;
					if (vidas < 0) vidas = 0;
					setVidas(vidas);
					barraVida.setSize(Vector2f(30.f * (num_vidas / 10.f), 3.f));
				}
			}
		}

		void Sapo::mover() {
			if (!pJog) {
				return;
			}

			Vector2f posJog = pJog->getPos();
			Vector2f posInim = getPos();

			if (fabs(posJog.x - posInim.x) < raio && fabs(posJog.y - posInim.y) < raio) {
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
				uniform_int_distribution<int> dist2(0, 3);
				moverAleatorio = dist2(rng);
				relogio.restart();
			}

			if (moverAleatorio % 2 != 0) {
				moverEsquerda();
			}
			else {
				moverDireita();
			}
		}

		void Sapo::moverEsquerda() {

			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo && pos.x > 30) {

				relogioDePulo.restart();
				tempoAceleracao.restart();

				emTerra = false;
				emAceleracao = true;

				vel.y = velocidadeInicial.y;
				vel.x = -velocidadeInicial.x;
			}
			setOlhandoDir(false);
		}

		void Sapo::moverDireita() {
			
			if (emTerra && relogioDePulo.getElapsedTime().asSeconds() >= intervaloPulo) {

				emTerra = false;
				emAceleracao = true;

				relogioDePulo.restart();
				tempoAceleracao.restart();

				vel.y = velocidadeInicial.y;
				vel.x = velocidadeInicial.x;
			}
			setOlhandoDir(true);
		}

		void Sapo::carregarSprite() {                         
			if (!carregarTexturaSprite("Textures/Sapo.png", false, false)) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(1.5f, 1.5f));
			setPos(pos);
			atualizaDirSprite();
		}

	} 
}