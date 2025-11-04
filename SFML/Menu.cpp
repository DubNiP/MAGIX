#include "Menu.hpp"
#include "Gerenciador_Grafico.hpp"

Menu::Menu() :
	Ente(),
	pos(1),
	pressed(false),
	theselect(false),
	sair(false),
	iniciar(false),

	font(NULL),

	options(),
	coords(),
	texts(),
	sizes()
{
	font = new Font();

	if (!font->loadFromFile("Fonts/ByteBounce.ttf")) {
		throw "Textura não carregada";
	}
	if (!carregarTexturaSprite("Textures/background 1.png")) {
		throw "Textura não carregada";
	}
	if (Sprite* sp = getSprite()) {
		if (const Texture* tex = sp->getTexture()) {
			Vector2u tamText = tex->getSize();
			if (tamText.x > 0 && tamText.y > 0) {
				float escalaX = 1280.f / tamText.x;
				float escalaY = 720.f / tamText.y;
				setScale(Vector2f(escalaX, escalaY));
			}
		}
	}

	set_values();
}

Menu::~Menu() {
	if (font) {
		delete font;
	}
	font = NULL;
}

void Menu::set_values() {

	options = { "Nome_Jogo","Jogar","Ranking","Sair" };                                //Classe de objetos gráficos, vale a pena olhar no futuro...
	texts.resize(4);
	coords = { {490.f,110.f},{620.f,380.f},{600.f,450.f},{630.f,520.f} };
	sizes = { 80u,50u,50u,50u };

	texts[1].setOutlineThickness(6);


	for (size_t i = 0; i < texts.size(); i++) {
		texts[i].setFont(*font);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setPosition(coords[i]);
		texts[i].setOutlineColor(Color::Black);
	}
}


void Menu::executar() {          //WTFFFFFFFFF

}

void Menu::loop_menu(Event& event){
	if (event.type == Event::Closed) {
		sair = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && !pressed) {
		if (pos < 3) {
			pos++;
			pressed = true;
			texts[pos].setOutlineThickness(6);
			texts[pos-1].setOutlineThickness(0);
			pressed = false;
			theselect = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && !pressed) {
		if (pos > 1) {
			pos--;
			pressed = true;
			texts[pos].setOutlineThickness(6);
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

void Menu::draw_menu() {
	if (pGG){
		pGG->clearWindow();

		desenhar();
		
		for (auto& t : texts) {
			pGG->desenharEnte(t);
		}
		pGG->displayWindow();
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