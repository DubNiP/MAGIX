#include "MenuPause.hpp"

MenuPause::MenuPause() :
    Menu(),
    continuar(false),
    voltarMenu(false)
{
    set_values();
    reseta();
}

MenuPause::~MenuPause() {
}

void MenuPause::set_values() {
    const char* opcoes[] = { "PAUSADO", "Continuar", "Menu Principal" };
    const Vector2f posicoes[] = { {500.f, 200.f}, {550.f, 350.f}, {450.f, 450.f} };
    const unsigned int tamanhos[] = { 70u, 50u, 50u };

    texts.clear();
    texts.reserve(3);

    for (size_t i = 0; i < 3; i++) {
        Text t;
        t.setFont(font);
        t.setString(opcoes[i]);
        t.setCharacterSize(tamanhos[i]);
        t.setPosition(posicoes[i]);
        t.setFillColor(Color::White);
        t.setOutlineColor(Color::Black);
        t.setOutlineThickness(0.f);
        texts.push_back(t);
    }

    posMin = 1;  
    posMax = 2;  
    pos = posMin;
}

void MenuPause::confirmar() {
    if (pos == 1) {
        continuar = true;
    }
    else if (pos == 2) {
        voltarMenu = true;
    }
}

bool MenuPause::getContinuar() const {
    return continuar;
}

bool MenuPause::getVoltarMenu() const {
    return voltarMenu;
}

void MenuPause::resetaFlags() {
    continuar = false;
    voltarMenu = false;
}