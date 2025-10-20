#include "Menu.hpp"

Menu::Menu() :
	gerenciador(NULL),
	winclose(NULL),
	font(NULL),
	image(NULL),
	bg(NULL)
{
	gerenciador = GerenciadorGrafico::getInstancia();
	winclose = new RectangleShape();
	font = new Font();
	image = new Texture();
	bg = new Sprite();
	set_values();
}

Menu::~Menu() {
	if (winclose) {
		delete winclose;
	}
	if (font) {
		delete font;
	}
	if (image) {
		delete image;
	}
	if (bg) {
		delete bg;
	}

	gerenciador = NULL;
	winclose = NULL;
	font = NULL;
	image = NULL;
	bg = NULL;
}

void Menu::set_values() {
	if (gerenciador != NULL) {
		pos = 1;
		pressed = theselect = false;
		if (!font->loadFromFile("Fonts/Newsreader-VariableFont_opsz,wght.ttf")) {
			throw "Deu Merda aqui";
		}
		if (!image->loadFromFile("Textures/Fundo_menu.png")) {
			throw "Deu Merda aqui";
		}
		bg->setTexture(*image);

		pos_mouse = { 0,0 };
		mouse_coord = { 0,0 };

		options = { "Nome_Jogo","Jogar","Opções","Sair" };
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
	else {
		throw "Deu merda aqui";
	}
}

void Menu::loop_menu(Event& event){
	if (event.type == Event::Closed ||
		Keyboard::isKeyPressed(Keyboard::Escape)) {
		gerenciador->getWindow()->close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && !pressed) {
		if (pos < 3) {
			pos++;
			pressed = true;
			texts[pos].setOutlineThickness(4);
			texts[pos-1].setOutlineThickness(0);
			pressed = false;
			theselect = false;
			cout << "pos: " << pos << "\n";
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
			cout << "pos: " << pos << "\n";
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Enter) && !theselect) {
		theselect = true;                                                    //OBS: os outros botões n fazem nada por enquanto..
		if (pos == 3) {
			gerenciador->getWindow()->close();
		}
		cout << options[pos] << endl;
	}
}

void Menu::draw_menu() {
	gerenciador->getWindow()->clear();
	gerenciador->getWindow()->draw(*bg);
	for (auto i : texts) {
		gerenciador->getWindow()->draw(i);
	}
	gerenciador->getWindow()->display();
}

void Menu::executar() {
	Event event;
	while (gerenciador->getWindow()->isOpen()) {
		while (gerenciador->getWindow()->pollEvent(event)) {
			loop_menu(event);
		}
		draw_menu();
	}
}