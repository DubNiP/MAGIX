#include "Entidade.hpp"

Entidade::Entidade(Vector2f posicao, Vector2f velocidade, bool dir) :
	Ente(),
	pos(posicao),
	emTerra(true),
	vel(velocidade),
	velocidadeInicialY(velocidade.y),
	velocidadeInicialX(velocidade.x),
	aceleracao(0.1f),
	emAceleracao(false),
	forcaGravidade(30.f),
	velocidadeTerminal(30.f),
	olhandoDir(dir)
{
	tempoMovimento.restart();
	tempoAceleracao.restart();
	attPos();
}

Entidade::~Entidade() {

}

const bool Entidade::getEmTerra() const {
	return emTerra;
}

void Entidade::setEmTerra(const bool v) {
	emTerra = v;
}

const Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setPos(const Vector2f& p) {
	pos = p;
	attPos();
}

const float Entidade::getVelocidadeX() const {
	return vel.x;
}

const float Entidade::getVelocidadeY() const {
	return vel.y;
}

void Entidade::setVelocidadeX(const float v) {
	vel.x = v;
}


void Entidade::setVelocidadeY(const float v) {
	vel.y = v;
}

const float Entidade::getVelocidadeInicialX() const { 
	return velocidadeInicialX; 
}

const float Entidade::getVelocidadeInicialY() const { 
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

const bool Entidade::getOlhandoDir() const {
	return olhandoDir;
}

void Entidade::setOlhandoDir(bool dir) {
	if (olhandoDir != dir) {
		olhandoDir = dir;
		atualizaDirSprite();
	}
}

void Entidade::atualizaDirSprite() {
	if (pSprite) {
		if (olhandoDir) {

			pSprite->setScale(abs(pSprite->getScale().x), pSprite->getScale().y);
			pSprite->setOrigin(0.f, 0.f);
		}
		else {
			
			pSprite->setScale(-abs(pSprite->getScale().x), pSprite->getScale().y);
			FloatRect bounds = pSprite->getLocalBounds();
			pSprite->setOrigin(bounds.width, 0.f);
		}
	}
}


//Entidade::void salvarDataBuffer() 