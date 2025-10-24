#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

using namespace sf;

class Entidade: public Ente {
protected:
	Vector2f pos;
	// ostream buffer;
	//void salvarDataBuffer();
public:
	Entidade(Vector2f posicao);
	virtual ~Entidade();
	virtual void executar() = 0;
	//virtual void salvar() = 0;
	Vector2f getPos() const;
	void setPos(const Vector2f& p);
	void attPos();
};