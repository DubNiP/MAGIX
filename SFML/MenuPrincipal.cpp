#include "MenuPrincipal.hpp"

MenuPrincipal::MenuPrincipal() :
    Menu(),
    sair(false),
    iniciar(false)
{
    set_values();
    reseta();
}

MenuPrincipal::~MenuPrincipal() {
}

void MenuPrincipal::set_values() {
    const char* options[] = { "MAGIX", "Jogar", "Ranking", "Sair" };
    const Vector2f posi[] = { {580.f, 110.f}, {620.f, 380.f}, {600.f, 450.f}, {630.f, 520.f} };
    const unsigned int tam[] = { 80u, 50u, 50u, 50u };

    texts.clear();
    texts.reserve(4);

    for (size_t i = 0; i < 4; i++) {
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

    posMin = 1;  
    posMax = 3;  
    pos = posMin;
}

void MenuPrincipal::confirmar() {
    if (pos == 1) {
        iniciar = true;
    }
    else if (pos == 3) {
        sair = true;
    }
    // pos == 2 (Ranking) não faz nada ainda
}

bool MenuPrincipal::getIniciar() const {
    return iniciar;
}

bool MenuPrincipal::getSair() const {
    return sair;
}

void MenuPrincipal::resetaFlags() {
    iniciar = false;
    sair = false;
}