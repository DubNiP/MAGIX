#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;


class Menu {
private:
	int pos;
	bool pressed;
	bool theselect;
	bool sair;
	bool iniciar;

	Font* font;
	Texture* image;
	Sprite* bg;              //mover para ente no futuro...

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
	bool getIniciar() const;
	bool getSair() const;
	void reseta();

};