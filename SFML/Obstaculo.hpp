#pragma once

#include "Jogador.hpp"
#include "Entidade.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Obstaculo : public Entidade {
protected:
	bool danoso;
	/*   OS SEGUINTES ATRIBUTOS SERÃO DE CLASSES DERIVADAS DE OBSTÁCULO:    
		
		ah, ax q o obstaculo medio é a porta com alavanca e o dificil é a poça de água/fogo/acido.
	*/

	float largura;
	float altura;

public:
	Obstaculo(Vector2f pos, Vector2f tam, bool dano = false);
	~Obstaculo();
	//void salvarDataBuffer();
	virtual void executar() = 0;
	//virtual void salvar() = 0;
	virtual void obstaculizar(Jogador* p) = 0;

	bool getDanoso() const;
};