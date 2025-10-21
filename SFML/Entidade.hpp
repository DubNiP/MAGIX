#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
//Vale a pena comentar que a classe ente está acoplada com entidade para o desenho das entidades.




class Entidade {
protected:
	Vector2f pos;
	RectangleShape shape;   
	// ostream buffer;
	//void salvarDataBuffer();
public:
	Entidade(Vector2f posicao);
	virtual ~Entidade();
	virtual void executar() = 0;
	//virtual void salvar() = 0;
	Vector2f getPos() const;
	void draw(RenderWindow* window);                  //Ente
	void attPos();
	void setCorShape(Color cor);
	void setTamanhoShape(Vector2f tamanho);
	FloatRect getBounds() const;
};