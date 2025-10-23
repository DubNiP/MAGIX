#include "Menu.hpp"

Menu::Menu() :
	pos(1),
	pressed(false),
	theselect(false),
	sair(false),
	iniciar(false),

	font(NULL),
	image(NULL),
	bg(NULL),

	pos_mouse(),
	mouse_coord(),

	options(),
	coords(),
	texts(),
	sizes()
{
	font = new Font();
	image = new Texture();
	bg = new Sprite();              //mover pra ente
	set_values();
}

Menu::~Menu() {
	if (font) {
		delete font;
	}
	if (image) {
		delete image;
	}
	if (bg) {
		delete bg;
	}

	font = NULL;
	image = NULL;
	bg = NULL;
}

void Menu::set_values() {
	if (!font->loadFromFile("Fonts/Newsreader-VariableFont_opsz,wght.ttf")) {
		throw "Deu Merda aqui";
	}
	if (!image->loadFromFile("Textures/Fundo_menu.png")) {
		throw "Deu Merda aqui";
	}
	if (bg) {
		bg->setTexture(*image);
	}

	pos_mouse = { 0,0 };
	mouse_coord = { 0,0 };

	options = { "Nome_Jogo","Jogar","Opções","Sair" };                                //Classe de objetos gráficos, vale a pena olhar no futuro...
	texts.resize(4);
	coords = { {490,180},{620,350},{600,420},{630,490} };
	sizes = { 80,50,50,50 };
	texts[1].setOutlineThickness(4);
	for (size_t i{}; i < texts.size(); i++) {
		texts[i].setFont(*font);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setPosition(coords[i]);
		texts[i].setOutlineColor(Color::Black);
	}
}

void Menu::loop_menu(Event& event){
	if (event.type == Event::Closed) {
		sair = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && !pressed) {
		if (pos < 3) {
			pos++;
			pressed = true;
			texts[pos].setOutlineThickness(4);
			texts[pos-1].setOutlineThickness(0);
			pressed = false;
			theselect = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && !pressed) {
		if (pos > 1) {
			pos--;
			pressed = true;
			texts[pos].setOutlineThickness(4);
			texts[pos + 1].setOutlineThickness(0);
			pressed = false;
			theselect = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && !theselect) {
		theselect = true;                                                    //OBS: O botao de opçoes n faz nada por enquanto
		if (pos == 1) {
			iniciar = true;
		}
		if (pos == 3) {
			sair = true;
		}
	}
}

void Menu::draw_menu(RenderWindow* window) {
	if (window) {
		window->clear();
		if (bg) {
			window->draw(*bg);
		}
		for (auto i : texts) {
			window->draw(i);
		}
		window->display();
	}
}

bool Menu::getSair() const {
	return sair;
}


bool Menu::getIniciar() const {
	return iniciar;
}

void Menu::reseta() {
	iniciar = false;
	sair = false;
	theselect = false;
}