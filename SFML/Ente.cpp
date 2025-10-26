#include "Ente.hpp"
#include "Gerenciador_Grafico.hpp"

GerenciadorGrafico* Ente::pGG = NULL;

Ente::Ente() :
	id(0),
	pSprite(NULL),
	textura(NULL)
{
	pSprite = new Sprite();
}

Ente::~Ente() {
	id = -1;
	if (pSprite) {
		delete pSprite;
	}
	if (textura) {
		delete textura;
	}
	pSprite = NULL;
	textura = NULL;
}

void Ente::desenhar() {
	if (pGG && pSprite) {
		pGG->desenharEnte(*pSprite);
	}
}

void Ente::setGG(GerenciadorGrafico* pG) {
	pGG = pG;
}

void Ente::setPos(const Vector2f& pos) {
	if (pSprite) pSprite->setPosition(pos);
}

void Ente::setScale(const Vector2f& scale) {
	if (pSprite) pSprite->setScale(scale);
}

FloatRect Ente::getBounds() const {
	if (pSprite) {
		return pSprite->getGlobalBounds();
	}
	return FloatRect();
}


bool Ente::carregarTexturaSprite(const string& arquivo, bool repeated, bool smooth) {
	if (textura) {
		delete textura;
		textura = NULL;
	}
	textura = new Texture();
	if (!textura->loadFromFile(arquivo)) {
		delete textura;
		textura = NULL;
		return false;
	}
	textura->setRepeated(repeated);
	textura->setSmooth(smooth);
	if (pSprite) {
		pSprite->setTexture(*textura, true);
	}
	return true;
}

Sprite* Ente::getSprite() {
	return pSprite;
}