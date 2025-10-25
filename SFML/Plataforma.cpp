#include "Plataforma.hpp"

Plataforma::Plataforma(Vector2f pos, Vector2f tam, bool dano):
	Obstaculo(pos,tam,dano)
{

}

Plataforma::~Plataforma() {

}

void Plataforma::executar() {
	attPos();
}

void Plataforma::obstaculizar(Jogador*p) {
	if (p) {
		//IMPLEMENTAR DANO OU OQ QUER QUE SEJA NO FUTURO.	
	}
}