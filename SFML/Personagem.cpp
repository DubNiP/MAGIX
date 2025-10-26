#include "Personagem.hpp"

Personagem::Personagem(Vector2f pos, float velocidade):
	Entidade(pos),
	num_vidas(1000),
	vel(velocidade)
{
}

Personagem::~Personagem() {

}

//Personagem::salvarDataBuffer() {};

int Personagem::getVidas() const {
	return num_vidas;
}

void Personagem::setVidas(int vidas) { 
	num_vidas = vidas; 
}
float Personagem::getVelocidade() const { 
	return vel; 
}