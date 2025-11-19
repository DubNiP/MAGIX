#include "Espinho.hpp"


namespace entidades { 
	namespace obstaculos {

		Espinho::Espinho(Vector2f pos, Vector2f tam, int quantDano):
			Obstaculo(pos,tam,true),
			danosidade(quantDano)
		{
			id = 8;
			carregarSprite();
		}

		Espinho::~Espinho() {

		}

		void Espinho::salvar() {
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

		void Espinho::salvarDataBuffer() {
			Obstaculo::salvarDataBuffer();

			tempBuffer << danosidade << "\n";
		}

		void Espinho::executar() {
			attPos();
		}


		void Espinho::obstaculizar(entidades::personagens::Mago* p) {
			if (p) {
				p->tomarDano(danosidade, false);
			}
		}

		const int Espinho::getDanosidade() const {
			return danosidade;
		}

		void Espinho::carregarSprite() {
			if (!carregarTexturaSprite("Textures/4 Conjoined Spikes.png", true, false)) {
				throw "Textura não carregada";
			}
			if (Sprite* sp = getSprite()) {
				sp->setTextureRect(IntRect(0, 0, static_cast<int>(largura), static_cast<int>(altura)));
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}
	} 
}