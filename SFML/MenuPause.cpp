#include "MenuPause.hpp"
#include <iostream>
#include <fstream>

MenuPause::MenuPause() :
    Menu(),
    continuar(false),
    voltarMenu(false),
    salvar(false)
{
    set_values();
    reseta();
}

MenuPause::~MenuPause() {
}

void MenuPause::set_values() {
    const char* opcoes[] = { "PAUSADO", "Continuar", "Menu Principal", "Salvar"};
    const Vector2f posicoes[] = { {530.f, 120.f}, {560.f, 350.f}, {510.f, 450.f}, {580.f, 550.f}};

    const unsigned int tamanhos[] = { 70u, 50u, 50u, 50u };

    texts.clear();
    texts.reserve(3);

    for (size_t i = 0; i < 4; i++) {
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
    posMax = 3;
    pos = posMin;
}

void MenuPause::confirmar() {
    if (pos == 1) {
        continuar = true;
    }
    else if (pos == 2) {
        voltarMenu = true;
    }
    else if (pos == 3) {
		salvar = true;
    }
}

bool MenuPause::getContinuar() const {
    return continuar;
}

bool MenuPause::getVoltarMenu() const {
    return voltarMenu;
}

void MenuPause::setSalvar(bool s) {
    salvar = s;
}

bool MenuPause::getSalvar() const {
    return salvar;
}

void MenuPause::resetaFlags() {
    continuar = false;
    voltarMenu = false;
	salvar = false;
}


