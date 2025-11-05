#include "Entidade.hpp"

Entidade::Entidade(Vector2f posicao, Vector2f velocidade) :
	Ente(),
	pos(posicao),
	emTerra(true),
	vel(velocidade),
	velocidadeInicialY(velocidade.y),
	velocidadeInicialX(velocidade.x),
	aceleracao(0.1f),
	emAceleracao(false),
	forcaGravidade(30.f),
	velocidadeTerminal(30.f)
{
	tempoMovimento.restart();
	tempoAceleracao.restart();
	attPos();
}

Entidade::~Entidade() {

}

bool Entidade::getEmTerra() const {
	return emTerra;
}

void Entidade::setEmTerra(const bool v) {
	emTerra = v;
}

Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setPos(const Vector2f& p) {
	pos = p;
	attPos();
}

float Entidade::getVelocidadeX() const {
	return vel.x;
}

float Entidade::getVelocidadeY() const {
	return vel.y;
}

void Entidade::setVelocidadeX(const float v) {
	vel.x = v;
}


void Entidade::setVelocidadeY(const float v) {
	vel.y = v;
}

float Entidade::getVelocidadeInicialX() const { 
	return velocidadeInicialX; 
}

float Entidade::getVelocidadeInicialY() const { 
	return velocidadeInicialY; 
}
void Entidade::setVelocidadeInicialX(float v) { 
	velocidadeInicialX = v;
}
void Entidade::setVelocidadeInicialY(float v) { 
	velocidadeInicialY = v;
}

void Entidade::attPos() {
	if (pSprite) {
		pSprite->setPosition(pos);
	}
}

void Entidade::gravidade() {
	float dt = tempoMovimento.getElapsedTime().asSeconds() ;

	if (!emTerra) {
		vel.y += forcaGravidade * dt;

		if (vel.y > velocidadeTerminal)
			vel.y = velocidadeTerminal;

		pos.y += vel.y * dt;
	}
	else {
		if (vel.y += dt * forcaGravidade < -90)
			vel.y = +15;

		tempoMovimento.getElapsedTime().asSeconds();
		pos.y += vel.y * dt;
	}

	attPos();
}

void Entidade::acelerar() {
	float dtAc = tempoAceleracao.getElapsedTime().asSeconds();;

	if (emAceleracao && dtAc < 0.4) {
		dtAc = tempoAceleracao.getElapsedTime().asSeconds();
		vel.x += aceleracao * dtAc;
		pos.x += vel.x * dtAc;

		attPos();
	}
}


void Entidade::resetaRelogio() {
	tempoMovimento.restart();
}


//Entidade::void salvarDataBuffer() {}