#include "MenuSelecaoFase.hpp"

MenuSelecaoFase::MenuSelecaoFase() :
    Menu(),
    voltar(false),
    faseEscolhida(-1)
{
    set_values();
    reseta();
}

MenuSelecaoFase::~MenuSelecaoFase() {
}

void MenuSelecaoFase::set_values() {
    const char* opcoes[] = { "Selecionar Fase", "Carregar", "Fase 1", "Fase 2", "Voltar"};
    const Vector2f posicoes[] = { {500.f, 110.f},  {600.f, 210.f}, {600.f, 300.f}, {600.f, 400.f}, {600.f, 500.f} };
    const unsigned int tamanhos[] = { 60u, 50u, 50u, 50u, 50u };

    texts.clear();
    texts.reserve(5);

    for (size_t i = 0; i < 5; i++) {
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
    posMax = 4;  
    pos = posMin;
}

void MenuSelecaoFase::confirmar() {
    if (pos == 1) {
		faseEscolhida = 1;
    }
    if (pos == 2) {
        faseEscolhida = 2;
    }
    else if (pos == 3) {
        faseEscolhida = 3;
    }
    else if (pos == 4) {
        voltar = true;
    }

}

bool MenuSelecaoFase::getVoltar() const {
    return voltar;
}

int MenuSelecaoFase::getFaseEscolhida() const {
    return faseEscolhida;
}

void MenuSelecaoFase::resetaFlags() {
    voltar = false;
    faseEscolhida = -1;
}