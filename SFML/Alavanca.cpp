#include "Alavanca.hpp"
#include <filesystem>

namespace entidades {
	namespace obstaculos {
		Alavanca::Alavanca(Vector2f pos, Vector2f tam, Plataforma* pPlat):
			Obstaculo(pos,tam),
			p(pPlat),
			acionada(false)
		{
			id = 9;
			carregarSprite();
		}

		Alavanca::~Alavanca() {
			p = NULL;                
		}

		void Alavanca::executar() {
			gravidade();
			vel.y = 0.f;
			attPos();
		}

		void Alavanca::salvar() {
			tempBuffer.str("");
			tempBuffer.clear();

			salvarDataBuffer();

			buffer.open(caminho, ios::out | ios::app);

			if (!buffer.is_open()) {
				cout << "Arquivo não pode ser aberto" << endl;
				fflush(stdin);
				return;
			}
			buffer << tempBuffer.str();

			buffer.close();
		}

		void Alavanca::salvarDataBuffer() {
			Obstaculo::salvarDataBuffer();

			tempBuffer << acionada << endl;
		}

		void Alavanca::carregar(float l, float a, bool dano, bool acionado) {
			Obstaculo::carregar(l, a, dano);
			acionada = acionado;
		}

		void Alavanca::obstaculizar(entidades::personagens::Mago* pJ) {
			if (p) {
				p->setAtiva();
			}
		}

		void Alavanca::carregarSprite() {
			if (!carregarTexturaSprite("Textures/Alavanca.png")) {
				throw "Textura não carregada";
			}
			setScale(Vector2f(1.f, 1.f));
			setPos(pos);
		}

	}
}