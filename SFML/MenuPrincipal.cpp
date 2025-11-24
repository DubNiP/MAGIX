#include "MenuPrincipal.hpp"
#include "Gerenciador_Grafico.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;
using namespace sf;

MenuPrincipal::MenuPrincipal() :
    Menu(),
    sair(false),
    iniciar(false),
	ranking(false)
{
    nomeMago[0] = '\0';
    set_values();
}

MenuPrincipal::~MenuPrincipal() {
}

void MenuPrincipal::set_values() {
    const char* options[] = { "MAGIX", nomeMago,"Ranking" ,"Jogar", "Sair"};
    const Vector2f posi[] = { {570.f, 100.f}, {500.f, 200.f}, {570.f, 290} , {590.f, 380.f}, {600.f, 450.f} };
    const unsigned int tam[] = { 80u, 60u, 50u, 50u, 50u};

    texts.clear();
    texts.reserve(5);

    for (size_t i = 0; i < 5; i++) {
        Text t;
        t.setFont(font);
        t.setString(options[i]);
        t.setCharacterSize(tam[i]);
        t.setPosition(posi[i]);
        t.setFillColor(Color::White);
        t.setOutlineColor(Color::Black);
        t.setOutlineThickness(0.f);
        texts.push_back(t);
    }

    posMin = 2;  
    posMax = 4;  
    pos = posMin;
}

void MenuPrincipal::confirmar() {
    if(pos == 2){
		ranking = true;
	}
    else if (pos == 3) {
        iniciar = true;
    }
    else if (pos == 4) {
        sair = true;
    }
    
}

bool MenuPrincipal::getIniciar() const {
    return iniciar;
}

bool MenuPrincipal::getSair() const {
    return sair;
}

bool MenuPrincipal::getRanking() const {
    return ranking;
}

void MenuPrincipal::setNomeMago(const char* n) {
    if (n) {
        strncpy_s(nomeMago, sizeof(nomeMago), n, _TRUNCATE);
    } else {
        nomeMago[0] = '\0';
    }

    if (texts.size() > 1) {
        texts[1].setString(nomeMago);
    }
}

void MenuPrincipal::resetaFlags() {
    sair = false;
    iniciar = false;
	ranking = false;
}

