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
	Texture* image;

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
	void executar();
	void loop_menu(Event& event);
	void draw_menu();
	bool getIniciar() const;
	bool getSair() const;
	void reseta();

};