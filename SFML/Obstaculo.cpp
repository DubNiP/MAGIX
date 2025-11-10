#include "Obstaculo.hpp"

namespace entidades {
	namespace obstaculos {

		Obstaculo::Obstaculo(Vector2f pos , Vector2f tam, bool dano):
			Entidade(pos),
			danoso(dano),
			largura(tam.x),
			altura(tam.y)
		{
	
		}

		Obstaculo::~Obstaculo() {

		}

		//void Obstaculo::salvarDataBuffer(){}

		const bool Obstaculo::getDanoso() const {
			return danoso;
		}		
	} 
}