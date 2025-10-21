#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Menu {
private:
	int pos;
	bool pressed;
	bool theselect;
	bool sair;
	bool iniciar;

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


	void set_values();
	

public:
	Menu();
	~Menu();
	void loop_menu(Event& event);
	void draw_menu(RenderWindow* window);
	bool getIniciar();
	bool getSair();
	void reseta();

};