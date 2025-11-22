#include "Obstaculo.hpp"

namespace entidades {
	namespace obstaculos {

		Obstaculo::Obstaculo(Vector2f pos, Vector2f tam, bool dano):
			Entidade(pos),
			danoso(dano),
			largura(tam.x),
			altura(tam.y)
		{
	
		}

		Obstaculo::~Obstaculo() {

		}
		
		void Obstaculo::salvarDataBuffer() {
			Entidade::salvarDataBuffer();

			tempBuffer << danoso << " "
				<< largura << " "
				<< altura << " ";
		}

		void Obstaculo::carregar(float larg, float alt, bool dano)
		{
			this->largura = larg;
			this->altura = alt;
			this->danoso = dano;

			resetaRelogio();
		}

		const bool Obstaculo::getDanoso() const {
			return danoso;
		}		
	} 
}