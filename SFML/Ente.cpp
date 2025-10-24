#include "Ente.hpp"
#include "Gerenciador_Grafico.hpp"

GerenciadorGrafico* Ente::pGG = NULL;

Ente::Ente() :
	id(0),
	pFig(NULL)
{
	pFig = new RectangleShape();              
	pFig->setSize(Vector2f(50.f, 50.f));     
	pFig->setFillColor(Color::White);
	pFig->setPosition({ 0.f, 0.f });
}

Ente::~Ente() {
	id = -1;
	if (pFig) {
		delete pFig;
	}
	pFig = NULL;
}

void Ente::desenhar() {
	if (pGG && pFig) {
		pGG->desenharEnte(*pFig);
	}
}

void Ente::setGG(GerenciadorGrafico* pG) {
	pGG = pG;
}

void Ente::setCorShape(Color cor) {
	if (pFig) {
		pFig->setFillColor(cor);
	}
}

void Ente::setTamanhoShape(Vector2f tamanho) {
	if (pFig) {
		pFig->setSize(tamanho);
	}
}

FloatRect Ente::getBounds() const {
	if (pFig) {
		return pFig->getGlobalBounds();
	}
	throw "Deu merda aqui";
}

RectangleShape Ente::getShape() const {
	if (pFig) {
		return *pFig;
	}
	throw "Deu merda aqui";
}