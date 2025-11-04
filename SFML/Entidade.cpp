#include "Entidade.hpp"

Entidade::Entidade(Vector2f posicao, Vector2f velocidade) :
	Ente(),
	pos(posicao),
	emTerra(true),
	vel(velocidade),
	tempoMovimento(),
	forcaGravidade(30.f)
{
	velocidadeInicialY = velocidade.y;
	velocidadeInicialX = velocidade.x;
	attPos();
}

Entidade::~Entidade() {

}


Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setEmTerra(const bool v) {
	emTerra = v;
}

void Entidade::setPos(const Vector2f& p) {
	pos = p;
	attPos();
}

float Entidade::getVelocidade() const {
	return vel.x;
}

void Entidade ::setVelocidadeY(const float v) {
	vel.y = v;
}

void Entidade::setVelocidadeX(const float v) {
	vel.x = v;
}

void Entidade::attPos() {
	if (pSprite) {
		pSprite->setPosition(pos);
	}
}

void Entidade::gravidade() {
	float dt = tempoMovimento.getElapsedTime().asSeconds();

	const float TERMINAL = 30.f;   // velocidade máxima de queda (px/s)

	if (!emTerra) {
		vel.y += forcaGravidade * dt;

		if (vel.y > TERMINAL)
			vel.y = TERMINAL;
		
		pos.y += vel.y * dt;
	}
	else {
		tempoMovimento.getElapsedTime().asSeconds();
		pos.y += vel.y * dt;

		if (tempoMovimento.getElapsedTime().asSeconds() > 0.5)
			resetaRelogio();
	}

	attPos();
}

void Entidade::resetaRelogio() {
	tempoMovimento.restart();
}


//Entidade::void salvarDataBuffer() {}