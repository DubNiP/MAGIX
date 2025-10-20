#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador.Grafico.hpp"
#include <iostream>

using namespace std;
using namespace sf;


class Menu {
private:
	int pos;
	bool pressed;
	bool theselect;

	GerenciadorGrafico* gerenciador;
	RectangleShape* winclose;
	Font* font;
	Texture* image;
	Sprite* bg;

	Vector2i pos_mouse;
	Vector2f mouse_coord;

	vector<const char*> options;
	vector<Vector2f> coords;
	vector<Text> texts;
	vector<size_t> sizes;

protected:
	void set_values();
	void loop_menu(Event& event);
	void draw_menu();

public:
	Menu();
	~Menu();
	void executar();
};