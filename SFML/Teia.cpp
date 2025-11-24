#include "Teia.hpp"
#include "Mago.hpp"

namespace entidades { 
	namespace obstaculos {

		Teia::Teia(Vector2f pos, Vector2f tam):
			Obstaculo(pos,tam),
			vida(3),
			ativo(true)
		{
			id = 5;
			carregarSprite();
		}
		Teia::~Teia() {

		}


		void Teia::executar() {
			gravidade();
			vel.y = 0.f;
			attPos();
		}

		void Teia::salvar() {
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

		void Teia::salvarDataBuffer() {
			Obstaculo::salvarDataBuffer();

			tempBuffer << vida << " "
			<< ativo << " "
			<< endl;
		}

		void Teia::carregar(float larg, float alt, bool dano, int v, bool atv) {
			Obstaculo::carregar(larg, alt, dano);
			vida = v;
			ativo = atv;
		}

		void Teia::obstaculizar(entidades::personagens::Mago* p) {
			if (p) {
				p->setNaTeia(true);
			}
		}

		void Teia::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Web3.png", true, false)) {
				throw "Textura não carregada";
			}
			if (Sprite* sp = getSprite()) {
				sp->setTextureRect(IntRect(0, 0, static_cast<int>(largura), static_cast<int>(altura)));
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}
		void Teia::setVida(int v) {
			vida = v > 0 ? v : 0;
			ativo = (vida > 0);
		}
		const int Teia::getVida() const {
			return vida;
		}

		const bool Teia::getAtivo() const {
			return ativo;
		}
	} 
}