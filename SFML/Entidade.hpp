#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.hpp"

using namespace sf;

class Entidade : public Ente {
protected:
	Vector2f pos;
	bool emTerra;
	Vector2f vel;
	float velocidadeInicialY;
	float velocidadeInicialX;
	float aceleracao;
	float emAceleracao;
	float forcaGravidade;
	float velocidadeTerminal;	
	Clock tempoMovimento;
	Clock tempoAceleracao;
	bool olhandoDir;
	// ostream buffer;
	//void salvarDataBuffer();
public:
	Entidade(Vector2f posicao = Vector2f(0.f, 0.f), Vector2f velocidade = Vector2f(0.f, 0.f), bool dir = true);
	virtual ~Entidade();

	virtual void executar() = 0;
	//virtual void salvar() = 0;

	const bool getEmTerra() const;
	void setEmTerra(const bool v);

	const Vector2f getPos() const;
	void setPos(const Vector2f& p);


	const float getVelocidadeX() const;
	const float getVelocidadeY() const;
	void setVelocidadeX(const float v);
	void setVelocidadeY(const float v);

	const float getVelocidadeInicialX() const;
	const float getVelocidadeInicialY() const;
	void setVelocidadeInicialX(float v);
	void setVelocidadeInicialY(float v);

	
	void attPos();
	void gravidade();
	void acelerar();

	void resetaRelogio();
	const bool getOlhandoDir() const;
	void setOlhandoDir(bool dir);
	void atualizaDirSprite();
};