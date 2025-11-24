#pragma once
#include <SFML/Graphics.hpp>
#include "Ente.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Entidade : public Ente {
protected:
	Vector2f pos;
	bool emTerra;
	Vector2f vel;
	Vector2f velocidadeInicial;
	bool emAceleracao;
	Clock tempoMovimento;
	Clock tempoAceleracao;
	bool olhandoDir;
	bool clocksIni;
	static string caminho;
	stringstream tempBuffer;
	ofstream buffer;
	void salvarDataBuffer();
public:
	Entidade(Vector2f posicao = Vector2f(0.f, 0.f), Vector2f velocidade = Vector2f(0.f, 0.f), bool dir = true);
	virtual ~Entidade();

	virtual void salvar() = 0;
	virtual void executar() = 0;

	const bool getEmTerra() const;
	void setEmTerra(const bool v);

	void setEmAceleracao(const bool v);
	void setTempMovSalvo(float temp);
	void setTempAclSalvo(float temp);

	const Vector2f getPos() const;
	void setPos(const Vector2f& p);


	const Vector2f getVelocidade() const;
	void setVelocidade(const float vx, const float vy);
	void setVelocidadeInicial(float vx, float vy);

	void attPos();
	void gravidade();
	void acelerar();

	void resetaRelogio();
	const bool getOlhandoDir() const;
	void setOlhandoDir(bool dir);
	void atualizaDirSprite();
	void iniciarClocks();
	void retomar();
};