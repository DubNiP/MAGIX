#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class GerenciadorGrafico;

class Ente {
protected:
	int id;
	static GerenciadorGrafico* pGG;
	RectangleShape* pFig;
public:
	Ente();
	virtual ~Ente();
	virtual void executar() = 0;
	void desenhar();
	void static setGG(GerenciadorGrafico* pG);
	void setCorShape(Color cor);
	void setTamanhoShape(Vector2f tamanho);
	FloatRect getBounds() const;
	RectangleShape getShape() const;           
};