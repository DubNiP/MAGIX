#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include <random>
extern std::mt19937 rng;

using namespace sf;
using namespace std;

class Ente {
protected:
	int id;
	static Gerenciadores::GerenciadorGrafico* pGG;
	Sprite* pSprite;
	Texture* textura;
	RectangleShape barraFundo;
	RectangleShape barraVida;
public:
	Ente();
	virtual ~Ente();
	virtual void executar() = 0;
	void desenhar();
	void static setGG(Gerenciadores::GerenciadorGrafico* pG);

	void setPos(const Vector2f& pos);
	void setScale(const Vector2f& scale);

	FloatRect getBounds() const;        

	bool carregarTexturaSprite(const string& arquivo, bool repeated = false, bool smooth = true);
	Sprite* getSprite();
};