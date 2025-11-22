#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ente.hpp"

using namespace std;
using namespace sf;

class Menu: public Ente {
protected:
	int pos;
	int posMin;  
	int posMax;

	Font font;
	vector<Text> texts;

	virtual void set_values() = 0;

public:
	Menu();
	~Menu();

	void executar();
	void moverBaixo();
	void moverCima();
	virtual void confirmar()= 0;
	void draw_menu();
	void reseta();

	const int getPosicao() const;
};