#include "Entidade.hpp"

Entidade::Entidade(Vector2f posicao):
	Ente(),
	pos(posicao)
{
	attPos();
}

Entidade::~Entidade() {

}


Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setPos(const Vector2f& p) {
	pos = p;
	attPos();
}

void Entidade::attPos() {
	if (pSprite) {
		pSprite->setPosition(pos);
	}
}


//Entidade::void salvarDataBuffer() {}