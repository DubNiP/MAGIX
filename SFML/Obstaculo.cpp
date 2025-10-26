#include "Obstaculo.hpp"

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

bool Obstaculo::getDanoso() const {
	return danoso;
}