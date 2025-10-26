#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GerenciadorGrafico;


/*ACREDITO QUE DEVEMOS MOVER AS PARTES DE SPRITE E TEXTURA PARA CÁ E REMOVER A PARTE DE CRIAR CIRCULO, RETANGULO, ETC...*/







class Ente {
protected:
	int id;
	static GerenciadorGrafico* pGG;
	Drawable* pFig;
	Transformable* pT;
	void criarRetangulo(const Vector2f& tamanho, const Color& cor = Color::White);
	void criarCirculo(float raio, const Color& cor = Color::White);
	void criarSprite(Texture* textura);
	void criarTexto(Font* fonte, const string& str, unsigned int tamanho = 30);
public:
	Ente();
	virtual ~Ente();
	virtual void executar() = 0;
	void desenhar();
	void static setGG(GerenciadorGrafico* pG);

	void setPos(const Vector2f& pos);
	void setRot(float angulo);
	void setScale(const Vector2f& scale);

	void setCorShape(Color cor);
	void setTamanhoShape(Vector2f tamanho);
	FloatRect getBounds() const;        
};