#include "Ente.hpp"
#include "Gerenciador_Grafico.hpp"
std::mt19937 rng(std::random_device{}());

Gerenciadores::GerenciadorGrafico* Ente::pGG = NULL;

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
		pGG->desenharEnte(barraFundo);
		pGG->desenharEnte(barraVida);
	}
}

void Ente::setGG(Gerenciadores::GerenciadorGrafico* pG) {
	pGG = pG;
}

void Ente::setScale(const Vector2f& scale) {
	if (pSprite) {
		pSprite->setScale(scale);
	}
}

FloatRect Ente::getBounds() const {
	if (pSprite) {
		return pSprite->getGlobalBounds();
	}
	return FloatRect();
}
bool Ente::carregarTexturaSprite(const string& arquivo) {
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
	textura->setRepeated(false);
	textura->setSmooth(false);
	if (pSprite) {
		pSprite->setTexture(*textura, true);
	}
	return true;
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

Sprite* Ente::getSprite() const {
	return pSprite;
}