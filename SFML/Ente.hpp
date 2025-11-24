#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"
#include <random>

using namespace sf;
using namespace std;

extern mt19937 rng;

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
	void clearWindow();
	void desenhaFundo(Sprite* fundo);
	virtual void executar() = 0;
	void displayWindow();
	void desenhar();
	void static setGG(Gerenciadores::GerenciadorGrafico* pG);
	void setScale(const Vector2f& scale);

	FloatRect getBounds() const;        

	bool carregarTexturaSprite(const string& arquivo);
	bool carregarTexturaSprite(const string& arquivo, bool repeated, bool smooth);
	
	Sprite* getSprite() const;
};