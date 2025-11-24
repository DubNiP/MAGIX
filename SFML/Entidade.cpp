#include "Entidade.hpp"
#define velocidadeTerminal 40.f
#define forcaGravidade 30.f
#define aceleracao 0.1f

string Entidade::caminho;

Entidade::Entidade(Vector2f posicao, Vector2f velocidade, bool dir) :
	Ente(),
	pos(posicao),
	emTerra(true),
	emAceleracao(false),
	vel(velocidade),
	velocidadeInicial(velocidade),
	olhandoDir(dir),
	tempoMovimento(),
	tempoAceleracao(),
	clocksIni(false)
{
	tempoAceleracao.restart();
	tempoAceleracao.restart();
	attPos();
}

Entidade::~Entidade() {

}

void Entidade::salvarDataBuffer() {

	tempBuffer << id << " "
		<< pos.x << " "
		<< pos.y << " "
		<< emTerra << " "
		<< vel.x << " "
		<< vel.y << " "
		<< velocidadeInicial.x << " "
		<< velocidadeInicial.y << " "
		<< emAceleracao << " "
		<< olhandoDir << " ";

}

const bool Entidade::getEmTerra() const {
	return emTerra;
}

void Entidade::setEmTerra(const bool v) {
	emTerra = v;
}

void Entidade::setEmAceleracao(const bool a)
{
	emAceleracao = a;
}

const Vector2f Entidade::getPos() const {
	return pos;
}

void Entidade::setPos(const Vector2f& p) {
	pos = p;
	attPos();
}

const Vector2f Entidade::getVelocidade() const {
	return vel;
}

void Entidade::setVelocidade(const float vx, const float vy) {
	vel.x = vx;
	vel.y = vy;
}


void Entidade::setVelocidadeInicial(float vx, float vy) { 
	velocidadeInicial.x = vx;
	velocidadeInicial.y = vy;
}


void Entidade::attPos() {
	if (pSprite) {
		pSprite->setPosition(pos);
	}
}

void Entidade::gravidade() {
	if (clocksIni) {

		float dt = tempoMovimento.getElapsedTime().asSeconds();

		vel.y += forcaGravidade * dt;    // v = a * t 

		if (vel.y > velocidadeTerminal)
			vel.y = velocidadeTerminal;

		pos.y += vel.y * dt;    // x = v * t

		attPos();
	}
	return;
}


void Entidade::acelerar() {
	if (clocksIni) {
		float dtAc = tempoAceleracao.getElapsedTime().asSeconds();;

		if (emAceleracao &&  dtAc < 0.4 ) {
			vel.x += aceleracao * dtAc;
			pos.x += vel.x * dtAc;

			attPos();
		}
	}
	return;
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

void Entidade::iniciarClocks() {
	if (!clocksIni) {
		tempoMovimento.restart();
		tempoAceleracao.restart();
		clocksIni = true;
	}
}

void Entidade::retomar() {
	if (clocksIni) {
		tempoMovimento.restart();
		tempoAceleracao.restart();
	}
}
