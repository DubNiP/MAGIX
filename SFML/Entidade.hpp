#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

using namespace sf;

class Entidade: public Ente {
protected:
	Vector2f pos;
	bool emTerra;
	Vector2f vel;
	float velocidadeInicialY;
	float velocidadeInicialX;
	float forcaGravidade;
	Clock tempoMovimento;
	// ostream buffer;
	//void salvarDataBuffer();
public:
	Entidade(Vector2f posicao, Vector2f velocidade = Vector2f(0.f, 0.f));
	virtual ~Entidade();

	virtual void executar() = 0;
	//virtual void salvar() = 0;

	void setEmTerra(const bool v);
	
	Vector2f getPos() const;
	void setPos(const Vector2f& p);
	float getVelocidade() const;
	void setVelocidadeY(const float v);
	void setVelocidadeX(const float v);
	
	void attPos();
	void gravidade();

	void resetaRelogio();
};