#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.hpp"

using namespace sf;
//Vale a pena comentar que a classe ente está acoplada com entidade para o desenho das entidades.




class Entidade {
protected:
	Vector2f pos;
	RectangleShape shape;                             //Ente??
	// ostream buffer;
	//void salvarDataBuffer();
public:
	Entidade(Vector2f posicao);
	virtual ~Entidade();
	virtual void executar() = 0;
	//virtual void salvar() = 0;
	Vector2f getPos() const;
	void setPos(const Vector2f& pos);
	void draw(RenderWindow* window);                  //Ente, deve percorrer a lista de entidades e desenhar chamando a funcao do GG
	void attPos();
	void setCorShape(Color cor);
	void setTamanhoShape(Vector2f tamanho);
	FloatRect getBounds() const;
	RectangleShape getShape() const;                   //acredito n estar sendo usada pra nada no momento
};