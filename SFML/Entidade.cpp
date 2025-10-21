#include "Entidade.hpp"

Entidade::Entidade(Vector2f posicao):
	pos(posicao),
	shape()
{
	shape.setSize(Vector2f(50, 50));
	shape.setFillColor(Color::White);
	shape.setPosition(pos);
}

Entidade::~Entidade() {

}


//Fzer o getpos aq

void Entidade::draw(RenderWindow* window) {
	window->draw(shape);
}



void Entidade::attPos() {
	shape.setPosition(pos);
}

//Entidade::void salvarDataBuffer() {}

Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setCorShape(Color cor) { 
	shape.setFillColor(cor); 
}

void Entidade::setTamanhoShape(Vector2f tamanho) { 
	shape.setSize(tamanho); 
}

FloatRect Entidade::getBounds() const {
	return shape.getGlobalBounds();
}