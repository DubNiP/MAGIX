#include "Menu.hpp"
#include "Gerenciador_Grafico.hpp"

Menu::Menu() :
	Ente(),
	pos(1),
	posMin(1),
	posMax(1),
	font(),
	texts()
{
	if (!font.loadFromFile("Fonts/ByteBounce.ttf")) {
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
}

Menu::~Menu() {
}

void Menu::executar() {          //WTFFFFFFFFF

}

void Menu::moverBaixo() {
    if (pos < posMax) {
        texts[pos].setOutlineThickness(0.f);
        pos++;
        texts[pos].setOutlineThickness(6.f);
    }
}

void Menu::moverCima() {
	if (pos > posMin) {
		texts[pos].setOutlineThickness(0.f);
		pos--;
		texts[pos].setOutlineThickness(6.f);;
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

void Menu::reseta() {
	pos = posMin;
	for (auto& t : texts) {
		t.setOutlineThickness(0.f);
	}
	if (pos < (int)texts.size()) {
		texts[pos].setOutlineThickness(6.f);
	}
}

const int Menu::getPosicao() const {
	return pos;
}
