#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GerenciadorGrafico;

class Ente {
protected:
	int id;
	static GerenciadorGrafico* pGG;
	Sprite* pSprite;
	Texture* textura;
public:
	Ente();
	virtual ~Ente();
	virtual void executar() = 0;
	void desenhar();
	void static setGG(GerenciadorGrafico* pG);

	void setPos(const Vector2f& pos);
	void setScale(const Vector2f& scale);

	FloatRect getBounds() const;        

	bool carregarTexturaSprite(const string& arquivo, bool repeated = false, bool smooth = true);
	Sprite* getSprite();
};