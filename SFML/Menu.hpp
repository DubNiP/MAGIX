#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ente.hpp"

using namespace std;
using namespace sf;


class Menu: public Ente {
private:
	int pos;
	bool pressed;
	bool theselect;
	bool sair;
	bool iniciar;

	Font* font;

	vector<string> options;
	vector<Vector2f> coords;
	vector<Text> texts;
	vector<unsigned int> sizes;


	void set_values();
	

public:
	Menu();
	~Menu();
	void executar();
	void loop_menu(Event& event);      //analisar passagem por referência escondida
	void draw_menu();
	bool getIniciar() const;
	bool getSair() const;
	void reseta();

};